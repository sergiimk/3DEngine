/*========================================================
* CTexture.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "CTexture.h"
#include "CD3DRenderer.h"
#include "TypeUtilities.h"
#include "CD3DRenderer.h"
#include "CRenderTarget.h"
#include "../Engine.Graphics/RendererExceptions.h"
#include "../Core.Logging/ILogger.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
		
	void CTexture::FinalConstruct(const Utils::URL &url)
	{
		mUrl = url;
	}

	//////////////////////////////////////////////////////////////////////////

	void CTexture::FinalConstruct(const SSurfaceDesc &desc)
	{
		mSurfaceDesc = desc;
		LogTrace("Texture resource created: %s", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	IRenderTarget* CTexture::GetRenderTarget()
	{
		ASSERT_STRICT(IsLoaded());
		if(!IsLoaded()) return 0;

		ASSERT_SOFT(mSurfaceDesc.Type == SFC_RENDERTARGET);
		if(mSurfaceDesc.Type != SFC_RENDERTARGET) 
		{
			LogErrorAlways("Only dynamicaly-created textures can be used as render targets");
			return 0;
		}

		if(!mRenderTarget)
		{
			IDirect3DSurface9* surface;
			HR(((IDirect3DTexture9*)mTexture)->GetSurfaceLevel(0, &surface));

			scom_new<CRenderTarget>(&mRenderTarget);
			mRenderTarget->FinalConstruct(surface);
		}

		return mRenderTarget;
	}

	//////////////////////////////////////////////////////////////////////////

	void CTexture::Load()
	{
		if(mUrl.Name.length()) // Load surface from file?
		{
			IDirect3DTexture9* tex;
			if(D3DXCreateTextureFromFileA(((CD3DRenderer*)g_Renderer)->GetDevice(), mUrl.Name.c_str(), &tex) != S_OK)
			{
				LogErrorAlways("Failed to load texture data from %s", mUrl.Name.c_str());
				throw ResourceException("Resource loading failed");
			}
			mTexture = tex;

			// Reload params
			D3DSURFACE_DESC desc;
			memset(&desc, 0, sizeof(D3DSURFACE_DESC));
			HR(((IDirect3DTexture9*)mTexture)->GetLevelDesc(0, &desc));

			mSurfaceDesc.Width = desc.Width;
			mSurfaceDesc.Height = desc.Height;
			mSurfaceDesc.Format = FromDXFormat(desc.Format);
			mSurfaceDesc.Type = SFC_TEXTURE;
		}
		else // Create dynamic texture
		{
			LPDIRECT3DDEVICE9 _device = ((CD3DRenderer*)g_Renderer)->GetDevice();

			DWORD usage = 0;
			if(mSurfaceDesc.Type == SFC_TEXTURE)			usage = D3DUSAGE_DYNAMIC;
			else if (mSurfaceDesc.Type == SFC_RENDERTARGET)	usage = D3DUSAGE_RENDERTARGET;

			IDirect3DTexture9* tex;
			HR(_device->CreateTexture(	mSurfaceDesc.Width,
										mSurfaceDesc.Height,
										1,
										usage,
										ToDXFormat(mSurfaceDesc.Format),
										D3DPOOL_DEFAULT,
										&tex,
										0 ));
			mTexture = tex;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CTexture::Unload()
	{
		if(mRenderTarget)
			mRenderTarget->Reset();

		if(mTexture) mTexture->Release();
		mTexture = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CTexture::OnDeviceLost()
	{
		if(!mUrl.Name.length() && IsLoaded()) // Dynamic texture?
		{
			Unload();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CTexture::OnDeviceReset()
	{
		if(!mUrl.Name.length() && IsLoaded()) // Dynamic texture?
		{
			Load();

			if(mRenderTarget)
			{
				IDirect3DSurface9* surface;
				HR(((IDirect3DTexture9*)mTexture)->GetSurfaceLevel(0, &surface));
				mRenderTarget->FinalConstruct(surface);
			}
		}
	}	

	//////////////////////////////////////////////////////////////////////////

} // namespace
