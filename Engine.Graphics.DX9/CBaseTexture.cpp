/*========================================================
* CBaseTexture.cpp
* @author Sergey Mikhtonyuk
* @date 22 May 2009
=========================================================*/
#include "CBaseTexture.h"
#include "CSurfaceManager.h"
#include "CRenderTarget.h"
#include "../Core.Logging/ILogger.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CBaseTexture::~CBaseTexture()
	{
		if(g_SurfaceManager)
			((CSurfaceManager*)g_SurfaceManager)->CloseResourceHandle(this);

		if(mRenderTarget) 
			mRenderTarget->Release();

		ASSERT_SOFT(mTexture == 0);
		if(mRefs)
			LogErrorAlways("[Memory leak] Texture %s still was loaded on release, missing RemoveUser call", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace