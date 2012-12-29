/*========================================================
* CMaterialManager.h
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#ifndef __CMATERIAL_MANAGER_H__
#define __CMATERIAL_MANAGER_H__


#include "../Engine.Graphics/Interfaces/IMaterialManager.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"
#include <hash_map>

namespace DXRenderer
{
	using namespace Engine::Graphics;

	/// Concrete Material Manager, for internal use only
	/** @ingroup DX9 */
	class NOVTABLE CMaterialManager : 
		public Core::SCOM::ComRootObject<>,
		public IMaterialManager
	{
	public:
		DECLARE_IMPLEMENTATION(CMaterialManager)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IMaterialManager)
			INTERFACE_ENTRY(IResourceManager)
		END_INTERFACE_MAP()

		CMaterialManager();
		~CMaterialManager();

		void		FindOrLoadMaterial(const Utils::URL &url, IMaterial** outMaterial);
		void		CreateMaterial(IMaterial** outMaterial);
		void		GetDefaultMaterial(IMaterial** outMaterial);

		void		CloseResourceHandle(IMaterial* mat);

		void		OnDeviceLost();
		void		OnDeviceReset();

	private:

		typedef std::hash_map<std::string, IMaterial*>	MaterialMap;
		typedef MaterialMap::iterator					MaterialMapIter;
		typedef MaterialMap::const_iterator				MaterialMapCIter;

		MaterialMap						mMaterials;
		Core::SCOM::ComPtr<IMaterial>	mDefaultMaterial;
	};	

} // namespace

#endif