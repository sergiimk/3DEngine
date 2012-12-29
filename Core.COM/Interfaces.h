/*========================================================
* Interfaces.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
=========================================================*/
#ifndef _INTERFACES_H__
#define _INTERFACES_H__

#include "COMTypes.h"
#include "GUID.h"

namespace Core
{
	namespace SCOM
	{
		//////////////////////////////////////////////////////////////////////////

		//@{
		/** Helper interface definition macros */
		#define NOVTABLE _declspec(novtable)

		#define SCOM_INTERFACE_IU(name, guid)									\
		SCOM_DECLARE_GUID(name, guid)											\
		class NOVTABLE name

		#define SCOM_INTERFACE(name, guid, base)								\
		SCOM_DECLARE_GUID(name, guid)											\
		class NOVTABLE name : public base
		//@}

		//////////////////////////////////////////////////////////////////////////

		/// IUnknown interface.
		/** Base interface for all implementations.
		 *  @ingroup SCOM */
		SCOM_INTERFACE_IU(IUnknown, "91B5E844-05DB-434d-AAAA-9E0FE55C39D1")
		{
		public:

			/// Dynamic casting method
			/** QueryInterface is used for dynamic casting and checking
			 *  if objects implements specific interface.
			 *
			 *  @param riid UUID of interface to cast to
			 *  @param ppObject pointer to returned interface pointer */
			virtual HResult QueryInterface(SCOM_RIID riid, void **ppObject) = 0;

			/// Increases reference counter
			virtual unsigned long AddRef() = 0;
			
			/// Decreases reference counter
			virtual unsigned long Release() = 0;
		};
	

		//////////////////////////////////////////////////////////////////////////


		/// IClassFactory interface.
		/** Base interface for creatable objects.
		 *  @ingroup SCOM */
		SCOM_INTERFACE(IClassFactory, "C1621CCE-40F5-46c0-9397-088475E0B2FA", IUnknown)
		{
		public:
			/// Creates instance and casts it to 'riid' interface
			/** @param riid			Unique identifier of class
			 *  @param ppvObject	Where to put class pointer */
			virtual HResult CreateInstance(SCOM_RIID riid, void **ppvObject) = 0;
		};

	} // namespace
} // namespace


/// Performs the type casting
/** @ingroup SCOM */
template<class I>
Core::SCOM::HResult interface_cast(Core::SCOM::IUnknown* pUnk, I** pp)
{
	return pUnk->QueryInterface(UUID_PPV(I, pp));
}

#endif // _INTERFACES_H__