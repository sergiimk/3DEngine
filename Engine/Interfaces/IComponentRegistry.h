/*========================================================
* IComponentRegistry.h
* @author Sergey Mikhtonyuk
* @date 29 June 2009
=========================================================*/
#ifndef _ICOMPONENTREGISTRY_H__
#define _ICOMPONENTREGISTRY_H__

#include "../Engine_fwd.h"
#include "../../Core/Core_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{

	/// Provides means of component management
	/** @ingroup Engine */
	SCOM_INTERFACE(IComponentRegistry, "8e5604a8-422a-45cb-8bb5-a63f39e0ae43", Core::SCOM::IUnknown)
	{
	public:
	
		/// Registers the component in system
		/** @param plugin Provider of the component
		 *  @param clsid class ID of the component implementation */
		virtual void RegisterComponent(Core::IPluginShadow* plugin, SCOM_RIID clsid) = 0;

		/// Creates the registered component by its ID
		/** @param clsid ID of component implementation
		 *  @return SCOM_E_FAIL if component is not registered, result from CreateInstance otherwise */
		virtual Core::SCOM::HResult CreateComponent(SCOM_RIID clsid, IComponent** pComp) = 0;
	};

} // namespace

#endif // _ICOMPONENTREGISTRY_H__