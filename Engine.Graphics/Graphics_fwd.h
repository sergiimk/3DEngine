/*========================================================
* Graphics_fwd.h
* @author Sergey Mikhtonyuk
* @date 30 April 2009
=========================================================*/
#ifndef _GRAPHICS_COMMON_FWD_H__
#define _GRAPHICS_COMMON_FWD_H__

namespace Engine
{
	namespace Graphics
	{
		class IRenderer;
		class IMatrixStack;
		class IMaterialCallback;

		class IResourceManager;
		class IMaterialManager;
		class IEffectManager;
		class IGeometryManager;
		class ISurfaceManager;

		class IGraphicsResource;
		class IResourceInternal;
		class IMaterial;
		class IEffect;
		class IEffectInstance;
		class IMesh;
		class IBuffer;
		class IGeometry;
		class ITexture;
		class IRenderTarget;

		struct SSurfaceDesc;
		struct SRendererCaps;
		struct SRendererParams;
		struct SMaterialBindings;
		struct SEffectDesc;
		struct SEffectCaps;
		struct SEffectParams;
	}
		struct SBoundingVolume;
}

#endif	// _GRAPHICS_COMMON_FWD_H__