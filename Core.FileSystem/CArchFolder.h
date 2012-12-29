/*========================================================
* CArchFolder.h
* @author Sergey Mikhtonyuk
* @date 27 December 2008
=========================================================*/
#ifndef _CARCHFOLDER_H__
#define _CARCHFOLDER_H__

#include "IFolder.h"
#include "../Core.COM/Implementations.h"
#include <boost/filesystem.hpp>

namespace Core
{
	namespace FileSystem
	{
		class CArchive;
		class CFileSystem;



		/// Implementation of IFolder interface for folder in archive
		/** @ingroup FileSystem */
		class NOVTABLE CArchFolder : 
			public SCOM::ComRootObject<SCOM::MultiThreadModel>,
			public IFolder
		{
			friend class CArchive;
		public:
			DECLARE_IMPLEMENTATION(CArchFolder)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IFolder)
				INTERFACE_ENTRY(IResourceContainer)
				INTERFACE_ENTRY(IResource)
			END_INTERFACE_MAP()

			bool							IsAccessible();
			Core::SCOM::ComPtr<IResource>	Parent();
			std::string						BaseName();
			const std::string&				FullPath();
			void							Accept(IFSTraverser* traverser);

			const std::vector<IResource*>&	GetChildren();

			IFileSystem*					FileSystem();
			Core::SCOM::ComPtr<IResource>	FindChild(const std::string &name);

			void				FinalConstruct(	CFileSystem *fs, const boost::filesystem::path &arch, 
												const boost::filesystem::path &path);
			virtual ~CArchFolder();

		protected:
			CFileSystem*			mFileSystem;
			boost::filesystem::path mArchive;
			boost::filesystem::path mPath;
			std::vector<IResource*> mChildren;
		};	
	
	
	} // namespace
} // namespace


#endif // _CARCHFOLDER_H__