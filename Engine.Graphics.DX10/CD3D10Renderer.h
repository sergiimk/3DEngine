/*========================================================
* CD3D10Renderer.h
* @author Sergey Mikhtonyuk
* @date 17 July 2009
=========================================================*/
#ifndef _CD3D10RENDERER_H__
#define _CD3D10RENDERER_H__

#include "../Engine.Graphics/Interfaces/IRenderer.h"
#include "../Core.COM/Implementations.h"

namespace DX10
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	//////////////////////////////////////////////////////////////////////////

	/// Concrete renderer based on DirectX10
	/** @ingroup DX10 */
	class NOVTABLE CD3D10Renderer : 
		public Core::SCOM::ComRootObject<>,
		public IRenderer
	{
	public:
		DECLARE_IMPLEMENTATION(CD3D10Renderer)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IRenderer)
		END_INTERFACE_MAP()

		CD3D10Renderer();
		~CD3D10Renderer();

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

		void				SetMaterial(IMaterial* material);
		IMaterial*			GetMaterial();

		void				SetTextureSet(ITextureSet* texures);
		ITextureSet*		GetTextureSet() const;

		void				SetGeometryBuffer(IMesh* mesh);
		void				DrawGeometry(IGeometry* geom);
		void				DrawFSQuad();
		void				DbgDrawBBox(const Engine::SBoundingVolume& bbox, unsigned int color);

		IMatrixStack*		GetMatrixStack(ETransformType forType) const;
		const VML::Matrix4&	GetTransform(ETransformType forType) const;

		IMaterialCallback*	GetMaterialCallback() const;
		void				SetMaterialCallback(IMaterialCallback* callback);

		ISurfaceManager*	GetSurfaceManager() const;
		IGeometryManager*	GetGeometryManager() const;
		IMaterialManager*	GetMaterialManager() const;

		//LPDIRECT3DDEVICE9	GetDevice();
		bool				InitDX(const SRendererParams& params, std::string* errorBuffer);
		bool				InitSubsystems();
		//void				ReadCaps(D3DCAPS9* pCaps, D3DPRESENT_PARAMETERS* pp);

	private:
		bool				CheckDeviceLost();
		void				OnDeviceLost();
		//void				LoadParams(D3DPRESENT_PARAMETERS& d3dpp);
		void				OnDeviceReset();

	private:
		/*SRendererParams							mParams;
		LPDIRECT3D9								mD3D;
		LPDIRECT3DDEVICE9						mD3DDevice;
		IMaterial*								mLineMat;
		IDirect3DVertexBuffer9*					mQuad;

		Core::SCOM::ComPtr<IMaterial>			mMaterial;
		Core::SCOM::ComPtr<ITextureSet>			mTextureSet;
		Core::SCOM::ComPtr<IMaterialCallback>	mMaterialCallback;

		SRendererCaps							mCaps;
		SRect									mScissorRect;
		SViewport								mViewport;
		Core::SCOM::ComPtr<IRenderTarget>		mRenderTargets[MAX_RT_NUM];
		Core::SCOM::ComPtr<IRenderTarget>		mBackBuffer;

		Core::SCOM::ComPtr<IResourceManager>	mManagers[MANAGER_NUM_MANAGERS];
		Core::SCOM::ComPtr<IMatrixStack>		mMatrixStacks[TRANSFORM_NUM_TRANSFORMS];*/
	};

} // namespace

#endif // _CD3D10RENDERER_H__