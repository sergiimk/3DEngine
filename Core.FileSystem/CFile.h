/*========================================================
* CFile.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _CFILE_H__
#define _CFILE_H__

#include "IFile.h"
#include "../Core.COM/Implementations.h"
#include <boost/filesystem.hpp>

namespace Core
{
	namespace FileSystem
	{
		class CFileSystem;


		/// Implementation of IFile interface
		/** @ingroup FileSystem */
		class NOVTABLE CFile : 
			public SCOM::ComRootObject<SCOM::MultiThreadModel>,
			public IFile
		{
		public:
			DECLARE_IMPLEMENTATION(CFile)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IFile)
				INTERFACE_ENTRY(IResource)
			END_INTERFACE_MAP()

			bool							IsAccessible();
			Core::SCOM::ComPtr<IResource>	Parent();
			std::string						BaseName();
			const std::string&				FullPath();
			void							Accept(IFSTraverser* traverser);

			IFileSystem*					FileSystem();
			const std::string&				Extension();
			std::fstream&					Stream(std::ios::open_mode mode);
			void							ReadFile(char **ppBuffer, std::ios::streamoff &size);
			void							ReadFileAsync(char **ppBuffer, 
														std::ios::streamoff &size, 
														boost::function<void ()> &handler);

			void FinalConstruct(CFileSystem *fs, const boost::filesystem::path &path);
			virtual ~CFile();

		protected:
			CFileSystem*			mFileSystem;
			boost::filesystem::path mPath;
			std::string				mExtension;
			std::fstream			mFileStream;
		};


	
	} // namespace
} // namespace


#endif // _CFILE_H__