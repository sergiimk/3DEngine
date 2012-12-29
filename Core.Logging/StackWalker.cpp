/*========================================================
* StackWalker.cpp
* @author Sergey Mikhtonyuk
* @date 04 December 2008
=========================================================*/

#include "StackWalker.h"

#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)

namespace  Core
{
	namespace  Logging
	{

		void StackWalker::GenerateStackTrace(std::ostream& os, CONTEXT ctx, int skip) 
		{
			STACKFRAME64 sf		= {};
			sf.AddrPC.Offset    = ctx.Eip;
			sf.AddrPC.Mode      = AddrModeFlat;
			sf.AddrStack.Offset = ctx.Esp;
			sf.AddrStack.Mode   = AddrModeFlat;
			sf.AddrFrame.Offset = ctx.Ebp;
			sf.AddrFrame.Mode   = AddrModeFlat;

			HANDLE process	= GetCurrentProcess();
			HANDLE thread	= GetCurrentThread();

			os << std::uppercase;
			for (;;) 
			{
				SetLastError(0);
				BOOL stack_walk_ok = StackWalk64(	IMAGE_FILE_MACHINE_I386, process, thread, &sf,
													&ctx, 0, &SymFunctionTableAccess64, 
													&SymGetModuleBase64, 0);

				if (!stack_walk_ok || !sf.AddrFrame.Offset) return;

				if (skip) 
				{
					--skip;
				} 
				else 
				{
					// write the address

					os << std::hex << reinterpret_cast<void *>(sf.AddrPC.Offset) << " | " << std::dec;

					WriteModuleName(os, process, sf.AddrPC.Offset);
					WriteFunctionName(os, process, sf.AddrPC.Offset);
					WriteFileAndLine(os, process, sf.AddrPC.Offset);

					os << "\n";
				}
			}
		}


		std::string StackWalker::GetModulePath(HMODULE module) 
		{
			char path_name[MAX_PATH] = {};
			DWORD size = GetModuleFileNameA(module, path_name, MAX_PATH);
			return std::string(path_name, size);
		}


		void StackWalker::WriteModuleName(std::ostream& os, HANDLE process, DWORD64 program_counter) 
		{
			DWORD64 module_base = SymGetModuleBase64(process, program_counter);
			if (module_base) 
			{
				std::string module_name = GetModulePath(reinterpret_cast<HMODULE>(module_base));
				if (!module_name.empty())
					os << module_name << " | ";
				else 
					os << "Unknown module | ";
			} 
			else 
			{
				os << "Unknown module | ";
			}
		}



		void StackWalker::WriteFunctionName(std::ostream& os, HANDLE process, DWORD64 program_counter) 
		{
			SYMBOL_INFO_PACKAGE sym = {};
			sym.si.SizeOfStruct = sizeof(SYMBOL_INFO);
			sym.si.MaxNameLen = MAX_SYM_NAME;
			if (SymFromAddr(process, program_counter, 0, &sym.si)) 
			{
				os << sym.si.Name << "()";
			} else {
				os << "Unknown function";
			} 
		}




		void StackWalker::WriteFileAndLine(std::ostream& os, HANDLE process, DWORD64 program_counter) 
		{
			IMAGEHLP_LINE64 ih_line = { sizeof(IMAGEHLP_LINE64) };
			DWORD dummy = 0;
			if (SymGetLineFromAddr64(process, program_counter, &dummy, &ih_line)) 
			{
				os << " in " << ih_line.FileName
					<< " : " << ih_line.LineNumber;
			}
		}


	} // namespace
} // namespace

#endif