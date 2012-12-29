/*========================================================
* IResourceContainer.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _IRESOURCECONTAINER_H__
#define _IRESOURCECONTAINER_H__

#include "IResource.h"
#include <vector>

namespace Core
{
	namespace FileSystem
	{

		/// IResourceContainer interface
		/** Composite class of IResource hierarchy
		 *  @ingroup  FileSystem */
		SCOM_INTERFACE(IResourceContainer, "3a52847a-c631-4309-ab37-58c1819d62b9", IResource)
		{
		public:
			/// Retrieves null-terminated list of child resources
			virtual const std::vector<IResource*>& GetChildren() = 0;
		};

	
	} // namespace
} // namespace


#endif // _IRESOURCECONTAINER_H__