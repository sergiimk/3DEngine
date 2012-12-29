/*========================================================
* CFileSystem.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _CFILESYSTEM_H__
#define _CFILESYSTEM_H__

#include "IFileSystem.h"
#include "../Core.COM/Implementations.h"
#include "../Core/AdapterFactoyContainer.h"
#include "../Core.Utils/stringutils.h"
#include <hash_map>
#include <boost/filesystem.hpp>

namespace Core
{
	namespace FileSystem
	{
		class IArchive;

		
		/// Implementation of IFileSystem interface
		/** Facade class that executes operation on resources 
		 *  @ingroup FileSystem */
		class NOVTABLE CFileSystem : 
			public SCOM::ComRootObject<SCOM::MultiThreadModel>,
			public IFileSystem
		{
		public:
			DECLARE_IMPLEMENTATION2(CFileSystem, SCOM::ComClassFactorySingleton)
	
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IFileSystem)
			END_INTERFACE_MAP()

			CFileSystem();
			virtual ~CFileSystem();
	
			// ------------------- IFileSystem members -----------------------
			Core::SCOM::ComPtr<IFolder>		CurrentFolder();
			Core::SCOM::ComPtr<IResource>	GetResource(const std::string& path, bool searchArchives);

			void				RegisterFileAdapterFactory(IAdapterFactory *pFactory);
			SCOM::HResult		CreateFileAdapter(IFile* file, SCOM_RIID uid, void **ppAdapter);
			Utils::Proactor<1>&	Proactor() { return mProactor; }

			std::string			PathGetParentFolder(const char* path) const;
			std::string			PathCombine(const char* path1, const char* path2) const;
			std::string			PathGetFull(const char* path) const;

			//----------------------------------------------------------------

			void		AddHandle(const std::string &path, IResource* res);
			void		GetResource(const std::string& path, IResource** ppRes);
			void		GetResource(const boost::filesystem::path &path, IResource** ppRes);
			void		TryGetResource(const boost::filesystem::path &path, IResource** ppRes);

			void		CreateFileHandle(const boost::filesystem::path &path, IFile** ppFile);
			void		CreateFolderHandle(const boost::filesystem::path &path, IFolder** ppFolder);
			void		CreateArchiveHandle(const boost::filesystem::path &path, IArchive** ppArchive);
			void		CloseHandle(const std::string &path);

		protected:
			typedef std::hash_map<std::string, IResource*> TResourceMap;

			TResourceMap					mResourceMap;
			AdapterFactoyContainer			mFileAdapterContainer;
			Utils::Proactor<1>				mProactor;
		};
	
	
	} // namespace
} // namespace


#endif // _CFILESYSTEM_H__