/*========================================================
* ITextureManager.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __ISURFACE_MANAGER_H__
#define __ISURFACE_MANAGER_H__

#include "IResourceManager.h"
#include "../../Core.Utils/URL.h"


namespace Engine
{
	namespace Graphics
	{
		/// Interface for managing the textures and render targets
		/** @ingroup Graphics */
		SCOM_INTERFACE(ISurfaceManager, "c18cbd6c-9dde-433d-92cb-c0e2aee94b1f", IResourceManager)
		{
		public:
			/// Tries to find and then to load texture
			virtual void FindOrLoadTexture(const Utils::URL &url, ITexture** outTex) = 0;

			/// Tries to find and then to load cube texture
			virtual void FindOrLoadCubeTexture(const Utils::URL &url, ITexture** outTex) = 0;

			/// Creates new texture (that can be used as render targets)
			/** New texture is not placed to the manager cache so will not be shared
			 *  @param sdesc description of the new surface */
			virtual void CreateNewTexture(const SSurfaceDesc& sdesc, ITexture** outTex) = 0;

			/// Saves texture to specified file
			virtual void SaveTextureToFile(ITexture* ptex, const char* file) = 0;
		};

	} // namespace
} // namespace

#endif // __ISURFACE_MANAGER_H__