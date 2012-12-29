/*========================================================
* IFolder.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _IFOLDER_H__
#define _IFOLDER_H__

#include "IResourceContainer.h"
#include "FileSystem_fwd.h"

namespace Core
{
	namespace FileSystem
	{
		/// Composite interface of file system
		/** @ingroup FileSystem */
		SCOM_INTERFACE(IFolder, "246f0486-5bc5-414e-812c-c0bbec5664fe", IResourceContainer)
		{
		public:
			/// File system object
			virtual IFileSystem* FileSystem() = 0;

			/// Service method for finding the child resource by its name
			virtual Core::SCOM::ComPtr<IResource> FindChild(const std::string &name) = 0;
		};
	
	} // namespace
} // namespace


#endif // _IFOLDER_H__