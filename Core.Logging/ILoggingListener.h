/*========================================================
* ILoggingListener.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
=========================================================*/
#ifndef _ILOGGING_LISTENER_H__
#define _ILOGGING_LISTENER_H__

#include "../Core.COM/Interfaces.h"
#include <string>

namespace Core
{
	namespace Logging
	{
		/// ILoggingListener interface for objects that want to intercept the logging messages
		/** @ingroup Logging */
		SCOM_INTERFACE(ILoggingListener, "b1d0733f-5539-4c8c-b53e-535dbaf69266", SCOM::IUnknown)
		{
		public:
			/// Trace message
			virtual void OnTrace	(const char* msg) = 0;
			
			/// Info message
			virtual void OnInfo		(const char* msg) = 0;
			
			/// Warning message
			virtual void OnWarning	(const char* msg) = 0;

			/// Error message
			virtual void OnError	(const char* msg) = 0;
		};
	
	
	} // namespace
} // namespace

#endif