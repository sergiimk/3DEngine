/*========================================================
* CCore.cpp
* @author Sergey Mikhtonyuk
* @date 09 November 2008
=========================================================*/

#include "CCore.h"
#include "CPluginManager.h"
#include "../Core.Logging/CLogger.h"
#include "CoreExceptions.h"
#include "IExtension.h"
#include "IExtensionPoint.h"
#include "IPluginShadow.h"
#include "IStartListener.h"

#include "../Core.Utils/EnvironmentDefs.h"

namespace Core
{
	//////////////////////////////////////////////////////////////////////////

	// Instance
	GlobalEnvironment* gEnv;

	//////////////////////////////////////////////////////////////////////////

	CCore::CCore() 
		: pCurrentEnvironment(&mEnvironment)
	{
		memset(&mEnvironment, 0, sizeof(GlobalEnvironment));

		gEnv = pCurrentEnvironment;
		pCurrentEnvironment->Core = this;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::Initialize(const char* paramsFile)
	{
		if(gEnv->PluginManager)
			throw CoreException("Multiple Core initialization");

		scom_new<Logging::CLogger>(&gEnv->Logger, UUIDOF(Logging::ILogger));
		gEnv->Logger->Initialize("Execution.log", "Error.log");

		LogInfoAlways("[Init] Initializing core");
		LogTrace("[Init] Creating plugin manager");

		scom_new<CPluginManager>(&gEnv->PluginManager, UUIDOF(IPluginManager));
		((CPluginManager*)gEnv->PluginManager)->Run(paramsFile);
	}

	//////////////////////////////////////////////////////////////////////////

	CCore::~CCore()
	{
		LogInfoAlways("[Shutdown] Shutting down the core");

		if(gEnv->PluginManager)
			gEnv->PluginManager->Release();

		if(gEnv->Logger)
			gEnv->Logger->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::StartExecution(int argc, char *argv[])
	{
#if defined(COMPILER_MSC) && defined(EXCEPTION_TRACE)
		__try
		{
			StartExecution_actual(argc, argv);
		}
		__except(gEnv->Logger->Error(GetExceptionInformation()))
		{
			throw;
		}
#else
		try
		{
			StartExecution_actual(argc, argv);
		}
		catch(CoreException& cex)
		{
			LogErrorAlways(cex.what());
		}
		catch(std::exception& sex)
		{
			LogErrorAlways(sex.what());
		}
		catch(...)
		{
			LogErrorAlways("Unrecognized exception");
		}
#endif
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::StartExecution_actual(int argc, char *argv[])
	{
		IPluginShadow *pMyShadow = gEnv->PluginManager->FindPluginShadow("core");
		IExtensionPoint *pStartListeners = pMyShadow->FindExtensionPoint("startlisteners");
		size_t nextensions = pStartListeners->getExtensionCount();

		for(size_t i = 0; i != nextensions; ++i)
		{
			IExtension *pEx = pStartListeners->getExtension(i);
			LogTrace("[Startup] Notifying start listener: %s", pEx->Extender()->PluginName().c_str());

			SCOM::ComPtr<IStartListener> l;
			pEx->Extender()->CreateInstance(pEx->ImplClassID(), UUID_PPV(IStartListener, l.wrapped()));

			if(l)
			{
				l->OnStart(argc, argv);
			}
			else
			{
				LogErrorAlways("[Startup] Failed to create start listener's implementation: %s", 
								pEx->Extender()->PluginName().c_str());
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::RegisterEnvironment(GlobalEnvironment* newEnv)
	{
		memcpy(newEnv, pCurrentEnvironment, sizeof(GlobalEnvironment));
		pCurrentEnvironment = newEnv;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
