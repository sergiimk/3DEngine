/*========================================================
* CArchFile.cpp
* @author Sergey Mikhtonyuk
* @date 21 December 2008
=========================================================*/

#include "CArchFile.h"
#include "CArchive.h"
#include "CFileSystem.h"
#include "IFSTraverser.h"

namespace Core
{
	namespace FileSystem
	{
		//////////////////////////////////////////////////////////////////////////

		void CArchFile::FinalConstruct(CFileSystem *fs, const boost::filesystem::path &arch, 
			const boost::filesystem::path &path, unsigned long offset)
		{
			mFileSystem = fs;
			mArchive = arch;
			mPath = path;
			mExtension =  boost::filesystem::extension(mPath);
			mOffset = offset;
		}

		//////////////////////////////////////////////////////////////////////////

		CArchFile::~CArchFile()
		{
			mFileSystem->CloseHandle(mPath.string());
		}

		//////////////////////////////////////////////////////////////////////////
		
		Core::SCOM::ComPtr<IResource> CArchFile::Parent()
		{
			Core::SCOM::ComPtr<IResource> ret;

			/// \todo improve logic of "has parent" check
			if(mPath.has_parent_path())
			{
				boost::filesystem::path pp = mPath.parent_path();
				if(pp.string()[pp.string().length() - 1] != ':')
					mFileSystem->GetResource(pp, ret.wrapped());
			}
			return ret;
		}

		//////////////////////////////////////////////////////////////////////////

		bool CArchFile::IsAccessible()
		{
			return true;
		}

		//////////////////////////////////////////////////////////////////////////

		IFileSystem* CArchFile::FileSystem()
		{
			return mFileSystem;
		}

		//////////////////////////////////////////////////////////////////////////

		std::string CArchFile::BaseName()
		{
			return mPath.filename();
		}

		//////////////////////////////////////////////////////////////////////////

		const std::string& CArchFile::FullPath()
		{
			return mPath.string();
		}

		//////////////////////////////////////////////////////////////////////////

		void CArchFile::Accept(IFSTraverser* traverser)
		{
			traverser->VisitFile(this);
		}

		//////////////////////////////////////////////////////////////////////////

		const std::string& CArchFile::Extension()
		{
			return mExtension;
		}

		//////////////////////////////////////////////////////////////////////////

		std::fstream& CArchFile::Stream(std::ios::open_mode mode)
		{
			throw 1;
			//ASSERT(IsAccessible())
			//return std::fstream(FullPath().c_str(), mode);
		}


		/*=======================================================================
		 =  Reads
		 =======================================================================*/
		// This non-member function is used to prevent async reading on deleted file handle
		static void ReadFile_Exec(unsigned long offset, const std::string &arch, char **ppBuffer, std::ios::streamoff &size)
		{
			*ppBuffer = 0; size = 0;
			ArchiveGuard g(arch.c_str());

			if(unzSetOffset(g.file, offset) != UNZ_OK) return;
			
			unz_file_info fi;
			if(unzGetCurrentFileInfo(g.file, &fi, 0, 0, 0, 0, 0, 0) != UNZ_OK) return;
			*ppBuffer = new char[size = fi.uncompressed_size];

			if(unzOpenCurrentFile(g.file) != UNZ_OK) return;
			unzReadCurrentFile(g.file, *ppBuffer, fi.uncompressed_size);
			unzCloseCurrentFile(g.file);
		}

		//////////////////////////////////////////////////////////////////////////

		void CArchFile::ReadFile(char **ppBuffer, std::ios::streamoff &size)
		{
			ReadFile_Exec(mOffset, mArchive.string(), ppBuffer, size);
		}

		//////////////////////////////////////////////////////////////////////////

		void CArchFile::ReadFileAsync(char **ppBuffer, std::ios::streamoff &size, boost::function<void ()> &handler)
		{
			mFileSystem->Proactor().ScheduleOperation(
				boost::function<void ()>(
					boost::bind(ReadFile_Exec, mOffset, mArchive.string(), ppBuffer, boost::ref(size))), 
				handler);
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace