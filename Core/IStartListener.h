/*========================================================
* IStartListener.h
* @author Sergey Mikhtonyuk
* @date 07 December 2008
=========================================================*/
#ifndef _ISTARTLISTENER_H__
#define _ISTARTLISTENER_H__

#include "../Core.COM/Interfaces.h"

namespace Core
{
	/// Extenders will be started on core startup
	/** @ingroup Core */
	SCOM_INTERFACE(IStartListener, "36d3d4bf-5b5f-4fb0-803d-3f7b89917979", SCOM::IUnknown)
	{
	public:
		/// Called after core initialization
		virtual void OnStart(int argc, char *argv[]) = 0;
	};


} // namespace


#endif // _ISTARTLISTENER_H__