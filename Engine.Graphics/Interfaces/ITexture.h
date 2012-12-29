/*========================================================
* ITexture.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __ITEXTURE_H__
#define __ITEXTURE_H__

#include "IResourceInternal.h"

namespace Engine
{
	namespace Graphics
	{
		/// Interface to resource that stores texture
		/** @ingroup Graphics */
		SCOM_INTERFACE(ITexture, "88556ddb-cb17-4c1a-b496-54fc953b89b9", IResourceInternal)
		{
		public:

			/// Returns description of the texture surface
			virtual SSurfaceDesc* GetSurfaceParams() = 0;

			/// Returns render target associated with this texture
			/** Note that texture should be dynamically created with SFC_RENDERTARGET type */
			virtual IRenderTarget* GetRenderTarget() = 0;

			/// Returns surface manager
			virtual ISurfaceManager* GetManager() = 0;
		};

	} // namespace
} // namespace

#endif