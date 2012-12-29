/*========================================================
* CD3D10Renderer.cpp
* @author Sergey Mikhtonyuk
* @date 17 July 2009
=========================================================*/
#include "CD3D10Renderer.h"
//#include "CBaseMesh.h"
//#include "CRenderTarget.h"
//#include "CGeometryManager.h"
//#include "CMaterialManager.h"
//#include "CSurfaceManager.h"
//#include "TypeUtilities.h"
//#include "../Core.Logging/ILogger.h"
#include "../Engine.Graphics/Objects/CMatrixStack.h"
//#include "../Engine.Graphics/Objects/CMaterialCallback.h"
//#include "../Engine.Graphics/Interfaces/IGeometry.h"
//#include "../Engine.Graphics/Interfaces/IMaterial.h"
//#include "../Engine.Graphics/RendererExceptions.h"

namespace DX10
{
	//////////////////////////////////////////////////////////////////////////
	/*IRenderer*			g_Renderer = 0;
	IGeometryManager*	g_GeometryManager = 0;
	ISurfaceManager*	g_SurfaceManager = 0;
	IMaterialManager*	g_MaterialManager = 0;*/
	//////////////////////////////////////////////////////////////////////////

	CD3D10Renderer::CD3D10Renderer()
		//: mD3D(0), mD3DDevice(0), mLineMat(0), mQuad(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CD3D10Renderer::~CD3D10Renderer()
	{
		Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	ERendererType CD3D10Renderer::RendererType() const
	{
		return RENDERER_DX10;
	}

	//////////////////////////////////////////////////////////////////////////

	SRendererCaps* CD3D10Renderer::GetRendererCaps() const
	{
		//return mD3DDevice ? (SRendererCaps*)&mCaps : 0;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	SRendererParams* CD3D10Renderer::GetRendererParams() const
	{
		//return mD3DDevice ? (SRendererParams*)&mParams : 0;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3D10Renderer::Init(const SRendererParams& params, std::string* errorBuffer)
	{
		/*LogInfoAlways("Initializing renderer");

		if(!InitDX(params, errorBuffer)) return false;

		if(!InitSubsystems()) return false;

		LogInfoAlways("Renderer initialization completed");*/

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::Shutdown()
	{
		/*// Release render targets
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

		// Release material
		if (mMaterial)
			mMaterial.Release();

		// Release texture set
		if (mTextureSet)
			mTextureSet.Release();

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
		if(mQuad)
		{
			mQuad->Release();
			mQuad = 0;
		}
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
		g_MaterialManager = 0;
		g_GeometryManager = 0;
		g_SurfaceManager = 0;*/
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::Clear(	unsigned int clearType, 
								unsigned int color, 
								float z,
								unsigned int stencil)
	{
		/*DWORD flags = 0;
		if(clearType & SRFC_CLEAR_COLOR) flags |= D3DCLEAR_TARGET;
		if(clearType & SRFC_CLEAR_DEPTH) flags |= D3DCLEAR_ZBUFFER;
		if(clearType & SRFC_CLEAR_STENCIL) flags |= D3DCLEAR_STENCIL;

		mD3DDevice->Clear(0, 0, flags, color, z, stencil);*/
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3D10Renderer::BeginFrame()
	{
		//if( CheckDeviceLost() ) return false;
		//return SCOM_SUCCEEDED(mD3DDevice->BeginScene());
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::EndFrame()
	{
		//mD3DDevice->EndScene();
		//mD3DDevice->Present(0, 0, 0, 0);
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetRenderTarget(int index, IRenderTarget* target)
	{
		//ASSERT_STRICT(index >= 0 && index < mCaps.MaxRenderTargets);

		//mRenderTargets[index] = target;

		//if(target)
		//{
		//	// Apply target
		//	IDirect3DSurface9* s = ((CRenderTarget*)target)->GetSurface();
		//	ASSERT_STRICT(s);
		//	HR(mD3DDevice->SetRenderTarget(index, s));

		//	// Invalidate viewport
		//	mViewport.X = mViewport.Y = 0;
		//	mViewport.Width = target->GetSurfaceParams()->Width;
		//	mViewport.Height = target->GetSurfaceParams()->Height;
		//	SetViewport(mViewport);

		//	// Invalidate scissors
		//	mScissorRect = mViewport;
		//	SetScissorRect(mScissorRect);
		//}
	}

	//////////////////////////////////////////////////////////////////////////

	IRenderTarget* CD3D10Renderer::GetRenderTarget(int index) const
	{
		/*ASSERT_STRICT(index >= 0 && index < mCaps.MaxRenderTargets);
		return mRenderTargets[index];*/
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetViewport(const SViewport &vp)
	{
		/*mViewport = vp;

		D3DVIEWPORT9 d3dvp;
		d3dvp.X = mViewport.X;			d3dvp.Y = mViewport.Y;
		d3dvp.Width = mViewport.Width;	d3dvp.Height = mViewport.Height;
		d3dvp.MinZ = 0;					d3dvp.MaxZ = 1.0f;

		HR(mD3DDevice->SetViewport(&d3dvp));*/
	}

	//////////////////////////////////////////////////////////////////////////

	SViewport* CD3D10Renderer::GetViewport() const
	{
		//return mD3DDevice ? (SViewport*)&mViewport : 0;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetScissorRect(const SRect& rect)
	{
		/*mScissorRect = rect;

		if(mScissorRect == mViewport)
		{
			mD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		}
		else
		{
			RECT r = { rect.X, rect.Y, rect.X + rect.Width, rect.Y + rect.Height };
			mD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
			HR(mD3DDevice->SetScissorRect(&r));
		}*/
	}

	//////////////////////////////////////////////////////////////////////////

	SRect* CD3D10Renderer::GetScissorRect() const
	{
		//return mD3DDevice ? (SRect*)&mScissorRect : 0;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetMaterial(IMaterial* material)
	{
		/*mMaterial = material;
		mMaterial->Update(MUPD_ALL);*/
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterial* CD3D10Renderer::GetMaterial()
	{
		//return mMaterial;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetTextureSet(ITextureSet *texures)
	{
		//mTextureSet = texures;
	}

	//////////////////////////////////////////////////////////////////////////

	ITextureSet* CD3D10Renderer::GetTextureSet() const
	{
		//return mTextureSet;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetGeometryBuffer(IMesh *mesh)
	{
		/*ASSERT_STRICT(mesh);
		CBaseMesh* cmesh = static_cast<CBaseMesh*>(mesh);

		HR(mD3DDevice->SetVertexDeclaration(cmesh->GetDeclaration()));
		HR(mD3DDevice->SetIndices(cmesh->GetIndexBuffer()));
		HR(mD3DDevice->SetStreamSource(0, cmesh->GetVertexBuffer(), 0, cmesh->GetVertexSize()));*/
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::DrawGeometry(IGeometry *geom)
	{
		/*const IGeometry::TInterval& f = geom->GetFaceInterval();
		const IGeometry::TInterval& v = geom->GetVertexInterval();

		HR(mD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, v.first, v.second, f.first * 3, f.second));*/
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::DrawFSQuad()
	{
		//struct PPVERT
		//{
		//	float x, y, z, rhw;
		//	float tu, tv;
		//};


		//if(!mQuad)
		//{
		//	float right = (float)mParams.ScreenWidth;
		//	float bottom = (float)mParams.ScreenHeight;

		//	//256 by 256 rectangle matching 256 by 256 texture
		//	PPVERT Quad[4] =
		//	{
		//		{ -0.5f,			-0.5f,          1.0f, 1.0f, 0.0f, 0.0f },
		//		{ right - 0.5f,		-0.5,           1.0f, 1.0f, 1.0f, 0.0f },
		//		{ -0.5,				bottom - 0.5f,	1.0f, 1.0f, 0.0f, 1.0f },
		//		{ right - 0.5f,		bottom - 0.5f,	1.0f, 1.0f, 1.0f, 1.0f }
		//	};

		//	// Copy data
		//	HR(mD3DDevice->CreateVertexBuffer(sizeof(PPVERT) * 4, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &mQuad, 0));
		//	void* data;
		//	HR(mQuad->Lock(0, 0, &data, D3DLOCK_DISCARD));
		//	memcpy(data, Quad, sizeof(PPVERT) * 4);
		//	mQuad->Unlock();
		//}

		//HR(mD3DDevice->SetStreamSource(0, mQuad, 0, sizeof(PPVERT)));
		//HR(mD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1));
		//HR(mD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2));
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::DbgDrawBBox(const Engine::SBoundingVolume& bbox, unsigned int color)
	{
		/*D3DVECTOR min = { bbox.getMin().getX(), bbox.getMin().getY(), bbox.getMin().getZ() };
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

		SetMaterial(mLineMat);
		mLineMat->BeginSequence();
		mLineMat->BeginPass(0);
		mD3DDevice->SetFVF(D3DFVF_XYZ);
		mD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 15, lines, sizeof(float) * 3);
		mLineMat->EndPass();
		mLineMat->EndSequence();*/
	}

	//////////////////////////////////////////////////////////////////////////

	IMatrixStack* CD3D10Renderer::GetMatrixStack(ETransformType forType) const
	{
		/*ASSERT_STRICT((size_t)forType < TRANSFORM_NUM_TRANSFORMS);
		return mMatrixStacks[(size_t)forType];*/
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	const VML::Matrix4& CD3D10Renderer::GetTransform(ETransformType forType) const
	{
		/*ASSERT_STRICT(forType < TRANSFORM_NUM_TRANSFORMS);
		ASSERT_STRICT(mMatrixStacks[(size_t)forType]->Size());
		return mMatrixStacks[(size_t)forType]->GetTop();*/
		return VML::Matrix4::identity();
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterialCallback* CD3D10Renderer::GetMaterialCallback() const
	{
		//return mMaterialCallback;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::SetMaterialCallback(IMaterialCallback* callback)
	{
		/*ASSERT_STRICT(callback);
		mMaterialCallback = callback;*/
	}

	//////////////////////////////////////////////////////////////////////////

	ISurfaceManager* CD3D10Renderer::GetSurfaceManager() const
	{
		//return g_SurfaceManager;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	IGeometryManager* CD3D10Renderer::GetGeometryManager() const
	{
		//return g_GeometryManager;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterialManager* CD3D10Renderer::GetMaterialManager() const
	{
		//return g_MaterialManager;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	//LPDIRECT3DDEVICE9 CD3D10Renderer::GetDevice()
	//{
		//return mD3DDevice;
	//}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	bool CD3D10Renderer::CheckDeviceLost()
	{
		/*HRESULT hr;
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
		}*/
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::OnDeviceLost()
	{
		/*for(size_t i = 0; i < MANAGER_NUM_MANAGERS; ++i)
			mManagers[i]->OnDeviceLost();

		((CRenderTarget*)static_cast<IRenderTarget*>(mBackBuffer))->Reset();*/
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3D10Renderer::Reset()
	{
		/*LogWarning("Performing device reset");

		OnDeviceLost();

		D3DPRESENT_PARAMETERS d3dpp;
		LoadParams(d3dpp);

		HRESULT hr = mD3DDevice->Reset(&d3dpp);

		if(FAILED(hr)) return false;

		OnDeviceReset();*/
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CD3D10Renderer::OnDeviceReset()
	{
		/*for(size_t i = 0; i < MANAGER_NUM_MANAGERS; ++i)
			mManagers[i]->OnDeviceReset();

		IDirect3DSurface9* bb;
		HR(mD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb));
		((CRenderTarget*)static_cast<IRenderTarget*>(mBackBuffer))->FinalConstruct(bb);*/
	}

	//////////////////////////////////////////////////////////////////////////

	/*void CD3D10Renderer::LoadParams(D3DPRESENT_PARAMETERS &d3dpp)
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
	}*/

	//////////////////////////////////////////////////////////////////////////

	bool CD3D10Renderer::InitDX(const SRendererParams& params, std::string* errorBuffer)
	{
		/*LogInfoAlways("DirectX initialization");

		if((mD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		{ if(errorBuffer) *errorBuffer = "Failed to create DirectX object"; return false; }

		//////////////////////////////////////////////////////////////////////////
		// Fill parameters
		//////////////////////////////////////////////////////////////////////////
		mParams = params;
		D3DPRESENT_PARAMETERS d3dpp;
		LoadParams(d3dpp);

		//////////////////////////////////////////////////////////////////////////
		// Choose adapter
		//////////////////////////////////////////////////////////////////////////
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

		//////////////////////////////////////////////////////////////////////////
		// Verifying hardware support for specified formats
		//////////////////////////////////////////////////////////////////////////
		if(	FAILED(mD3D->CheckDeviceType(AdapterToUse, DeviceType, d3dpp.BackBufferFormat, d3dpp.BackBufferFormat, d3dpp.Windowed)) )
		{ if(errorBuffer) *errorBuffer = "Hardware doesn't support specified formats"; return false; }

		//////////////////////////////////////////////////////////////////////////
		// Check for requested vertex processing and pure device
		//////////////////////////////////////////////////////////////////////////
		D3DCAPS9 caps;
		if(FAILED(mD3D->GetDeviceCaps(AdapterToUse, DeviceType, &caps)))
		{ if(errorBuffer) *errorBuffer = "Failed to get device caps"; return false; }

		DWORD devBehaviorFlags = 0;
		devBehaviorFlags |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? 
			D3DCREATE_HARDWARE_VERTEXPROCESSING : 
			D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		//////////////////////////////////////////////////////////////////////////
		// If pure device and HW T&L supported
		//////////////////////////////////////////////////////////////////////////
		if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE && devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
			devBehaviorFlags |= D3DCREATE_PUREDEVICE;


		//////////////////////////////////////////////////////////////////////////
		// Create device
		//////////////////////////////////////////////////////////////////////////
		if(FAILED(mD3D->CreateDevice(	AdapterToUse, 
			DeviceType, 
			(HWND)params.MainWindow,
			devBehaviorFlags,
			&d3dpp, &mD3DDevice)))
		{ if(errorBuffer) *errorBuffer = "Failed to create device"; return false; }

		ReadCaps(&caps, &d3dpp);

		mD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
*/
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CD3D10Renderer::InitSubsystems()
	{
		/*// ===== Create render target from back buffer =====
		IDirect3DSurface9* bb;
		HR(mD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb));

		CRenderTarget* rt = CRenderTarget::_ObjectClass::CreateInstance();
		mBackBuffer = rt;
		mRenderTargets[0] = rt;
		rt->FinalConstruct(bb);		

		// Create default material callback
		CMaterialCallback* clbck = CMaterialCallback::_ObjectClass::CreateInstance();
		clbck->FinalConstruct(this);
		mMaterialCallback = clbck;

		// ===== Init subsystems ======
		LogInfoAlways("Initializing renderer subsystems");
		g_GeometryManager = CGeometryManager::_ObjectClass::CreateInstance();
		mManagers[0] = g_GeometryManager;

		g_SurfaceManager = CSurfaceManager::_ObjectClass::CreateInstance();
		mManagers[1] = g_SurfaceManager;

		g_MaterialManager = CMaterialManager::_ObjectClass::CreateInstance();
		mManagers[2] = g_MaterialManager;

		for(size_t i = 0; i != TRANSFORM_NUM_TRANSFORMS; ++i)
			mMatrixStacks[i] = CMatrixStack::_ObjectClass::CreateInstance();

		g_Renderer = this;

		// Debug line material
		g_MaterialManager->FindOrLoadMaterial(Utils::URL("../Resources/Meshes/Materials/solid_color.xml"), &mLineMat);
		if(!mLineMat)
		{
			LogErrorAlways("Failed to load line drawing material");
			Shutdown();
			return false;
		}
		mLineMat->AddUser();
		*/
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	/*void CD3D10Renderer::ReadCaps(D3DCAPS9* pCaps, D3DPRESENT_PARAMETERS* pp)
	{
		if(pCaps)
			mCaps.MaxRenderTargets = pCaps->NumSimultaneousRTs;

		mViewport.X = mViewport.Y = 0;
		mViewport.Width = pp->BackBufferWidth;
		mViewport.Height = pp->BackBufferHeight;
	}*/

	//////////////////////////////////////////////////////////////////////////

} // namespace
