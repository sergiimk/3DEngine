/*========================================================
* CTextureManager.h
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#ifndef __CSURFACE_MANAGER_H__
#define __CSURFACE_MANAGER_H__

#include "../Engine.Graphics/Interfaces/ISurfaceManager.h"
#include "../Core.COM/Implementations.h"
#include <hash_map>

namespace DXRenderer
{
	using namespace Engine::Graphics;

	/// Concrete surface manager
	/** @ingroup DX9 */
	class NOVTABLE CSurfaceManager : 
		public Core::SCOM::ComRootObject<>,
		public ISurfaceManager
	{
	public:
		DECLARE_IMPLEMENTATION(CSurfaceManager)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ISurfaceManager)
			INTERFACE_ENTRY(IResourceManager)
		END_INTERFACE_MAP()

		CSurfaceManager();
		~CSurfaceManager();

		void		FindOrLoadTexture(const Utils::URL &url, ITexture** outTex);
		void		FindOrLoadCubeTexture(const Utils::URL &url, ITexture** outTex);
		void		CreateNewTexture(const SSurfaceDesc& sdesc, ITexture** outTex);
		void		SaveTextureToFile(ITexture* ptex, const char* file);

		void		CloseResourceHandle(ITexture* tex);

		void		OnDeviceLost();
		void		OnDeviceReset();

	private:
		typedef std::hash_map<std::string, ITexture*> TextureMap;
		typedef TextureMap::iterator TextureMapIter;
		typedef std::vector<ITexture*> TDTexContainer;

		TextureMap mTextures;
		 TDTexContainer mDynamicTextures;
	};

} // namespace

#endif // __CSURFACE_MANAGER_H__