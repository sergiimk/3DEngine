/*========================================================
* CComponentRegistry.cpp
* @author Sergey Mikhtonyuk
* @date 29 June 2009
=========================================================*/
#include "CComponentRegistry.h"
#include "../../Core/IPluginShadow.h"
#include "../../Core/CommonPlugin.h"

#include "../Interfaces/ICmpAppearance.h"
#include "../Interfaces/ICmpSpatialNode.h"
#include "../Interfaces/ICmpPhysicalBody.h"
#include "../Interfaces/ICmpLogic.h"

#include "../Engine_classid.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CComponentRegistry::CComponentRegistry()
	{
		// Register built-in components
		/// \todo refactor to extension point

		Core::IPluginShadow* myShadow = Core::CommonPlugin::Instance->PluginShadow();

		RegisterComponent(myShadow, CLSID_CCmpAppearance);
		RegisterComponent(myShadow, CLSID_CCmpSpatialNode);
		RegisterComponent(myShadow, CLSID_CCmpPhysicalBody);
	}

	//////////////////////////////////////////////////////////////////////////

	void CComponentRegistry::RegisterComponent(Core::IPluginShadow *plugin, SCOM_RIID clsid)
	{
		mComponentFactories.insert(std::make_pair(clsid, plugin));
	}

	//////////////////////////////////////////////////////////////////////////

	Core::SCOM::HResult CComponentRegistry::CreateComponent(SCOM_RIID clsid, IComponent** pComp)
	{
		if(!pComp) 
			return SCOM_E_POINTER;

		*pComp = 0;

		TComponentReg::const_iterator it = mComponentFactories.find(clsid);
		
		if(it == mComponentFactories.end())
			return SCOM_E_FAIL;

		return it->second->CreateInstance(clsid, UUID_PPV(IComponent, pComp));
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace