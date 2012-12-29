/*========================================================
* Engine_fwd.h
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#ifndef _ENGINE_FWD_H__
#define _ENGINE_FWD_H__

namespace Engine
{

	//////////////////////////////////////////////////////////////////////////
	
	class IEngine;
	class IMainLoop;
	class IFrameListener;
	struct GlobalEnvironment;

	//////////////////////////////////////////////////////////////////////////

	class IEntity;
	class IEntityObserver;
	struct SEntitySpawnParams;
	struct SEntityThinkContext;

	class IComponent;
	struct SComponentDesc;

	class ICmpAppearance;
	struct SAppearanceDesc;

	class ICmpSpatialNode;
	struct SSpatialNodeDesc;

	class ICmpPhysicalBody;
	struct SPhysicalBodyDesc;

	class ICmpLogic;
	//////////////////////////////////////////////////////////////////////////
	
	class IComponentRegistry;
	class ISceneManager;
	class IPhysicsManager;
	class ILogicController;
	class IAnimationController;
	class ITransformGraph;
	class ITransformTraverser;
	
	//////////////////////////////////////////////////////////////////////////
} // namespace

//////////////////////////////////////////////////////////////////////////
//PhysX
class NxPhysicsSDK;
class NxCookingInterface;
class NxScene;
class NxActor;
class NxActorDesc;
//////////////////////////////////////////////////////////////////////////

#endif	// _ENGINE_FWD_H__