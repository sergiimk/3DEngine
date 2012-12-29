/** @defgroup SCOM SCOM
 *  Lightweight COM library
 *  @ingroup Core */

#ifndef _COMTYPES_H__
#define _COMTYPES_H__


namespace Core
{
	namespace SCOM
	{
	
		//@{
		/** Predefined HResult types */
		typedef long HResult;
	
		#define SCOM_S_OK							((Core::SCOM::HResult)0L)
		#define SCOM_S_FALSE						((Core::SCOM::HResult)1L)
	
		#define SCOM_E_NOTIMPL						((Core::SCOM::HResult)0x80004001L)
		#define SCOM_E_OUTOFMEMORY					((Core::SCOM::HResult)0x8007000EL)
		#define SCOM_E_INVALIDARG					((Core::SCOM::HResult)0x80070057L)
		#define SCOM_E_NOINTERFACE					((Core::SCOM::HResult)0x80004002L)
		#define SCOM_E_POINTER						((Core::SCOM::HResult)0x80004003L)
		#define SCOM_E_HANDLE						((Core::SCOM::HResult)0x80070006L)
		#define SCOM_E_ABORT						((Core::SCOM::HResult)0x80004004L)
		#define SCOM_E_FAIL							((Core::SCOM::HResult)0x80004005L)
		#define SCOM_E_ACCESSDENIED					((Core::SCOM::HResult)0x80070005L)
	
		#define SCOM_CLASS_E_NOAGGREGATION			((Core::SCOM::HResult)0x80040110L)
	
		#define SCOM_SUCCEEDED(hr) (((Core::SCOM::HResult)(hr)) >= 0)
		#define SCOM_FAILED(hr) (((Core::SCOM::HResult)(hr)) < 0)
		//@}
	
	
	} // namespace
} // namespace

#endif // _COMTYPES_H__