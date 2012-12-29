/*============================================================================
ExceptionHandler.cpp: ExceptionHandler class definition

Author: Sergey Mikhtonyuk, 2008
============================================================================*/

#include "ExceptionHandler.h"

#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)

#include <sstream>
#include <fstream>
#include "StackWalker.h"

namespace Core
{
	namespace Logging
	{

		DWORD ExceptionHandler::GetExceptionInfo(EXCEPTION_POINTERS* eps, std::string& buffer) 
		{
			std::stringstream sstr;
			const EXCEPTION_RECORD& er = *eps->ExceptionRecord;
			int skip = 0;

			switch (er.ExceptionCode) 
			{

			// C++ exception
			case 0xE06D7363: 
				{ 
					UntypedException ue(er);
					if (std::exception* e = exception_cast<std::exception>(ue)) 
					{
						const std::type_info & ti = typeid(*e);
						sstr << ti.name() << ":" << e->what();
					} 
					else 
					{
						sstr << "Unknown C++ exception thrown.\n";
						get_exception_types(sstr, ue);
					}
					skip = 2; // skip RaiseException and _CxxThrowException
				} 
				break;

			case EXCEPTION_ACCESS_VIOLATION: 
				{
					sstr	<< "Access violation. Illegal "
							<< (er.ExceptionInformation[0] ? "write" : "read")
							<< " by "
							<< er.ExceptionAddress
							<< " at "
							<< reinterpret_cast<void *>(er.ExceptionInformation[1]);
				} 
				break;

			default: 
				{
					sstr	<< "SEH exception thrown. Exception code: "
							<< std::hex << std::uppercase << er.ExceptionCode
							<< " at "
							<< er.ExceptionAddress;
				}
			}

			sstr << "\nStack Trace:\n";
			StackWalker::GenerateStackTrace(sstr, *eps->ContextRecord, skip);
			buffer = sstr.str();

			return EXCEPTION_EXECUTE_HANDLER;
		}




		void* ExceptionHandler::exception_cast_worker(const UntypedException& e, const type_info& ti) 
		{
			for (int i = 0; i < e.type_array->nCatchableTypes; ++i) 
			{
				_CatchableType& type_i = *e.type_array->arrayOfCatchableTypes[i];
				const std::type_info& ti_i = *reinterpret_cast<std::type_info*>(type_i.pType);

				if (ti_i == ti) 
				{
					char * base_address = reinterpret_cast<char*>(e.exception_object);
					base_address += type_i.thisDisplacement.mdisp;
					return base_address;
				}
			}
			return 0;
		}



		void ExceptionHandler::get_exception_types(std::ostream& os, const UntypedException& e) 
		{
			for (int i = 0; i < e.type_array->nCatchableTypes; ++i) 
			{
				_CatchableType& type_i = *e.type_array->arrayOfCatchableTypes[i];
				const std::type_info& ti_i = *reinterpret_cast<std::type_info*>(type_i.pType);
				os << ti_i.name() << "\n";
			}
		}


		bool ExceptionHandler::CreateMiniDump(EXCEPTION_POINTERS *eps)
		{
			HANDLE hFile = CreateFile(L"ErrorDump.dmp", GENERIC_READ | GENERIC_WRITE, 
			0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

			if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
			{
				MINIDUMP_EXCEPTION_INFORMATION mdei; 

				mdei.ThreadId           = GetCurrentThreadId(); 
				mdei.ExceptionPointers  = eps; 
				mdei.ClientPointers     = FALSE; 
				MINIDUMP_TYPE mdt       = MiniDumpNormal; 

				BOOL res = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), 
				  hFile, mdt, (eps != 0) ? &mdei : 0, 0, 0 ); 

				CloseHandle( hFile ); 

				return res == TRUE;
			}
			else 
			{
				return false;
			}
		}

	} // namespace
} // namespace

#endif