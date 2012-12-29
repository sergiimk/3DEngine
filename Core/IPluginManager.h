/*========================================================
* IPluginManager.h
* @author Sergey Mikhtonyuk
* @date 15 November 2008
=========================================================*/

#ifndef IPluginManager_h__
#define IPluginManager_h__

#include "IPluginShadow.h"
#include <string>

namespace Core
{
	/// IPluginManager interface
	/** Implementor of this interface responsible 
	  * for loading and supporting all plug-ins in the system 
	  *  
	  * @ingroup  Core */
	SCOM_INTERFACE(IPluginManager, "6ad90a75-daeb-49d8-9167-0c5a8f5c5a41", SCOM::IUnknown)
	{
	public:
		/// Finds the shadow by plug-in name
		virtual IPluginShadow* FindPluginShadow(const std::string &name) = 0;

		/// Finds the extension by full name
		virtual IExtensionPoint* FindExtensionPoint(const std::string &name) = 0;
	};
} // namespace

#endif // IPluginManager_h__