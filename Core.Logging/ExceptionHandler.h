/*========================================================
* ExceptionHandler.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
=========================================================*/
#ifndef _EXCEPTION_HANDLER_H__
#define _EXCEPTION_HANDLER_H__

#include "../Core.Utils/EnvironmentDefs.h"

#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)

#include <windows.h>
#include <dbghelp.h>
#include <string>

namespace Core
{
	namespace Logging
	{
		/// Static class for getting the exception's info and creating mini-dump file
		/** @ingroup Logging */
		class ExceptionHandler
		{
		public:
			/// Returns the type of exception and call stack of place where it was thrown
			static DWORD GetExceptionInfo(EXCEPTION_POINTERS * eps, std::string & buffer);
			/// Creates mini-dump file
			static bool CreateMiniDump(EXCEPTION_POINTERS *eps);
		private:
			
			struct UntypedException 
			{
				void*					exception_object;
				_CatchableTypeArray*	type_array;

				UntypedException(const EXCEPTION_RECORD & er)
					:	exception_object(reinterpret_cast<void*>(er.ExceptionInformation[1])),
					type_array(reinterpret_cast<_ThrowInfo*>(er.ExceptionInformation[2])->pCatchableTypeArray)
				{
				}
			};

			static void* exception_cast_worker(const UntypedException& e, const type_info& ti);
			static void get_exception_types(std::ostream& os, const UntypedException& e);

			template <typename T> 
			static T* exception_cast(const UntypedException& e) 
			{
				const std::type_info& ti = typeid(T);
				return reinterpret_cast<T*>(exception_cast_worker(e, ti));
			}
		};
	
	
	
	} // namespace
} // namespace

#endif
#endif