/*========================================================
* IEngine.h
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#ifndef _IENGINE_H__
#define _IENGINE_H__

#include "../Engine_fwd.h"
#include "../../Engine.Graphics/Graphics_fwd.h"
#include "../../Engine.Input/Input_fwd.h"
#include "../../Engine.UI/UI_fwd.h"
#include "../../Core/IStartListener.h"

namespace Engine
{

	/// Facade interface to all subsystems, responsible for system initialization and shutdown
	/** @ingroup Engine */
	SCOM_INTERFACE(IEngine, "309b689c-76a9-4541-b2f8-7e0552c6196e", Core::IStartListener)
	{
	public:
		/// Returns engine environment pointer
		virtual GlobalEnvironment* Environment() const = 0;

		/// Returns component registry instance
		virtual IComponentRegistry* getComponentRegistry() const = 0;

		/// Returns scene manager instance
		virtual ISceneManager* getSceneManager() const = 0;

		/// Returns user interface manager instance
		virtual UI::IUIManager* getUIManager() const = 0;

		/// Returns physics manager instance
		virtual IPhysicsManager* getPhysicsManager() const = 0;

		/// Hierarchical transform tree
		virtual ITransformGraph* getTransformGraph() const = 0;

		/// Logic component controller
		virtual ILogicController* getLogicController() const = 0;

		/// Animation controller
		virtual IAnimationController* getAnimationController() const = 0;

		/// Current renderer
		virtual Graphics::IRenderer* getRenderer() const = 0;

		/// Returns input controller device
		virtual Input::IInputController* getInputController() const = 0;
	};

} // namespace

#endif	// _IENGINE_H__