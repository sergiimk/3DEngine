/*========================================================
* CTexture.h
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__

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
	class NOVTABLE CTexture : 
		public Core::SCOM::ComRootObject<>,
		public CBaseTexture
	{
	public:
		DECLARE_IMPLEMENTATION(CTexture)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ITexture)
			INTERFACE_ENTRY(IResourceInternal)
			INTERFACE_ENTRY(IGraphicsResource)
		END_INTERFACE_MAP()

		/// Ctor for textures from file
		void FinalConstruct(const Utils::URL &url);

		/// Ctor for dynamic textures
		void FinalConstruct(const SSurfaceDesc &desc);

		IRenderTarget*		GetRenderTarget();

		void				Load();
		void				Unload();
		void				OnDeviceLost();
		void				OnDeviceReset();
	};	

} // namespace

#endif