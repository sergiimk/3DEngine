/*========================================================
* CCubeTexture.h
* @author Sergey Mikhtonyuk
* @date 22 May 2009
=========================================================*/
#ifndef _CCUBETEXTURE_H__
#define _CCUBETEXTURE_H__

#include "CBaseTexture.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	class CSurfaceDesc;
	class CRenderTarget;
	//////////////////////////////////////////////////////////////////////////


	/// Concrete class of texture
	/** @ingroup DX9 */
	class NOVTABLE CCubeTexture : 
		public Core::SCOM::ComRootObject<>,
		public CBaseTexture
	{
	public:
		DECLARE_IMPLEMENTATION(CCubeTexture)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ITexture)
			INTERFACE_ENTRY(IResourceInternal)
			INTERFACE_ENTRY(IGraphicsResource)
		END_INTERFACE_MAP()

		/// Ctor for textures from file
		void FinalConstruct(const Utils::URL &url);

		IRenderTarget*		GetRenderTarget();

		void				Load();
		void				Unload();
		void				OnDeviceLost();
		void				OnDeviceReset();
	};	

} // namespace

#endif	// _CCUBETEXTURE_H__