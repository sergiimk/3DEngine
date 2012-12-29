/*========================================================
* CEngine.h
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#ifndef _CENGINE_H__
#define _CENGINE_H__

#include "../Interfaces/IEngine.h"
#include "../Interfaces/GlobalEnvironment.h"
#include "../../Core.COM/Implementations.h"
#include "../../Core.COM/Intellectual.h"

namespace Engine
{

	/// Implementation of IEngine interface
	/** @ingroup Engine */
	class NOVTABLE CEngine : 
		public Core::SCOM::ComRootObject<>,
		public IEngine
	{
	public:
		DECLARE_IMPLEMENTATION(CEngine)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IEngine)
			INTERFACE_ENTRY(Core::IStartListener)
		END_INTERFACE_MAP()

		CEngine();
		~CEngine();

		void						OnStart(int argc, char *argv[]);
		GlobalEnvironment*			Environment() const;
		IComponentRegistry*			getComponentRegistry() const;
		ISceneManager*				getSceneManager() const;
		UI::IUIManager*				getUIManager() const;
		IPhysicsManager*			getPhysicsManager() const;
		ITransformGraph*			getTransformGraph() const;
		ILogicController*			getLogicController() const;
		IAnimationController*		getAnimationController() const;
		Graphics::IRenderer*		getRenderer() const;
		Input::IInputController*	getInputController() const;

	private:
		bool						InitSubsystems();

	private:
		GlobalEnvironment							mEngineEnvironment;
		Core::SCOM::ComPtr<IMainLoop>				mMainLoop;
		Core::SCOM::ComPtr<IComponentRegistry>		mComponentRegistry;
		Core::SCOM::ComPtr<ISceneManager>			mSceneManager;
		Core::SCOM::ComPtr<UI::IUIManager>			mUIManager;
		Core::SCOM::ComPtr<IPhysicsManager>			mPhysicsManager;
		Core::SCOM::ComPtr<ITransformGraph>			mTransformGraph;
		Core::SCOM::ComPtr<ILogicController>		mLogicController;
		Core::SCOM::ComPtr<IAnimationController>	mAnimationController;
		Core::SCOM::ComPtr<Graphics::IRenderer>		mRenderer;
		Core::SCOM::ComPtr<Input::IInputController> mInputController;
	};

} // namespace

#endif	// _CENGINE_H__