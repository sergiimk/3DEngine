/*========================================================
* CComponentRegistry.h
* @author Sergey Mikhtonyuk
* @date 29 June 2009
=========================================================*/
#ifndef _CCOMPONENTREGISTRY_H__
#define _CCOMPONENTREGISTRY_H__

#include "../Interfaces/IComponentRegistry.h"
#include "../../Core.COM/Implementations.h"
#include <functional>
#include <hash_map>
#include "../../Core.Utils/GuidHashCmp.h"

namespace Engine
{

	/// Implementation of component registry
	/** @ingroup Engine */
	class NOVTABLE CComponentRegistry : 
		public Core::SCOM::ComRootObject<>,
		public IComponentRegistry
	{
	public:
		
		DECLARE_IMPLEMENTATION(CComponentRegistry)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IComponentRegistry)
		END_INTERFACE_MAP()

		CComponentRegistry();
	
		void RegisterComponent(Core::IPluginShadow* plugin, SCOM_RIID clsid);

		Core::SCOM::HResult CreateComponent(SCOM_RIID clsid, IComponent** pComp);

	private:

		typedef std::hash_map<Core::SCOM::GUID, Core::IPluginShadow*> TComponentReg;

		TComponentReg mComponentFactories;
	};

} // namespace

#endif // _CCOMPONENTREGISTRY_H__