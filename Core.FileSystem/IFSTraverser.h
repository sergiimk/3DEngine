/*========================================================
* IFSTraverser.h
* @author Sergey Mikhtonyuk
* @date 03 May 2009
=========================================================*/
#ifndef _IFSTRAVERSER_H__
#define _IFSTRAVERSER_H__

namespace Core
{
	namespace FileSystem
	{
		//////////////////////////////////////////////////////////////////////////
		class IFolder;
		class IFile;
		class IArchive;
		//////////////////////////////////////////////////////////////////////////


		/// Eases the operations with tree structure of file system
		/** @ingroup FileSystem */
		class IFSTraverser
		{
		public:
			/// Called on enter to folder
			/** @return false if you want to stop traversing this branch */
			virtual bool VisitFolder(IFolder* fld) = 0;

			/// Allows depth-first traversing
			virtual void LeaveFolder(IFolder* fld) = 0;

			/// Called on enter to archive
			/** @return false if you want to stop traversing this branch */
			virtual bool VisitArchive(IArchive* arch) = 0;

			/// Allows depth-first traversing
			virtual void LeaveArchive(IArchive* arch) = 0;

			/// Called to process the file
			virtual void VisitFile(IFile* file) = 0;
		};

	} // namespace
} // namespace

#endif	// _IFSTRAVERSER_H__