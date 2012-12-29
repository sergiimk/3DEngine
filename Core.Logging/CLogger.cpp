/*========================================================
* CLogger.cpp
* @author Sergey Mikhtonyuk
* @date 04 December 2008
=========================================================*/
#include "CLogger.h"
#include "ExceptionHandler.h"
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Core
{
	namespace  Logging
	{
		//////////////////////////////////////////////////////////////////////////
		#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)
		struct SymGuard
		{
			HANDLE mProc;
			SymGuard() : mProc(GetCurrentProcess())
			{
				SymInitialize(mProc, 0, true);
				DWORD options = SymGetOptions();
				options |= SYMOPT_LOAD_LINES;
				SymSetOptions(options);
			}

			~SymGuard()
			{
				SymCleanup(mProc);
			}
		};
		#endif
		//////////////////////////////////////////////////////////////////////////


		/*=======================================================================
		 =  Init / Shutdown
		 =======================================================================*/
		void CLogger::Initialize(const char* execfile, const char* errorfile)
		{
			mExecFile = execfile;
			mErrorFile = errorfile;
			ClearLogs();
		}

		/*=======================================================================
		 =  FileWriters
		 =======================================================================*/

		void CLogger::ClearLogs()
		{
			std::ofstream ofs;
			ofs.open(mExecFile.c_str(), std::ios_base::out);
			if(!ofs.bad())
				ofs.close();

			ofs.open(mErrorFile.c_str(), std::ios_base::out);
			if(!ofs.bad())
				ofs.close();
		}

		//////////////////////////////////////////////////////////////////////////

		const char* GetPrefix(LogType type)
		{
			switch(type)
			{
			case LT_TRACE:		return " -TRACE-";
			case LT_INFO:		return " -INFO-";
			case LT_WARNING:	return " <<WARNING>>";
			case LT_ERROR:		return " ===ERROR===";
			default:			return "";
			}
		}

		//////////////////////////////////////////////////////////////////////////

		int WritePrefix(char *buffer, LogType type)
		{
			boost::posix_time::ptime now(boost::posix_time::second_clock::local_time());
			boost::posix_time::time_duration time(now.time_of_day());
			
			return sprintf_s(buffer, MAX_MESSAGE_LENGTH, "[%0.2d:%0.2d:%0.2d] %s\t", 
								time.hours(), 
								time.minutes(),
								time.seconds(),
								GetPrefix(type));
		}

		//////////////////////////////////////////////////////////////////////////

		void DumpToFile(const std::string& file, const std::string& info)
		{
			std::ofstream ofs;
			ofs.open(file.c_str(), std::ios_base::out | std::ios_base::app);
			if (!ofs.bad())
			{
				ofs << info;
				ofs.close();
			}
		}

		//////////////////////////////////////////////////////////////////////////

		void CLogger::Log(LogType type, const char* format, va_list args)
		{
			char buffer[MAX_MESSAGE_LENGTH];

			int pref = WritePrefix(buffer, type);
			int len = MAX_MESSAGE_LENGTH - pref - 1;

			len = _vsnprintf_s(&buffer[pref], len, len - 1, format, args);

			NotifyListeners(type, &buffer[pref]);
			
			if(len == -1)	len = MAX_MESSAGE_LENGTH - 2;
			else			len += pref;

			buffer[len] = '\n';
			buffer[len + 1] = '\0';

			DumpToFile(mExecFile, buffer);
			if(type == LT_ERROR)
				DumpToFile(mErrorFile, buffer);
		}

		//////////////////////////////////////////////////////////////////////////

		void CLogger::Log(LogType type, const char* format, ...)
		{
			va_list args;
			va_start(args, format);
			Log(type, format, args);
			va_end(args);
		}

		//////////////////////////////////////////////////////////////////////////

		void CLogger::Exception(const char *message)
		{
			Log(LT_ERROR, message);
		}

		//////////////////////////////////////////////////////////////////////////

		void CLogger::Exception(const std::exception& ex)
		{
			Exception(ex.what());
		}

		//////////////////////////////////////////////////////////////////////////


		/*=======================================================================
		 =  Exception catchers
		 =======================================================================*/
		#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)

		DWORD CLogger::Error(EXCEPTION_POINTERS* eps) 
		{
			SymGuard g;
			std::string buffer;	
			DWORD res = _Error(eps, buffer);
			
			Exception(buffer.c_str());
			return res;
		}

		//////////////////////////////////////////////////////////////////////////

		DWORD CLogger::_Error(EXCEPTION_POINTERS *eps, std::string& buffer)
		{
			__try
			{
				ExceptionHandler::CreateMiniDump(eps);
				return ExceptionHandler::GetExceptionInfo(eps, buffer);
			} 
			__except (EXCEPTION_EXECUTE_HANDLER) 
			{
				return EXCEPTION_CONTINUE_SEARCH;
			}
		}

		#endif
		
		//////////////////////////////////////////////////////////////////////////


		void CLogger::RegisterListener(Core::Logging::ILoggingListener *listener)
		{
			mListeners.push_back(listener);
		}

		//////////////////////////////////////////////////////////////////////////

		void CLogger::UnregisterListener(ILoggingListener *listener)
		{
			std::vector<ILoggingListener*>::iterator it = 
				std::find(mListeners.begin(), mListeners.end(), listener);

			if(it != mListeners.end()) mListeners.erase(it);
		}

		//////////////////////////////////////////////////////////////////////////

		void CLogger::NotifyListeners(LogType type, const char* msg) const
		{
			typedef void (ILoggingListener::*lfT)(const char*);
			lfT fun = 0;

			switch(type)
			{
			case LT_TRACE:
				fun = &ILoggingListener::OnTrace;
				break;
			case LT_INFO:
				fun = &ILoggingListener::OnInfo;
				break;
			case LT_WARNING:
				fun = &ILoggingListener::OnWarning;
				break;
			case LT_ERROR:
				fun = &ILoggingListener::OnError;
				break;
			};

			std::for_each(mListeners.begin(), mListeners.end(), std::bind2nd(std::mem_fun1(fun), msg));
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace