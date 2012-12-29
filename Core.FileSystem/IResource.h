/*========================================================
* IResource.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _IRESOURCE_H__
#define _IRESOURCE_H__

#include "../Core.COM/Interfaces.h"
#include "../Core.COM/Intellectual.h"
#include "FileSystem_fwd.h"
#include <string>

namespace Core
{
	namespace FileSystem
	{
		/// IResource interface
		/** Base interface for all resources 
		 *  @ingroup  FileSystem */
		SCOM_INTERFACE(IResource, "b072a13c-3298-4a19-ac48-946bbbe05873", SCOM::IUnknown)
		{
		public:
			/// Returns parent resource
			virtual Core::SCOM::ComPtr<IResource> Parent() = 0;

			/// Returns base name of resource (like file or folder name without preceding path)
			virtual std::string BaseName() = 0;
			
			/// Returns full resource path, paths are persistent between the sessions
			virtual const std::string& FullPath() = 0;

			/// Determines if this resource is accessible and you can perform complex operations on it
			virtual bool IsAccessible() = 0;

			/// Pass traverser through resource tree
			virtual void Accept(IFSTraverser* traverser) = 0;
		};	
	} // namespace
} // namespace


#endif // _IRESOURCE_H__