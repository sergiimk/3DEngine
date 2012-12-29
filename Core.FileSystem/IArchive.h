/*========================================================
* IArchive.h
* @author Sergey Mikhtonyuk
* @date 21 December 2008
=========================================================*/
#ifndef _IARCHIVE_H__
#define _IARCHIVE_H__

#include "IResourceContainer.h"
#include "FileSystem_fwd.h"

namespace Core
{
	namespace FileSystem
	{
		/// Interface to archive files
		/** Archives are fully transparent, so you can use them as usual folder,
		  * this is also great when you work with resources, you can work
		  * with them stored in a folder or in an archive uniformly, pack and unpack them
		  * without changing the loading code 
		  *
		  * @ingroup FileSystem */
		SCOM_INTERFACE(IArchive, "bc9dcbc4-2a0b-49ba-b242-02e988dd613d", IResourceContainer)
		{
		public:
			/// Returns child with specified name (child is a top level file or folder in archive)
			virtual Core::SCOM::ComPtr<IResource> FindChild(const std::string& name) = 0;

			/// Returns item with specified name
			virtual Core::SCOM::ComPtr<IResource> FindItem(const std::string& name) = 0;
		};
	
	
	} // namespace
} // namespace


#endif // _IARCHIVE_H__