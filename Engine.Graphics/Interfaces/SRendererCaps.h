/*========================================================
* SRendererCaps.h
* @author Sergey Mikhtonyuk
* @date 08 May 2009
=========================================================*/
#ifndef _SRENDERERCAPS_H__
#define _SRENDERERCAPS_H__

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		/// Type of the renderer
		/** @ingroup Graphics */
		enum ERendererType
		{
			RENDERER_NULL,
			RENDERER_DX9,
			RENDERER_DX10,
			RENDERER_DX11,
			RENDERER_XBOX360,
			RENDERER_PS3,
			RENDERER_OPENGL,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Transformation type
		/** @ingroup Graphics */
		enum ETransformType
		{
			TRANSFORM_WORLD,
			TRANSFORM_VIEW,
			TRANSFORM_PROJECTION,

			TRANSFORM_NUM_TRANSFORMS, // indicates number of base transforms
		};

		//////////////////////////////////////////////////////////////////////////

		enum EManagerType
		{
			MANAGER_GEOMETRY,
			MANAGER_SURFACE,
			MANAGER_MATERIAL,
			MANAGER_EFFECT,

			MANAGER_NUM_MANAGERS,
		};

		//////////////////////////////////////////////////////////////////////////

		enum ESurfaceClearType
		{
			SRFC_CLEAR_COLOR = 0x1,
			SRFC_CLEAR_DEPTH = 0x2,
			SRFC_CLEAR_STENCIL = 0x4,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Contains renderer properties that depend on used hardware
		/** @ingroup Graphics */
		struct SRendererCaps
		{
			int			MaxRenderTargets;		///< Maximum number of supported render targets
		};

	} // namespace
} // namespace

#endif	// _SRENDERERCAPS_H__