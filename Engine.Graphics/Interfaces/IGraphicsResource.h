/*========================================================
* IResource.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __IRESOURCE_H__
#define __IRESOURCE_H__

#include "../Graphics_fwd.h"
#include "../../Core.Utils/URL.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	namespace Graphics
	{
		/// Base interface for all resources with integrated reference counter
		/** All resources act like a proxies to the real data, they contain all info
		 *  needed to load real data from disk when the user is added and they hold it
		 *  until last user is removed. This allows dynamic resource management with 
		 *  different caching policies.
		 *
		 *  @ingroup Graphics */
		SCOM_INTERFACE(IGraphicsResource, "1cc7769d-9ab1-43d2-9eef-d91d34d3a7fa", Core::SCOM::IUnknown)
		{
		public:
			/// Indicates interest in data, commands proxy to load the real data needed for rendering
			virtual void AddUser() = 0;

			/// Decreases user counter, when it reaches zero proxy can free underlying resources
			virtual void RemoveUser() = 0;

			/// Tells if the data is prepared for rendering
			virtual bool IsLoaded() const = 0;

			/// Returns the unique resource locator (can be empty in dynamically-created resources that not bound to data on disk)
			virtual Utils::URL* GetURL() = 0;
		};

	} // namespace
} // namespace

#endif