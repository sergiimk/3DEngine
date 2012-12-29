/*========================================================
* CCubeTexture.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "CCubeTexture.h"
#include "CD3DRenderer.h"
#include "TypeUtilities.h"
#include "CD3DRenderer.h"
#include "CRenderTarget.h"
#include "../Engine.Graphics/RendererExceptions.h"
#include "../Core.Logging/ILogger.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	void CCubeTexture::FinalConstruct(const Utils::URL &url)
	{
		mUrl = url;
	}

	//////////////////////////////////////////////////////////////////////////

	IRenderTarget* CCubeTexture::GetRenderTarget()
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCubeTexture::Load()
	{
		IDirect3DCubeTexture9* tex;
		if(D3DXCreateCubeTextureFromFileA(((CD3DRenderer*)g_Renderer)->GetDevice(), mUrl.Name.c_str(), &tex) != S_OK)
		{
			LogErrorAlways("Failed to load cube texture data from %s", mUrl.Name.c_str());
			throw ResourceException("Resource loading failed");
		}
		mTexture = tex;

		// Reload params
		D3DSURFACE_DESC desc;
		memset(&desc, 0, sizeof(D3DSURFACE_DESC));
		HR(tex->GetLevelDesc(0, &desc));

		mSurfaceDesc.Width = desc.Width;
		mSurfaceDesc.Height = desc.Height;
		mSurfaceDesc.Format = FromDXFormat(desc.Format);
		mSurfaceDesc.Type = SFC_CUBETEXTURE;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCubeTexture::Unload()
	{
		if(mRenderTarget)
			mRenderTarget->Reset();

		if(mTexture) mTexture->Release();
		mTexture = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCubeTexture::OnDeviceLost()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CCubeTexture::OnDeviceReset()
	{
	}	

	//////////////////////////////////////////////////////////////////////////

} // namespace
