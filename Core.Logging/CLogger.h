/*========================================================
* CLogger.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
=========================================================*/
#ifndef _CLOGGER_H__
#define _CLOGGER_H__

#include "ILogger.h"
#include "../Core.COM/Implementations.h"

#include <string>
#include <vector>

namespace Core
{
	namespace Logging
	{
		//////////////////////////////////////////////////////////////////////////

		#define MAX_MESSAGE_LENGTH 4096

		//////////////////////////////////////////////////////////////////////////
		
		/// Singleton class for printing debug information and logging an exceptions
		/** @ingroup Logging */
		/// \todo make logger thread-safe, add thread name to output, improve streaming
		class NOVTABLE CLogger : 
			public SCOM::ComRootObject<SCOM::MultiThreadModel>,
			public ILogger
		{
		public:

			DECLARE_IMPLEMENTATION2(CLogger, SCOM::ComClassFactorySingleton)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(ILogger)
			END_INTERFACE_MAP()

			void Initialize(const char* execfile, const char* errorfile);
			void ClearLogs();
			void Log(LogType type, const char* format, va_list args);
			void Log(LogType type, const char* format, ...);
			void Exception(const char *mssage);
			void Exception(const std::exception& ex);
			
			#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)
			unsigned long Error(EXCEPTION_POINTERS* eps);
			#endif

			void RegisterListener(ILoggingListener *listener);
			void UnregisterListener(ILoggingListener *listener);
			void NotifyListeners(LogType type, const char* msg) const;

		private:
			#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)
			unsigned long _Error (EXCEPTION_POINTERS *eps, std::string& buffer);
			#endif

			std::string mExecFile;
			std::string mErrorFile;
			std::vector<ILoggingListener*> mListeners;
		};
	
	
	
	} // namespace
} // namespace

#endif