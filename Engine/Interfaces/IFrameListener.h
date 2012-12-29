/*========================================================
* IFrameListener.h
* @author Sergey Mikhtonyuk
* @date 12 December 2008
=========================================================*/
#ifndef _IFRAMELISTENER_H__
#define _IFRAMELISTENER_H__

#include "../Engine_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	/// Interface of objects that will be polled by MainLoop on each frame loop
	/** @ingroup Engine */
	SCOM_INTERFACE(IFrameListener, "cad0cae5-b4b2-4519-8ecf-a0cd0e3727f8", Core::SCOM::IUnknown)
	{
	public:
		/// Initialization of listener by MainLoop
		virtual void Initialize(IMainLoop *pMainLoop) = 0;

		/// Called each frame so object can perform it's actions
		/** Return -1 to break main loop, 0 to continue, 1 to unsubscribe from loop events, 2 if don't care. 
		 *  If loop have only don't cares it will exit, it is useful for background resident systems. */
		virtual int OnFrame() = 0;
	};



} // namespace


#endif // _IFRAMELISTENER_H__