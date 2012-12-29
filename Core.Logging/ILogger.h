/*========================================================
* ILogger.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
=========================================================*/
/** @defgroup Logging Logging
 *  Logging and exception handling library
 *  @ingroup Core */

#ifndef _ILOGGER_H__
#define _ILOGGER_H__

#include "../Core.Utils/EnvironmentDefs.h"

//////////////////////////////////////////////////////////////////////////

#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)
	#if defined(DEBUG) || defined(_DEBUG)
		#include <crtdbg.h>
	#endif
	#include <windows.h>
	#pragma comment(lib, "dbghelp.lib")
#endif

#include "../Core/GlobalEnvironment.h"
#include "../Core.COM/Interfaces.h"
#include "ILoggingListener.h"
#include <stdarg.h>
//////////////////////////////////////////////////////////////////////////

namespace Core
{
	namespace Logging
	{
		//////////////////////////////////////////////////////////////////////////
		// This enables extended argument checking by GCC.
		// Put this after the function or method declaration (not the definition!),
		// between the final closing parenthesis and the semicolon.
		// The first parameter indicates the 1-based index of the format string
		// parameter, the second parameter indicates the 1-based index of the first
		// variable parameter.
		// 
		// Example:
		// void foobar(int a, const char *fmt, ...) PRINTF_PARAMS(2, 3);
		//
		// For va_list based printf style functions, specfy 0 as the second parameter.
		// Example:
		//   void foobarv(int a, const char *fmt, va_list ap) PRINTF_PARAMS(2, 0);
		//
		// Note that 'this' is counted as a method argument. For non-static methods,
		// add 1 to the indices.
		//////////////////////////////////////////////////////////////////////////
		#ifdef COMPILER_GNUC
			#define PRINTF_PARAMS(...) __attribute__ ((format (printf, __VA_ARGS__)))
			#define SCANF_PARAMS(...) __attribute__ ((format (scanf, __VA_ARGS__)))
		#else
			#define PRINTF_PARAMS(...)
			#define SCANF_PARAMS(...)
		#endif

		//////////////////////////////////////////////////////////////////////////

		// Logging level affects to log functions without *Always
		// Values [0..4] 4 - maximum
		#define LOG_LEVEL 4

		//////////////////////////////////////////////////////////////////////////

		/// Logging types that defines the importance of logging
		enum LogType
		{
			LT_TRACE = 0,
			LT_INFO = 1,
			LT_WARNING = 2,
			LT_ERROR = 3,
		};

		//////////////////////////////////////////////////////////////////////////

		/// ILogger interface for printing debug information and logging an exceptions
		/** @ingroup Logging */
		SCOM_INTERFACE(ILogger, "aa82aafb-be77-4b20-ab68-e03b294cf7b5", SCOM::IUnknown)
		{
		public:
			/// Creates logging files
			virtual void Initialize(const char* execfile, const char* errorfile) = 0;

			/// Clears all log files
			virtual void ClearLogs() = 0;

			/// Logs message with specified logging type
			virtual void Log(LogType type, const char* format, va_list args) PRINTF_PARAMS(3, 0) = 0;

			/// Logs exception information
			virtual void Exception(const char *mssage) = 0;

			/// Logs exception information
			/// \todo refactor to no char* exceptions
			virtual void Exception(const std::exception& ex) = 0;

			#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)
			/// Is used inside __except block to log exceptions automatically (MS-specific)
			virtual unsigned long Error(EXCEPTION_POINTERS *eps) = 0;
			#endif

			/// Register log listener
			virtual void RegisterListener(ILoggingListener *listener) = 0;

			/// Removes log listener
			virtual void UnregisterListener(ILoggingListener *listener) = 0;
		};

		//////////////////////////////////////////////////////////////////////////

		#if LOG_LEVEL >= 4
			#define LogTrace(format, ...)	Core::Logging::_LogTraceAlways(format, __VA_ARGS__)
		#endif
		#if LOG_LEVEL >= 3
			#define LogInfo(format, ...)	Core::Logging::_LogInfoAlways(format, __VA_ARGS__)
		#endif
		#if LOG_LEVEL >= 2
			#define LogWarning(format, ...) Core::Logging::_LogWarningAlways(format, __VA_ARGS__)
		#endif
		#if LOG_LEVEL >= 1
			#define LogError(format, ...)	Core::Logging::_LogErrorAlways(format, __VA_ARGS__)
		#endif

		#define LogTraceAlways(format, ...)		Core::Logging::_LogTraceAlways(format, __VA_ARGS__)
		#define LogInfoAlways(format, ...)		Core::Logging::_LogInfoAlways(format, __VA_ARGS__)
		#define LogWarningAlways(format, ...)	Core::Logging::_LogWarningAlways(format, __VA_ARGS__)
		#define LogErrorAlways(format, ...)		Core::Logging::_LogErrorAlways(format, __VA_ARGS__)

		//////////////////////////////////////////////////////////////////////////

		void _LogTraceAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
		inline void _LogTraceAlways(const char *format, ...)
		{
			if(gEnv && gEnv->Logger)
			{
				va_list args;
				va_start(args, format);
				gEnv->Logger->Log(LT_TRACE, format, args);
				va_end(args);
			}
		}

		void _LogInfoAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
		inline void _LogInfoAlways(const char *format, ...)
		{
			if(gEnv && gEnv->Logger)
			{
				va_list args;
				va_start(args, format);
				gEnv->Logger->Log(LT_INFO, format, args);
				va_end(args);
			}
		}

		void _LogWarningAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
		inline void _LogWarningAlways(const char *format, ...)
		{
			if(gEnv && gEnv->Logger)
			{
				va_list args;
				va_start(args, format);
				gEnv->Logger->Log(LT_WARNING, format, args);
				va_end(args);
			}
		}

		void _LogErrorAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
		inline void _LogErrorAlways(const char *format, ...)
		{
			if(gEnv && gEnv->Logger)
			{
				va_list args;
				va_start(args, format);
				gEnv->Logger->Log(LT_ERROR, format, args);
				va_end(args);
			}
		}

		//////////////////////////////////////////////////////////////////////////
	
	} // namespace
} // namespace													

#endif // _ILOGGER_H__