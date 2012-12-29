/*========================================================
* CEngine.cpp
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#include "CEngine.h"
#include "../MainLoop/CMainLoop.h"
#include "CComponentRegistry.h"
#include "CSceneManager.h"
#include "CPhysicsManager.h"
#include "CTransformGraph.h"
#include "CLogicController.h"
#include "CAnimationController.h"
#include "../../Engine.Graphics/Interfaces/IRenderer.h"
#include "../../Engine.Input/IInputController.h"
#include "../../Engine.UI/Interfaces/IUIManager.h"
#include "../../Core/CommonPlugin.h"
#include "../../Core/SekaiCore.h"
#include "../../Core.Logging/ILogger.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////
	GlobalEnvironment* gEnv;
	//////////////////////////////////////////////////////////////////////////

	CEngine::CEngine()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CEngine::~CEngine()
	{
		mUIManager.Release();
		mTransformGraph.Release();
		mPhysicsManager.Release();
		mSceneManager.Release();
		mComponentRegistry.Release();
		mMainLoop.Release();
		
		if(mRenderer)
			mRenderer->Shutdown();
		mRenderer.Release();

		// Restore environment pointer
		Core::gEnv->Core->RegisterEnvironment(Core::gEnv);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEngine::OnStart(int argc, char *argv[])
	{
		LogTrace("Initializing engine");
		
		if(InitSubsystems())
			mMainLoop->Start();

		LogTrace("Shutting engine");
	}

	//////////////////////////////////////////////////////////////////////////

	GlobalEnvironment* CEngine::Environment() const
	{
		return (GlobalEnvironment*)&mEngineEnvironment;
	}

	//////////////////////////////////////////////////////////////////////////

	IComponentRegistry* CEngine::getComponentRegistry() const
	{
		return mComponentRegistry;
	}

	//////////////////////////////////////////////////////////////////////////

	ISceneManager* CEngine::getSceneManager() const
	{
		return mSceneManager;
	}

	//////////////////////////////////////////////////////////////////////////

	UI::IUIManager* CEngine::getUIManager() const
	{
		return mUIManager;
	}

	//////////////////////////////////////////////////////////////////////////

	IPhysicsManager* CEngine::getPhysicsManager() const
	{
		return mPhysicsManager;
	}

	//////////////////////////////////////////////////////////////////////////

	ITransformGraph* CEngine::getTransformGraph() const
	{
		return mTransformGraph;
	}

	//////////////////////////////////////////////////////////////////////////

	ILogicController* CEngine::getLogicController() const
	{
		return mLogicController;
	}

	//////////////////////////////////////////////////////////////////////////

	IAnimationController* CEngine::getAnimationController() const
	{
		return mAnimationController;
	}

	//////////////////////////////////////////////////////////////////////////

	Graphics::IRenderer* CEngine::getRenderer() const
	{
		return mRenderer;
	}

	//////////////////////////////////////////////////////////////////////////

	Input::IInputController* CEngine::getInputController() const
	{
		return mInputController;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CEngine::InitSubsystems()
	{
		// Set up global environment
		memset(&mEngineEnvironment, 0, sizeof(GlobalEnvironment));
		memcpy(&mEngineEnvironment, Core::gEnv, sizeof(Core::GlobalEnvironment));
		mEngineEnvironment.Engine = this;
		Engine::gEnv = &mEngineEnvironment;
		Core::gEnv->Core->RegisterEnvironment(&mEngineEnvironment);

		// Main loop
		scom_new<CMainLoop>(mMainLoop);
		mEngineEnvironment.MainLoop = mMainLoop;

		// Component registry
		scom_new<CComponentRegistry>(mComponentRegistry);
		mEngineEnvironment.ComponentRegistry = mComponentRegistry;

		// Scene manager
		scom_new<CSceneManager>(mSceneManager);
		mEngineEnvironment.SceneManager = mSceneManager;

		// Physics manager
		scom_new<CPhysicsManager>(mPhysicsManager);
		mEngineEnvironment.PhysicsManager = mPhysicsManager;

		// Transformation graph
		scom_new<CTransformGraph>(mTransformGraph);
		mEngineEnvironment.TransformGraph = mTransformGraph;

		// Logic controller
		scom_new<CLogicController>(mLogicController);
		mEngineEnvironment.LogicController = mLogicController;

		// Animation controller
		scom_new<CAnimationController>(mAnimationController);
		mEngineEnvironment.AnimationController = mAnimationController;

		// Create input controller
		/// \todo refactor to extension point like renderer
		Core::IPluginShadow* im = gEnv->PluginManager->FindPluginShadow("engine.input");
		if(!im || SCOM_FAILED(im->CreateInstance(UUID_PPV(Input::IInputController, mInputController.wrapped()))))
		{		
			LogErrorAlways("Failed to create input controller");
			return false;
		}
		else
		{
			mEngineEnvironment.InputController = mInputController;
		}

		// Create renderer
		Core::IPluginShadow* myShadow = Core::CommonPlugin::Instance->PluginShadow();
		Core::IExtensionPoint* ep = myShadow->FindExtensionPoint("renderers");
		size_t nextensions = ep->getExtensionCount();

		for(size_t i = 0; i != nextensions; ++i)
		{
			// Create first renderer found
			ep->getExtension(i)->Extender()->CreateInstance(UUID_PPV(Graphics::IRenderer, mRenderer.wrapped()));
			if(mRenderer)
			{
				mEngineEnvironment.Renderer = mRenderer;
				break;
			}
		}

		if(!mRenderer)
		{
			LogErrorAlways("Failed to create suitable renderer");
			return false;
		}


		// Create UI manager
		/// \todo refactor to extension point like renderer
		Core::IPluginShadow* ui = gEnv->PluginManager->FindPluginShadow("engine.ui");
		if(!ui || SCOM_FAILED(ui->CreateInstance(UUID_PPV(UI::IUIManager, mUIManager.wrapped()))))
		{		
			LogErrorAlways("Failed to create UI manager");
			return false;
		}
		else
		{
			mEngineEnvironment.UIManager = mUIManager;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace