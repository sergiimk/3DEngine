/*============================================================================
StackWalker.h: StackWalker class declaration

Author: Sergey Mikhtonyuk, 2008
============================================================================*/

#ifndef _STACK_WALKER_H__
#define _STACK_WALKER_H__

#include "../Core.Utils/EnvironmentDefs.h"

#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)

#include <windows.h>
#include <dbghelp.h>
#include <string>

namespace  Core
{
	namespace  Logging
	{
		/// Static class for getting the exception's stack trace
		/** @ingroup Logging */
		class StackWalker
		{
		public:
			///
			static void GenerateStackTrace(std::ostream& os, CONTEXT ctx, int skip);
			///
			static std::string GetModulePath(HMODULE module = 0);
			///
			static void WriteModuleName(std::ostream& os, HANDLE process, DWORD64 program_counter);
			///
			static void WriteFunctionName(std::ostream& os, HANDLE process, DWORD64 program_counter);
			///
			static void WriteFileAndLine(std::ostream& os, HANDLE process, DWORD64 program_counter);
		};
	
	
	} // namespace
} // namespace

#endif
#endif