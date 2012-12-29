/*========================================================
* IExtensionPoint.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
=========================================================*/
#ifndef _IEXTENSIONPOINT_H__
#define _IEXTENSIONPOINT_H__

#include "Core_fwd.h"
#include <string>
#include <vector>

namespace Core
{
	
	/// Extension point interface serves a link between extension provider's shadow and extenders
	/** @ingroup Core */
	SCOM_INTERFACE(IExtensionPoint, "f46632cb-fc73-4d5f-a418-0c30b8150a61", SCOM::IUnknown)
	{
	public:
		/// Name of extension point
		virtual const std::string& ID() = 0;

		/// Unique id of extension point (in format plugin_name::point_name)
		virtual const std::string& UniqueID() = 0;

		/// Gets provider of this extension point
		virtual IPluginShadow* Provider() = 0;

		/// Interface all extenders must implement
		virtual const SCOM::GUID& InterfaceID() = 0;

		/// Returns the number of extensions of this point
		virtual size_t getExtensionCount() = 0;

		/// Retrieves specified extension
		virtual IExtension* getExtension(size_t index) = 0;
	};

} // namespace


#endif // _IEXTENSIONPOINT_H__