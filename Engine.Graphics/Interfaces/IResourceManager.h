/*========================================================
* IResourceManager.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __IRESOURCE_MANAGER_H__
#define __IRESOURCE_MANAGER_H__

#include "../Graphics_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	namespace Graphics
	{
		/// Base interface to all resource managers
		/** @ingroup Graphics */
		SCOM_INTERFACE(IResourceManager, "851f0ea5-850c-4896-9ff4-5e6d34fe4342", Core::SCOM::IUnknown)
		{
		public:
			virtual void OnDeviceLost() = 0;
			virtual void OnDeviceReset() = 0;
		};

	} // namespace
} // namespace

#endif