/*========================================================
* CRenderTarget.cpp
* @author Sergey Mikhtonyuk
* @date 07 May 2009
=========================================================*/
#include "CRenderTarget.h"
#include "TypeUtilities.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	
	CRenderTarget::CRenderTarget()
		: mSurface(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CRenderTarget::FinalConstruct(IDirect3DSurface9 *surface)
	{
		mSurface = surface;

		D3DSURFACE_DESC desc;
		memset(&desc, 0, sizeof(D3DSURFACE_DESC));
		HR(mSurface->GetDesc(&desc));

		mDesc.Width = desc.Width;
		mDesc.Height = desc.Height;
		mDesc.Format = FromDXFormat(desc.Format);
		mDesc.Type = SFC_RENDERTARGET;
	}

	//////////////////////////////////////////////////////////////////////////

	CRenderTarget::~CRenderTarget()
	{
		Reset();
	}

	//////////////////////////////////////////////////////////////////////////

	void CRenderTarget::Reset()
	{
		if(mSurface)
		{
			mSurface->Release();
			mSurface = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	SSurfaceDesc* CRenderTarget::GetSurfaceParams()
	{
		if(!mSurface) return 0;
		return &mDesc;
	}

	//////////////////////////////////////////////////////////////////////////

	IDirect3DSurface9* CRenderTarget::GetSurface()
	{ 
		ASSERT_STRICT(mSurface); 
		return mSurface; 
	}

} // namespace