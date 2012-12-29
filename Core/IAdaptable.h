/*========================================================
* IAdaptable.h
* @author Sergey Mikhtonyuk
* @date 23 November 2008
=========================================================*/

#ifndef _IADAPTABLE_H__
#define _IADAPTABLE_H__

#include "Core.COM/Interfaces.h"

namespace Core
{
	/// IAdaptable interface
	/** This interface is a base of "Extension Object" pattern
	  * that allows: 
	  * - to add a service interface to a type without exposing it in that type;
	  * - to add behavior to preexisting types.
	  *
	  * Adapters are the wrapper classes that extend the functionality of the wrapped object.
	  * They are similar to tear-off interfaces but simpler, because QueryInterface symmetric rule
	  * can be ignored. 
	  *
	  * @ingroup Core */
	SCOM_INTERFACE(IAdaptable, "f7c5f5ea-33ed-48e8-8823-5904da2cf6fa", SCOM::IUnknown)
	{
	public:
		/// Returns the adapter of the object if it exist
		virtual SCOM::HResult GetAdapter(SCOM_RIID iid, SCOM::IUnknown** ppv) = 0;
	};

} // namespace


#endif // _IADAPTABLE_H__