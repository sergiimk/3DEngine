/*============================================================================
	Renderer.cpp: Renderer class definition
	
	Author: Sergey Mikhtonyuk, 2008
============================================================================*/

#include "CD3DRenderer.h"
#include "CBaseMesh.h"
#include "CRenderTarget.h"
#include "CGeometryManager.h"
#include "CMaterialManager.h"
#include "CEffectManager.h"
#include "CSurfaceManager.h"
#include "TypeUtilities.h"
#include "../Core.Logging/ILogger.h"
#include "../Engine.Graphics/Objects/CMatrixStack.h"
#include "../Engine.Graphics/Objects/CMaterialCallback.h"
#include "../Engine.Graphics/Interfaces/IGeometry.h"
#include "../Engine.Graphics/Interfaces/IMaterial.h"
#include "../Engine.Graphics/Interfaces/IEffect.h"
#include "../Engine.Graphics/Interfaces/IEffectInstance.h"
#include "../Engine.Graphics/RendererExceptions.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	IRenderer*			g_Renderer = 0;
	IGeometryManager*	g_GeometryManager = 0;
	ISurfaceManager*	g_SurfaceManager = 0;
	IMaterialManager*	g_MaterialManager = 0;
	IEffectManager*		g_EffectManager = 0;
	//////////////////////////////////////////////////////////////////////////

	CD3DRenderer::CD3DRenderer()
		: mD3D(0), mD3DDevice(0), mLineMat(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CD3DRenderer::~CD3DRenderer()
	{
		Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	ERendererType CD3DRenderer::RendererType() const
	{
		return RENDERER_DX9;
	}

	//////////////////////////////////////////////////////////////////////////

	SRendererCaps* CD3DRenderer::GetRendererCaps() const
	{
		return mD3DDevice ? (SRendererCaps*)&mCaps : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	SRendererParams* CD3DRenderer::GetRendererParams() const
	{
		return mD3DDevice ? (SRendererParams*)&mParams : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3DRenderer::Init(const SRendererParams& params, std::string* errorBuffer)
	{
		LogInfoAlways("Initializing renderer");

		if(!InitDX(params, errorBuffer)) return false;
		
		if(!InitSubsystems()) return false;
		
		LogInfoAlways("Renderer initialization completed");
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::Shutdown()
	{
		// Release render targets
		for(int i = 0; i != MAX_RT_NUM; ++i)
			if(mRenderTargets[i])
				mRenderTargets[i].Release();

		// And back buffer
		mBackBuffer.Release();

		// Release line-drawing material
		if(mLineMat) 
		{
			mLineMat->RemoveUser();
			mLineMat->Release();
			mLineMat = 0;
		}

		// Release effect instance
		if(mEffectInstance)
			mEffectInstance.Release();

		// Release material
		if (mMaterial)
			mMaterial.Release();

		// Release callback
		if(mMaterialCallback)
			mMaterialCallback.Release();

		// Release managers
		for(size_t i = 0; i != MANAGER_NUM_MANAGERS; ++i)
			mManagers[i].Release();

		// Release stacks
		for(size_t i = 0; i != TRANSFORM_NUM_TRANSFORMS; ++i)
			mMatrixStacks[i].Release();

		// Release D3D objects
		if(mD3DDevice)
		{
			mD3DDevice->Release();
			mD3DDevice = 0;
		}
		if(mD3D)
		{
			mD3D->Release();
			mD3D = 0;
		}

		// Reset global variables
		g_Renderer = 0;
		g_EffectManager = 0;
		g_MaterialManager = 0;
		g_GeometryManager = 0;
		g_SurfaceManager = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::Clear(	unsigned int clearType, 
								unsigned int color, 
								float z,
								unsigned int stencil)
	{
		DWORD flags = 0;
		if(clearType & SRFC_CLEAR_COLOR) flags |= D3DCLEAR_TARGET;
		if(clearType & SRFC_CLEAR_DEPTH) flags |= D3DCLEAR_ZBUFFER;
		if(clearType & SRFC_CLEAR_STENCIL) flags |= D3DCLEAR_STENCIL;

		mD3DDevice->Clear(0, 0, flags, color, z, stencil);
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3DRenderer::BeginFrame()
	{
		if( CheckDeviceLost() ) return false;
		return SCOM_SUCCEEDED(mD3DDevice->BeginScene());
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::EndFrame()
	{
		mD3DDevice->EndScene();
		mD3DDevice->Present(0, 0, 0, 0);
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::SetRenderTarget(int index, IRenderTarget* target)
	{
		ASSERT_STRICT(index >= 0 && index < mCaps.MaxRenderTargets);
		
		mRenderTargets[index] = target;

		if(target)
		{
			// Apply target
			IDirect3DSurface9* s = ((CRenderTarget*)target)->GetSurface();
			ASSERT_STRICT(s);
			HR(mD3DDevice->SetRenderTarget(index, s));

			// Invalidate viewport
			mViewport.X = mViewport.Y = 0;
			mViewport.Width = target->GetSurfaceParams()->Width;
			mViewport.Height = target->GetSurfaceParams()->Height;
			SetViewport(mViewport);

			// Invalidate scissors
			mScissorRect = mViewport;
			SetScissorRect(mScissorRect);
		}
		else
		{
			HR(mD3DDevice->SetRenderTarget(index, 0));
		}
	}

	//////////////////////////////////////////////////////////////////////////

	IRenderTarget* CD3DRenderer::GetRenderTarget(int index) const
	{
		ASSERT_STRICT(index >= 0 && index < mCaps.MaxRenderTargets);
		return mRenderTargets[index];
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::SetViewport(const SViewport &vp)
	{
		mViewport = vp;
		
		D3DVIEWPORT9 d3dvp;
		d3dvp.X = mViewport.X;			d3dvp.Y = mViewport.Y;
		d3dvp.Width = mViewport.Width;	d3dvp.Height = mViewport.Height;
		d3dvp.MinZ = 0;					d3dvp.MaxZ = 1.0f;

		HR(mD3DDevice->SetViewport(&d3dvp));
	}

	//////////////////////////////////////////////////////////////////////////

	SViewport* CD3DRenderer::GetViewport() const
	{
		return mD3DDevice ? (SViewport*)&mViewport : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::SetScissorRect(const SRect& rect)
	{
		mScissorRect = rect;

		if(mScissorRect == mViewport)
		{
			mD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		}
		else
		{
			RECT r = { rect.X, rect.Y, rect.X + rect.Width, rect.Y + rect.Height };
			mD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
			HR(mD3DDevice->SetScissorRect(&r));
		}
	}

	//////////////////////////////////////////////////////////////////////////

	SRect* CD3DRenderer::GetScissorRect() const
	{
		return mD3DDevice ? (SRect*)&mScissorRect : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::SetMaterial(IMaterial* material, size_t effect_stage)
	{
		ASSERT_STRICT(material->IsLoaded());
		mMaterial = material;
		IEffect* pEffect = mMaterial->GetEffect(effect_stage);
		
		if(!pEffect)
		{
			mEffectInstance.Release();
			return;
		}

		mEffectInstance = mMaterial->GetEffectInstance(effect_stage);

		if(!mEffectInstance && pEffect)
		{
			// Gather instantiation caps
			SEffectCaps caps;
			mMaterialCallback->FillInstanceCaps(caps, mMaterial, pEffect);
			
			// Create effect instance
			g_EffectManager->CreateEffectInstance(pEffect, caps, mEffectInstance.wrapped());
			material->SetEffectInstance(effect_stage, mEffectInstance);
		}

		mEffectInstance->UpdateParameters();
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterial* CD3DRenderer::GetMaterial()
	{
		return mMaterial;
	}

	//////////////////////////////////////////////////////////////////////////

	IEffectInstance* CD3DRenderer::GetEffectInstance()
	{
		return mEffectInstance;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::SetGeometryBuffer(IMesh *mesh)
	{
		if(mesh->GetSubsetCount() == 0) return;

		ASSERT_STRICT(mesh);
		CBaseMesh* cmesh = static_cast<CBaseMesh*>(mesh);

		HR(mD3DDevice->SetVertexDeclaration(cmesh->GetDeclaration()));
		CIndexBuffer* ibuf = (CIndexBuffer*)cmesh->GetIndexBuffer();
		CVertexBuffer* vbuf = (CVertexBuffer*)cmesh->GetVertexBuffer();
		HR(mD3DDevice->SetStreamSource(0, vbuf->getDXBuffer(), 0, cmesh->GetVertexSize()));

		if(mesh->getPrimitiveType() == PT_INDEXED_TRIANGLE_LIST)
		{
			HR(mD3DDevice->SetIndices(ibuf->getDXBuffer()));
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::DrawGeometry(IGeometry *geom)
	{
		const IGeometry::TInterval& i = geom->GetIndexInterval();
		const IGeometry::TInterval& v = geom->GetVertexInterval();

		EPrimitiveType pt = geom->GetMesh()->getPrimitiveType();
		if(pt == PT_INDEXED_TRIANGLE_LIST)
		{
			HR(mD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, v.first, v.second, i.first, i.second / 3));
		}
		else if(pt == PT_TRIANGLE_LIST)
		{
			mD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, v.first, v.second / 3);
		}
		else if(pt == PT_TRIANGLE_STRIP)
		{
			mD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, v.first, v.second - 2);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::DrawFSQuad()
	{
		struct ScreenVertex
		{
			D3DXVECTOR3 p; // position
			D3DXVECTOR2 t; // texture coordinate
		};
		const DWORD SV_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

		float width = (float)mRenderTargets[0]->GetSurfaceParams()->Width;
		float height = (float)mRenderTargets[0]->GetSurfaceParams()->Height;

		float left = -1.0f - 0.5f / width;
		float right = 1.0f - 0.5f / width;
		float top = 1.0f + 0.5f / height;
		float bottom = -1.0f + 0.5f / height;

		float uv_left = 0.0f;
		float uv_right = 1.0f;
		float uv_top = 0.0f;
		float uv_bottom = 1.0f;

		ScreenVertex svQuad[4];

		svQuad[0].p = D3DXVECTOR3( left, top, 0.5f );
		svQuad[0].t = D3DXVECTOR2( uv_left, uv_top );

		svQuad[1].p = D3DXVECTOR3( right, top, 0.5f );
		svQuad[1].t = D3DXVECTOR2( uv_right, uv_top );

		svQuad[2].p = D3DXVECTOR3( left, bottom, 0.5f );
		svQuad[2].t = D3DXVECTOR2( uv_left, uv_bottom );

		svQuad[3].p = D3DXVECTOR3( right, bottom, 0.5f );
		svQuad[3].t = D3DXVECTOR2( uv_right, uv_bottom );

		HR(mD3DDevice->SetFVF(SV_FVF));
		HR(mD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, svQuad, sizeof( ScreenVertex )));
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::DbgDrawBBox(const Engine::SBoundingVolume& bbox, const VML::Vector4& color)
	{
		if(!bbox.IsValid()) return;

		D3DVECTOR min = { bbox.getMin().getX(), bbox.getMin().getY(), bbox.getMin().getZ() };
		D3DVECTOR max = { bbox.getMax().getX(), bbox.getMax().getY(), bbox.getMax().getZ() };

		D3DVECTOR lines[] = {
			{	min.x,	min.y,	min.z,	},
			{	max.x,	min.y,	min.z,	},
			{	max.x,	min.y,	max.z,	},
			{	min.x,	min.y,	max.z,	},
			{	min.x,	min.y,	min.z,	},

			{	min.x,	max.y,	min.z,	},
			{	max.x,	max.y,	min.z,	},
			{	max.x,	max.y,	max.z,	},
			{	min.x,	max.y,	max.z,	},
			{	min.x,	max.y,	min.z,	},

			{	min.x,	max.y,	max.z,	},
			{	min.x,	min.y,	max.z,	},
			{	max.x,	min.y,	max.z,	},
			{	max.x,	max.y,	max.z,	},
			{	max.x,	max.y,	min.z,	},
			{	max.x,	min.y,	min.z,	},
		};

		SMaterialBindings* bindings = mLineMat->GetBindings();
		bindings->addColorBinding(FXP_COLOR_DIFFUSE, color);

		SetMaterial(mLineMat, 0);

		mEffectInstance->BeginSequence();
		mEffectInstance->BeginPass(0);
		mD3DDevice->SetFVF(D3DFVF_XYZ);
		mD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 15, lines, sizeof(float) * 3);
		mEffectInstance->EndPass();
		mEffectInstance->EndSequence();
	}

	//////////////////////////////////////////////////////////////////////////

	IMatrixStack* CD3DRenderer::GetMatrixStack(ETransformType forType) const
	{
		ASSERT_STRICT((size_t)forType < TRANSFORM_NUM_TRANSFORMS);
		return mMatrixStacks[(size_t)forType];
	}

	//////////////////////////////////////////////////////////////////////////

	const VML::Matrix4& CD3DRenderer::GetTransform(ETransformType forType) const
	{
		ASSERT_STRICT(forType < TRANSFORM_NUM_TRANSFORMS);
		ASSERT_STRICT(mMatrixStacks[(size_t)forType]->Size());
		return mMatrixStacks[(size_t)forType]->GetTop();
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterialCallback* CD3DRenderer::GetMaterialCallback() const
	{
		return mMaterialCallback;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::SetMaterialCallback(IMaterialCallback* callback)
	{
		ASSERT_STRICT(callback);
		mMaterialCallback = callback;
	}

	//////////////////////////////////////////////////////////////////////////

	ISurfaceManager* CD3DRenderer::GetSurfaceManager() const
	{
		return g_SurfaceManager;
	}

	//////////////////////////////////////////////////////////////////////////

	IGeometryManager* CD3DRenderer::GetGeometryManager() const
	{
		return g_GeometryManager;
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterialManager* CD3DRenderer::GetMaterialManager() const
	{
		return g_MaterialManager;
	}

	//////////////////////////////////////////////////////////////////////////

	IEffectManager* CD3DRenderer::GetEffectManager() const
	{
		return g_EffectManager;
	}

	//////////////////////////////////////////////////////////////////////////

	LPDIRECT3DDEVICE9 CD3DRenderer::GetDevice()
	{
		return mD3DDevice;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	bool CD3DRenderer::CheckDeviceLost()
	{
		HRESULT hr;
		hr = mD3DDevice->TestCooperativeLevel();
		switch(hr)
		{
		case D3DERR_DEVICELOST:
			LogWarning("Device lost");
			Sleep(50);
			return true;
		case D3DERR_DRIVERINTERNALERROR:
			throw RendererException("Internal driver error, can't reset device");
		case D3DERR_DEVICENOTRESET:
			LogWarning("Device not reset");
			Reset();
			return false;
		default:
			return false;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::OnDeviceLost()
	{
		for(size_t i = 0; i < MANAGER_NUM_MANAGERS; ++i)
			mManagers[i]->OnDeviceLost();

		((CRenderTarget*)static_cast<IRenderTarget*>(mBackBuffer))->Reset();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3DRenderer::Reset()
	{
		LogWarning("Performing device reset");

		OnDeviceLost();

		D3DPRESENT_PARAMETERS d3dpp;
		LoadParams(d3dpp);

		HRESULT hr = mD3DDevice->Reset(&d3dpp);
		
		if(FAILED(hr)) return false;
		
		OnDeviceReset();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::OnDeviceReset()
	{
		for(size_t i = 0; i < MANAGER_NUM_MANAGERS; ++i)
			mManagers[i]->OnDeviceReset();

		IDirect3DSurface9* bb;
		HR(mD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb));
		((CRenderTarget*)static_cast<IRenderTarget*>(mBackBuffer))->FinalConstruct(bb);
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::LoadParams(D3DPRESENT_PARAMETERS &d3dpp)
	{
		memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

		d3dpp.BackBufferWidth = mParams.ScreenWidth;
		d3dpp.BackBufferHeight = mParams.ScreenHeight;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Windowed = mParams.FullScreen ? FALSE : TRUE;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.BackBufferCount = 1;
		d3dpp.hDeviceWindow = (HWND)mParams.MainWindow;

		if(mParams.FullScreen)
		{
			d3dpp.BackBufferFormat = ToDXFormat(mParams.BackBufferFormat);
			d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
			d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		}
		else
		{
			D3DDISPLAYMODE d3ddm;
			mD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
			d3dpp.BackBufferFormat = d3ddm.Format;
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		}

		ReadCaps(0, &d3dpp);
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3DRenderer::InitDX(const SRendererParams& params, std::string* errorBuffer)
	{
		LogInfoAlways("DirectX initialization");

		if((mD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		{ if(errorBuffer) *errorBuffer = "Failed to create DirectX object"; return false; }

		/*=======================================================================
		=  Fill parameters
		=======================================================================*/
		mParams = params;
		D3DPRESENT_PARAMETERS d3dpp;
		LoadParams(d3dpp);

		/*=======================================================================
		=  Choose adapter
		=======================================================================*/
		unsigned int AdapterToUse = D3DADAPTER_DEFAULT;
		D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;

		// Look for 'NVIDIA PerfHUD' adapter 
		// If it is present, override default settings
		for (unsigned int Adapter = 0; Adapter < mD3D->GetAdapterCount(); ++Adapter)  
		{ 
			D3DADAPTER_IDENTIFIER9	Identifier; 

			if(SUCCEEDED(mD3D->GetAdapterIdentifier(Adapter, 0, &Identifier)) && strstr(Identifier.Description,"PerfHUD") != 0)
			{ 
				AdapterToUse=Adapter; 
				DeviceType = D3DDEVTYPE_REF; // REF is a fake, no worries :)
				break; 
			} 
		}

		/*=======================================================================
		=  Verifying hardware support for specified formats
		=======================================================================*/
		if(	FAILED(mD3D->CheckDeviceType(AdapterToUse, DeviceType, d3dpp.BackBufferFormat, d3dpp.BackBufferFormat, d3dpp.Windowed)) )
		{ if(errorBuffer) *errorBuffer = "Hardware doesn't support specified formats"; return false; }

		/*=======================================================================
		=  Check for requested vertex processing and pure device
		=======================================================================*/
		D3DCAPS9 caps;
		if(FAILED(mD3D->GetDeviceCaps(AdapterToUse, DeviceType, &caps)))
		{ if(errorBuffer) *errorBuffer = "Failed to get device caps"; return false; }

		DWORD devBehaviorFlags = 0;
		devBehaviorFlags |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? 
			D3DCREATE_HARDWARE_VERTEXPROCESSING : 
			D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		/*=======================================================================
		=  If pure device and HW T&L supported
		=======================================================================*/
		if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE && devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		devBehaviorFlags |= D3DCREATE_PUREDEVICE;


		/*=======================================================================
		=  Create device
		=======================================================================*/
		if(FAILED(mD3D->CreateDevice(	AdapterToUse, 
										DeviceType, 
										(HWND)params.MainWindow,
										devBehaviorFlags,
										&d3dpp, &mD3DDevice)))
		{ if(errorBuffer) *errorBuffer = "Failed to create device"; return false; }

		ReadCaps(&caps, &d3dpp);

		mD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3DRenderer::InitSubsystems()
	{
		// ===== Create render target from back buffer =====
		IDirect3DSurface9* bb;
		HR(mD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb));

		CRenderTarget* rt;
		scom_new<CRenderTarget>(&rt);
		mBackBuffer = rt;
		mRenderTargets[0] = rt;
		rt->FinalConstruct(bb);
		rt->Release();

		// Create default material callback
		CMaterialCallback* clbck;
		scom_new<CMaterialCallback>(&clbck);
		clbck->FinalConstruct(this);
		mMaterialCallback = clbck;
		clbck->Release();

		// ===== Init subsystems ======
		LogInfoAlways("Initializing renderer subsystems");
		scom_new<CGeometryManager>(&g_GeometryManager, UUIDOF(IGeometryManager));
		mManagers[MANAGER_GEOMETRY] = g_GeometryManager;
		g_GeometryManager->Release();

		scom_new<CSurfaceManager>(&g_SurfaceManager, UUIDOF(ISurfaceManager));
		mManagers[MANAGER_SURFACE] = g_SurfaceManager;
		g_SurfaceManager->Release();

		scom_new<CMaterialManager>(&g_MaterialManager, UUIDOF(IMaterialManager));
		mManagers[MANAGER_MATERIAL] = g_MaterialManager;
		g_MaterialManager->Release();

		scom_new<CEffectManager>(&g_EffectManager, UUIDOF(IEffectManager));
		mManagers[MANAGER_EFFECT] = g_EffectManager;
		g_EffectManager->Release();

		for(size_t i = 0; i != TRANSFORM_NUM_TRANSFORMS; ++i)
			scom_new<CMatrixStack>(mMatrixStacks[i]);

		g_Renderer = this;

		//////////////////////////////////////////////////////////////////////////
		// Line material
		IEffect* lineEffect;

		g_MaterialManager->CreateMaterial(&mLineMat);
		g_EffectManager->FindOrLoadEffect(Utils::URL("gbuf_ubershader.fxd"), &lineEffect);

		if(!mLineMat || !lineEffect)
		{
			if(mLineMat) mLineMat->Release();
			if(lineEffect) lineEffect->Release();

			LogErrorAlways("Failed to load line drawing material");
			Shutdown();
			return false;
		}

		mLineMat->SetEffect(0, lineEffect);
		lineEffect->Release();

		mLineMat->AddUser();

		SEffectCaps caps;
		IEffectInstance* pInst;
		g_EffectManager->CreateEffectInstance(mLineMat->GetEffect(0), caps, &pInst);
		mLineMat->SetEffectInstance(0, pInst);
		pInst->Release();

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3DRenderer::ReadCaps(D3DCAPS9* pCaps, D3DPRESENT_PARAMETERS* pp)
	{
		if(pCaps)
			mCaps.MaxRenderTargets = pCaps->NumSimultaneousRTs;

		mViewport.X = mViewport.Y = 0;
		mViewport.Width = pp->BackBufferWidth;
		mViewport.Height = pp->BackBufferHeight;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
