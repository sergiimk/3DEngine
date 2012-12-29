/*========================================================
* CBaseTexture.h
* @author Sergey Mikhtonyuk
* @date 22 May 2009
=========================================================*/
#ifndef _CBASETEXTURE_H__
#define _CBASETEXTURE_H__

#include "CBaseResource.h"
#include "../Engine.Graphics/Interfaces/ITexture.h"
#include "../Engine.Graphics/Interfaces/SSurfaceDesc.h"
#include "DirectX.h"
#include "managers.h"
#include "../Core.COM/Implementations.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	class CSurfaceDesc;
	class CRenderTarget;
	//////////////////////////////////////////////////////////////////////////

	/// Base class for texture implementations
	/** @ingroup DX9 */
	class NOVTABLE CBaseTexture : public CBaseResource<ITexture>
	{
	public:
		CBaseTexture() : mTexture(0), mRenderTarget(0) { }
		~CBaseTexture();

		SSurfaceDesc*			GetSurfaceParams()  { return IsLoaded() ? &mSurfaceDesc : 0; }
		ISurfaceManager*		GetManager()		{ return g_SurfaceManager; }
		IDirect3DBaseTexture9*	GetTexture()		{ ASSERT_STRICT(IsLoaded()); return mTexture; }

	protected:
		SSurfaceDesc			mSurfaceDesc;
		IDirect3DBaseTexture9*	mTexture;
		CRenderTarget*			mRenderTarget;
	};	

} // namespace

#endif	// _CBASETEXTURE_H__