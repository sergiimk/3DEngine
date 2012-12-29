/*========================================================
* GlobalEnvironment.h
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#ifndef _ENGINE_GLOBALENVIRONMENT_H__
#define _ENGINE_GLOBALENVIRONMENT_H__

#include "../../Core/GlobalEnvironment.h"
#include "../Engine_fwd.h"
#include "../../Engine.Input/Input_fwd.h"
#include "../../Engine.Graphics/Graphics_fwd.h"
#include "../../Engine.UI/UI_fwd.h"

namespace Engine
{
	/// Extension of Core::GlobalEnvironment that gives access to Engine subsystems
	/** @ingroup Engine */
	struct GlobalEnvironment : public Core::GlobalEnvironment
	{
		IEngine*					Engine;				///< Engine instance
		IMainLoop*					MainLoop;			///< Main loop pointer
		Input::IInputController*	InputController;	///< Input device controller
		IComponentRegistry*			ComponentRegistry;	///< Registry for components (subparts of the entity)
		ISceneManager*				SceneManager;		///< Scene manager instance
		UI::IUIManager*				UIManager;			///< User interface manager instance
		IPhysicsManager*			PhysicsManager;		///< Physics manager instance
		ITransformGraph*			TransformGraph;		///< Transform hierarchy graph
		ILogicController*			LogicController;	///< Drives the process of 'think' notifications
		IAnimationController*		AnimationController;///< Manages interpolation and animation

		Graphics::IRenderer*		Renderer;			///< Renderer pointer
		Graphics::IMaterialManager*	MaterialManager;	///< Renderer's material manager
		Graphics::IEffectManager*	EffectManager;		///< Renderer's effect manager
		Graphics::ISurfaceManager*	SurfaceManager;		///< Renderer's surface manager
		Graphics::IGeometryManager*	GeometryManager;	///< Renderer's geometry manager

		NxPhysicsSDK*				PhysX;				///< PhysX SDK object instance
		NxScene*					PhysXScene;			///< Main PhysX scene object
		/// \todo Cooking should be done offline
		NxCookingInterface*			PhysXCooking;		///< Cooking library
	};

	//////////////////////////////////////////////////////////////////////////
	extern GlobalEnvironment* gEnv;											//
	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif	// _ENGINE_GLOBALENVIRONMENT_H__