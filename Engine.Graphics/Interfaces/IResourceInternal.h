/*============================================================================
	IResourceInternal.h: IResourceInternal interface declaration
	
	Author: Sergey Mikhtonyuk, 2008
============================================================================*/

#ifndef __IRESOURCE_INTERNAL_H__
#define __IRESOURCE_INTERNAL_H__

#include "IGraphicsResource.h"

namespace Engine
{
	namespace Graphics
	{
		/// Interface for internal use, adds Load and Unload methods which will be called in response of AddUser/RemoveUser
		/** @ingroup Graphics */
		SCOM_INTERFACE(IResourceInternal, "4eb9ced4-33f6-4528-b4ef-99f0242d950c", IGraphicsResource)
		{
		public:
			virtual void Load() = 0;
			virtual void Unload() = 0;

			virtual void OnDeviceLost() = 0;
			virtual void OnDeviceReset() = 0;
		};

	} // namespace
} // namespace

#endif