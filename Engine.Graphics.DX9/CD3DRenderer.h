/*========================================================
* CD3DRenderer.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef _D3D_RENDERER_H__
#define _D3D_RENDERER_H__

#include "../Engine.Graphics/Interfaces/IRenderer.h"
#include "../Engine.Graphics/Interfaces/SRendererParams.h"
#include "DirectX.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"

#define MAX_RT_NUM 16


namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	class CSurfaceManager;
	class CMeshManager;
	class CMaterialManager;
	class WindowRegistry;
	//////////////////////////////////////////////////////////////////////////

	/// Concrete renderer based on DirectX
	/** @ingroup DX9 */
	class NOVTABLE CD3DRenderer : 
		public Core::SCOM::ComRootObject<>,
		public IRenderer
	{
	public:
		DECLARE_IMPLEMENTATION(CD3DRenderer)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IRenderer)
		END_INTERFACE_MAP()

		CD3DRenderer();
		~CD3DRenderer();

		ERendererType		RendererType() const;
		SRendererCaps*		GetRendererCaps() const;
		SRendererParams*	GetRendererParams() const;

		bool				Init(const SRendererParams& params, std::string* errorBuffer);
		bool				Reset();
		void				Shutdown();

		void				Clear(	unsigned int clearType, 
									unsigned int color, 
									float z,
									unsigned int stencil);
		bool				BeginFrame();
		void				EndFrame();

		void				SetRenderTarget(int index, IRenderTarget* target);
		IRenderTarget*		GetRenderTarget(int index) const;

		void				SetViewport(const SViewport& vp);
		SViewport*			GetViewport() const;

		void				SetScissorRect(const SRect& rect);
		SRect*				GetScissorRect() const;

		void				SetMaterial(IMaterial* material, size_t effect_stage);
		IMaterial*			GetMaterial();
		IEffectInstance*	GetEffectInstance();

		void				SetGeometryBuffer(IMesh* mesh);
		void				DrawGeometry(IGeometry* geom);
		void				DrawFSQuad();
		void				DbgDrawBBox(const Engine::SBoundingVolume& bbox, const VML::Vector4& color);

		IMatrixStack*		GetMatrixStack(ETransformType forType) const;
		const VML::Matrix4&	GetTransform(ETransformType forType) const;

		IMaterialCallback*	GetMaterialCallback() const;
		void				SetMaterialCallback(IMaterialCallback* callback);

		ISurfaceManager*	GetSurfaceManager() const;
		IGeometryManager*	GetGeometryManager() const;
		IMaterialManager*	GetMaterialManager() const;
		IEffectManager*		GetEffectManager() const;

		LPDIRECT3DDEVICE9	GetDevice();
		bool				InitDX(const SRendererParams& params, std::string* errorBuffer);
		bool				InitSubsystems();
		void				ReadCaps(D3DCAPS9* pCaps, D3DPRESENT_PARAMETERS* pp);

	private:
		bool				CheckDeviceLost();
		void				OnDeviceLost();
		void				LoadParams(D3DPRESENT_PARAMETERS& d3dpp);
		void				OnDeviceReset();

	private:
		SRendererParams							mParams;
		LPDIRECT3D9								mD3D;
		LPDIRECT3DDEVICE9						mD3DDevice;
		IMaterial*								mLineMat;

		Core::SCOM::ComPtr<IMaterial>			mMaterial;
		Core::SCOM::ComPtr<IEffectInstance>		mEffectInstance;
		Core::SCOM::ComPtr<IMaterialCallback>	mMaterialCallback;

		SRendererCaps							mCaps;
		SRect									mScissorRect;
		SViewport								mViewport;
		Core::SCOM::ComPtr<IRenderTarget>		mRenderTargets[MAX_RT_NUM];
		Core::SCOM::ComPtr<IRenderTarget>		mBackBuffer;

		Core::SCOM::ComPtr<IResourceManager>	mManagers[MANAGER_NUM_MANAGERS];
		Core::SCOM::ComPtr<IMatrixStack>		mMatrixStacks[TRANSFORM_NUM_TRANSFORMS];
	};

} // namespace


#endif