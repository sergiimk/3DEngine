/*========================================================
* IRenderer.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef _IRENDERER_H__
#define _IRENDERER_H__

#include "../Graphics_fwd.h"
#include "../../Core.Math/VML_fwd.h"
#include "../../Core.COM/Interfaces.h"
#include "SRendererCaps.h"
#include "SViewport.h"
#include <string>

namespace Engine
{
	namespace Graphics
	{
		/// Base interface to the graphics API
		/** @ingroup Graphics */
		SCOM_INTERFACE(IRenderer, "3710416a-13a6-4b00-8c4a-7683661c747f", Core::SCOM::IUnknown)
		{
		public:

			/// Returns type of this renderer
			virtual ERendererType RendererType() const = 0;

			/// Returns the renderer parameters that depend on used hardware
			virtual SRendererCaps* GetRendererCaps() const = 0;

			/// Returns renderer params, call reset after modifying to apply them
			virtual SRendererParams* GetRendererParams() const = 0;



			/// Initializes the renderer
			virtual bool Init(const SRendererParams& params, std::string* errorBuffer = 0) = 0;

			/// Resets device (applies new params)
			virtual bool Reset() = 0;

			/// Shuts down the renderer
			virtual void Shutdown() = 0;



			/// Clears current surface data
			/** @param clearType combination of ESurfaceClearType
			 *  @param color color in XRGB format 
			 *  @param z depth buffer value [0; 1]
			 *  @param stencil stencil buffer value */
			virtual void Clear(unsigned int clearType, unsigned int color = 0xffffffff, float z = 1.0f, unsigned int stencil = 0x0) = 0;

			/// Should be called before frame rendering
			/** @return true if succeeded */
			virtual bool BeginFrame() = 0;

			/// Presents rendered scene at the end of the frame
			virtual void EndFrame() = 0;



			/// Sets current render target
			/** @param index index of the render target for MRT rendering, verify support through caps first */
			virtual void SetRenderTarget(int index, IRenderTarget* target) = 0;

			/// Returns current render target
			/** @param index index of the render target */
			virtual IRenderTarget* GetRenderTarget(int index) const = 0;



			/// Sets current viewport
			/** viewport defines the region of target surface that will be used for rendering.
			  * NOTE: Viewport and scissor rects are invalidated after any render target changes */
			virtual void SetViewport(const SViewport& vp) = 0;

			/// Returns current viewport
			virtual SViewport* GetViewport() const = 0;



			/// Sets current scissor rect
			/** NOTE: Viewport and scissor rects are invalidated after any render target changes */
			virtual void SetScissorRect(const SRect& rect) = 0;

			/// Returns current scissor rect
			virtual SRect* GetScissorRect() const = 0;



			/// Applies material for rendering with specified effect stage
			virtual void SetMaterial(IMaterial* material, size_t effect_stage = 0) = 0;

			/// Returns current material
			virtual IMaterial* GetMaterial() = 0;

			/// Returns current effect instance
			virtual IEffectInstance* GetEffectInstance() = 0;



			/// Sets current geometry buffer
			virtual void SetGeometryBuffer(IMesh* mesh) = 0;

			/// Draws geometry subset specified by geometry object
			virtual void DrawGeometry(IGeometry* geom) = 0;

			/// Draws full-screen quadrilateral (for post-processing needs)
			virtual void DrawFSQuad() = 0;



			/// Draws bounding box using line primitives
			virtual void DbgDrawBBox(const SBoundingVolume& bbox, const VML::Vector4& color) = 0;



			/// Returns the matrix stack where you should push all your transforms
			virtual IMatrixStack* GetMatrixStack(ETransformType forType) const = 0;

			/// Same as getting the top matrix of the stack
			virtual const VML::Matrix4& GetTransform(ETransformType forType) const = 0;



			/// Returns current material callback
			virtual IMaterialCallback* GetMaterialCallback() const = 0;

			/// Sets new material callback
			virtual void SetMaterialCallback(IMaterialCallback* callback) = 0;



			/// Returns texture manager
			virtual ISurfaceManager*	GetSurfaceManager() const = 0;

			/// Returns geometry manager
			virtual IGeometryManager*	GetGeometryManager() const = 0;

			/// Returns material manager
			virtual IMaterialManager*	GetMaterialManager() const = 0;

			/// Returns effect manager
			virtual IEffectManager*		GetEffectManager() const = 0;
		};

	} // namespace
} // namespace

#endif