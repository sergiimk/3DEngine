/*========================================================
* CRenderTarget.h
* @author Sergey Mikhtonyuk
* @date 07 May 2009
=========================================================*/
#ifndef _CRENDERTARGET_H__
#define _CRENDERTARGET_H__

#include "../Engine.Graphics/Interfaces/IRenderTarget.h"
#include "../Engine.Graphics/Interfaces/SSurfaceDesc.h"
#include "../Core.COM/Implementations.h"
#include "DirectX.h"

namespace DXRenderer
{
	using namespace Engine::Graphics;

	/// Surface that can be a target for rendering
	/** @ingroup DX9 */
	class NOVTABLE CRenderTarget : 
		public Core::SCOM::ComRootObject<>,
		public IRenderTarget
	{
	public:
		DECLARE_IMPLEMENTATION(CRenderTarget)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IRenderTarget)
		END_INTERFACE_MAP()

		CRenderTarget();
		~CRenderTarget();

		void FinalConstruct(IDirect3DSurface9* surface);
		void Reset();

		SSurfaceDesc* GetSurfaceParams();

		IDirect3DSurface9* GetSurface();

	private:
		SSurfaceDesc		mDesc;
		IDirect3DSurface9*	mSurface;
	};

} // namespace

#endif	// _CRENDERTARGET_H__