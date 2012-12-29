/*========================================================
* CArchive.h
* @author Sergey Mikhtonyuk
* @date 21 December 2008
=========================================================*/
#ifndef _CARCHIVE_H__
#define _CARCHIVE_H__

#include "IArchive.h"
#include "CFile.h"
#include "../Core.FileSystem.MiniZip/minizip/unzip.h"
#include <vector>

namespace Core
{
	namespace FileSystem
	{
		/// Implements both IArchive and IFile interfaces
		/** @ingroup FileSystem */
		class NOVTABLE CArchive : 
			public CFile,
			public IArchive
		{
		public:
			DECLARE_IMPLEMENTATION_DERIVED(CArchive, CFile)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IArchive)
				INTERFACE_ENTRY(IResourceContainer)
				INTERFACE_ENTRY_CHAIN(CFile)
			END_INTERFACE_MAP()

			bool							IsAccessible()	{ return CFile::IsAccessible(); }
			Core::SCOM::ComPtr<IResource>	Parent()		{ return CFile::Parent(); }
			std::string						BaseName()		{ return CFile::BaseName(); }
			const std::string&				FullPath()		{ return CFile::FullPath(); }
			void							Accept(IFSTraverser* traverser);

			const std::vector<IResource*>&	GetChildren();
			Core::SCOM::ComPtr<IResource>	FindChild(const std::string& name);
			Core::SCOM::ComPtr<IResource>	FindItem(const std::string& name);

			void							InitItems();
			void							BuildHierarchy(const std::string &fldPath, std::vector<IResource*> &children);
			std::pair<int, int>				GetSubpathBouds(const std::string &base, const std::string &chld);
			virtual ~CArchive();

		protected:
			std::vector<IResource*> mChildren;
			std::vector<IResource*> mItems;
		};


		/*=======================================================================
		=  Guard
		=======================================================================*/
		struct ArchiveGuard
		{
			ArchiveGuard(const char *p) : file(unzOpen(p)) { }
			~ArchiveGuard() { unzClose(file); }
			unzFile file;
		};
	
	
	} // namespace
} // namespace


#endif // _CARCHIVE_H__