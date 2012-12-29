/*========================================================
* CFileSystem.cpp
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#include "CFileSystem.h"
#include "../Core.Logging/ILogger.h"
#include "CFile.h"
#include "CFolder.h"
#include "CArchive.h"
#include "CXMLFileAdapter.h"
#include "CINIFileAdapter.h"
#include "../Core.COM/Intellectual.h"
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <vector>

namespace Core
{
	namespace FileSystem
	{
		//////////////////////////////////////////////////////////////////////////

		namespace bfs = boost::filesystem;

		//////////////////////////////////////////////////////////////////////////

		CFileSystem::CFileSystem()
		{
			LogTrace("[Init] Initializing file system");

			// Adding built-in adapter factories
			SCOM::ComPtr<IAdapterFactory> pFactory;
			scom_new<CXMLFileAdapterFactory>(pFactory);
			mFileAdapterContainer.AddFactory(pFactory);
			pFactory.Release();
			scom_new<CINIFileAdapterFactory>(pFactory);
			mFileAdapterContainer.AddFactory(pFactory);
		}
		
		//////////////////////////////////////////////////////////////////////////

		CFileSystem::~CFileSystem()
		{
			LogTrace("[Shutdown] Shutting down file system");

			// Zero out all non-archives
			for (TResourceMap::iterator it = mResourceMap.begin(); 
				it != mResourceMap.end() ; ++it)
			{
				IArchive* pArch;
				interface_cast<IArchive>(it->second, &pArch);
				if(pArch)
					pArch->Release();
				else
					it->second = 0;
			}
			
			TResourceMap::iterator it = mResourceMap.begin(); 
			while(it != mResourceMap.end())
			{
				if(it->second)
				{
					IResource *arch = it->second;
					
					it->second = 0;
					LogWarningAlways("Releasing cached archive: %s", arch->FullPath().c_str());
					arch->Release();

					// iterator now invalid - start over
					it = mResourceMap.begin();
					continue;
				}
				++it;
			}
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::TryGetResource(const boost::filesystem::path &path, IResource** ppRes)
		{
			TResourceMap::const_iterator it = mResourceMap.find(path.string());
			*ppRes = it == mResourceMap.end() ? 0 : it->second;
			if(*ppRes)
				(*ppRes)->AddRef();
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::CreateFileHandle(const bfs::path& path, IFile** ppFile)
		{
			CFile* pFile;
			scom_new<CFile>(&pFile);
			pFile->FinalConstruct(this, path);

			mResourceMap.insert(std::make_pair(pFile->FullPath(), pFile));
			*ppFile = pFile;
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::CreateFolderHandle(const bfs::path &path, IFolder** ppFolder)
		{
			CFolder *pFld;
			scom_new<CFolder>(&pFld);
			pFld->FinalConstruct(this, path);

			mResourceMap.insert(std::make_pair(pFld->FullPath(), pFld));
			*ppFolder = pFld;
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::CreateArchiveHandle(const bfs::path &path, IArchive** ppArchive)
		{
			CArchive *pArch;
			scom_new<CArchive>(&pArch);
			pArch->FinalConstruct(this, path);

			mResourceMap.insert(std::make_pair(pArch->FullPath(), (IResource*)(IFile*)pArch));

			/// \todo Avoid caching of archives
			*ppArchive = pArch;
			(*ppArchive)->AddRef();
		}

		//////////////////////////////////////////////////////////////////////////

		Core::SCOM::ComPtr<IFolder> CFileSystem::CurrentFolder()
		{
			IResource* res;
			GetResource(bfs::current_path(), &res);
			Core::SCOM::ComPtr<IFolder> ret = (IFolder*)res;
			res->Release();
			return ret;
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::AddHandle(const std::string &path, Core::FileSystem::IResource *res)
		{
			mResourceMap.insert(std::make_pair(path, res));
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::CloseHandle(const std::string &path)
		{
			TResourceMap::iterator it = mResourceMap.find(path);
			mResourceMap.erase(it);
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::GetResource(const std::string& path, IResource** ppRes)
		{
			GetResource(bfs::path(path), ppRes);
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::GetResource(const bfs::path &path, IResource** ppRes)
		{
			bfs::path p = bfs::system_complete(path);
			
			// Is already loaded?
			TryGetResource(p, ppRes);
			if(*ppRes) return;

			// Resolve type and create
			if(bfs::exists(p) && bfs::is_regular_file(p))
			{
				if(bfs::extension(p) == ".zip")
				{
					IArchive* parch;
					CreateArchiveHandle(p, &parch);
					*ppRes = parch;
				}
				else
				{
					IFile* pfile;
					CreateFileHandle(p, &pfile);
					*ppRes = pfile;
				}
			}
			else if(bfs::is_directory(path))
			{
				IFolder* pfld;
				CreateFolderHandle(p, &pfld);
				*ppRes = pfld;
			}
		}

		//////////////////////////////////////////////////////////////////////////

		Core::SCOM::ComPtr<IResource> CFileSystem::GetResource(const std::string& path, bool searchArchives)
		{
			Core::SCOM::ComPtr<IResource> pResource;

			bfs::path search = bfs::system_complete(bfs::path(path));
			bfs::path root = search.root_path();

			GetResource(search, pResource.wrapped());

			if(!pResource && searchArchives)
			{
				// Find archive
				bfs::path current = search.parent_path();
				while(current != root)
				{
					if(bfs::is_regular_file(current) && bfs::exists(current))
						break;
					current = current.parent_path();
				}

				// Create CArchive and get child
				if(current.extension() == ".zip")
				{
					SCOM::ComPtr<IArchive> arch;
					IResource* pRes;
					GetResource(current, &pRes);
					arch = pRes;
					pRes->Release();
					pResource = arch->FindItem(search.string().substr(current.string().size() + 1));
				}
			}
			return pResource;
		}

		//////////////////////////////////////////////////////////////////////////

		std::string CFileSystem::PathGetParentFolder(const char* path) const
		{
			bfs::path p(path);
			return p.parent_path().string();
		}

		//////////////////////////////////////////////////////////////////////////

		std::string CFileSystem::PathCombine(const char* path1, const char* path2) const
		{
			bfs::path p(path1);
			p /= path2;
			return p.string();
		}

		//////////////////////////////////////////////////////////////////////////

		std::string CFileSystem::PathGetFull(const char* path) const
		{
			return bfs::system_complete(path).string();
		}

		//////////////////////////////////////////////////////////////////////////

		void CFileSystem::RegisterFileAdapterFactory(IAdapterFactory *pFactory)
		{
			mFileAdapterContainer.AddFactory(pFactory);
		}

		//////////////////////////////////////////////////////////////////////////
		
		SCOM::HResult CFileSystem::CreateFileAdapter(IFile* file, SCOM_RIID uid, void **ppAdapter)
		{
			return mFileAdapterContainer.CreateAdapter(file, uid, ppAdapter);
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace