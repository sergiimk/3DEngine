/*========================================================
* Module.cpp
* @author Sergey Mikhtonyuk
* @date 20 April 2009
=========================================================*/
#include "Module.h"
#include <Windows.h>

namespace Core
{
	namespace SCOM
	{
		//////////////////////////////////////////////////////////////////////////
		
		HResult Module::Init(const char* moduleName)
		{
			mModule = LoadLibraryExA(moduleName, 0, 0);
			if(!mModule) return SCOM_E_FAIL;

			ModuleAccessor::GET_MAP_FUNC getModuleMap;
			getModuleMap = (ModuleAccessor::GET_MAP_FUNC)GetProcAddress((HMODULE)mModule, "GetModuleMap");
			if(!getModuleMap) return SCOM_E_FAIL;

			mInitFunc = (INIT_FUNC)GetProcAddress((HMODULE)mModule, "ModuleInit");
			mShutdownFunc = (SHUTDOWN_FUNC)GetProcAddress((HMODULE)mModule, "ModuleShutdown");

			mModuleAccessor.Init(getModuleMap);

			if(mInitFunc)
				mInitFunc();

			return SCOM_S_OK;
		}

		//////////////////////////////////////////////////////////////////////////

		void Module::Shutdown()
		{
			mInitFunc = 0;
			if(mShutdownFunc)	
			{
				mShutdownFunc();
				mShutdownFunc = 0;
			}
		}

		//////////////////////////////////////////////////////////////////////////

		void Module::UnloadPackage()
		{
			if(mModule)
			{
				FreeLibrary((HMODULE)mModule);
				mModule = 0;
			}
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace