/*========================================================
* IRenderTarget.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef _IRENDER_TARGET_H__
#define _IRENDER_TARGET_H__

#include "../Graphics_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	namespace Graphics
	{
		/// Interface for all objects that can be the destination of rendering operation
		/** @ingroup Graphics */
		SCOM_INTERFACE(IRenderTarget, "eff7a535-2d69-4d58-a8c8-97dd0e64b7bd", Core::SCOM::IUnknown)
		{
		public:
			/// Returns params of the surface
			virtual SSurfaceDesc* GetSurfaceParams() = 0;
		};

	} // namespace
} // namespace

#endif