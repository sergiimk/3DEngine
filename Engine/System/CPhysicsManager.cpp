/*========================================================
* CPhysicsManager.cpp
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/

#include "CPhysicsManager.h"
#include "../Engine.h"
#include "../../Core.Math/VML.h"
#include "../../Core.Logging/ILogger.h"
#include <NxPhysics.h>
#include <NxCooking.h>

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CPhysicsManager::CPhysicsManager()
	{
		// SDK
		gEnv->PhysX = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
		if(!gEnv->PhysX)
		{
			/// \todo add engine exceptions
			LogErrorAlways("Failed to create PhysX instance");
			ASSERT_STRICT(false);
			throw 1;
		}
		gEnv->PhysX->setParameter(NX_SKIN_WIDTH, 0.05f);
		//gEnv->PhysX->getFoundationSDK().getRemoteDebugger()->connect ("localhost", 5425);

		// Scene
		NxSceneDesc sd;
		sd.gravity.set(0, -9.8f, 0);
		gEnv->PhysXScene = gEnv->PhysX->createScene(sd);
		if(!gEnv->PhysXScene)
		{
			LogErrorAlways("Failed to create PhysX scene");
			ASSERT_STRICT(false);
			throw 1;
		}

		// Set default material
		NxMaterial* defaultMaterial = gEnv->PhysXScene->getMaterialFromIndex(0);
		defaultMaterial->setRestitution(0.0f);
		defaultMaterial->setStaticFriction(0.5f);
		defaultMaterial->setDynamicFriction(0.5f);

		// Cooking
		gEnv->PhysXCooking = NxGetCookingLib(NX_PHYSICS_SDK_VERSION);
		if(!gEnv->PhysXCooking)
		{
			LogErrorAlways("Failed to create PhysX cooking library");
			ASSERT_STRICT(false);
			throw 1;
		}
		gEnv->PhysXCooking->NxInitCooking();
	}

	//////////////////////////////////////////////////////////////////////////

	CPhysicsManager::~CPhysicsManager()
	{
		gEnv->PhysX->release();
		gEnv->PhysXCooking->NxCloseCooking();
		gEnv->PhysX = 0;
		gEnv->PhysXScene = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	class PhysUpdateDynamic : public ITransformTraverser
	{
	public:
		void TraversingStarted(ITransformGraph* tg) {}
		void TraversingEnd(ITransformGraph* tg) {}

		bool VisitNode(ICmpSpatialNode* node, IEntity* entity) 
		{
			ICmpPhysicalBody* body = (ICmpPhysicalBody*)entity->getComponent(UUIDOF(ICmpPhysicalBody));
			if(!body) return true;
			NxActor* actor = body->getActor();

			const char* name = entity->getName();
			if(!actor->readBodyFlag(NX_BF_KINEMATIC))
			{
				NxVec3 position = actor->getGlobalPosition();
				NxQuat rot = actor->getGlobalOrientationQuat();

				node->setPosition(VML::Vector3(position.x, position.y, position.z));
				node->setRotation(VML::Quat(rot.x, rot.y, rot.z, rot.w));
			}

			return true;
		}

		void LeaveNode(ICmpSpatialNode* node, IEntity* entity) {}
	};

	//////////////////////////////////////////////////////////////////////////

	class PhysUpdateKinematic : public ITransformTraverser
	{
	public:
		void TraversingStarted(ITransformGraph* tg) {}
		void TraversingEnd(ITransformGraph* tg) {}

		bool VisitNode(ICmpSpatialNode* node, IEntity* entity) 
		{
			ICmpPhysicalBody* body = (ICmpPhysicalBody*)entity->getComponent(UUIDOF(ICmpPhysicalBody));
			if(!body) return true;
			NxActor* actor = body->getActor();

			const char* name = entity->getName();
			if(actor->readBodyFlag(NX_BF_KINEMATIC))
			{
				NxVec3 position((float* const)&node->getPosition().get128());
				VML::Quat r = node->getRotation();
				NxQuat rot;
				rot.setXYZW(r.getX(), r.getY(), r.getZ(), r.getW());
				actor->moveGlobalPosition(position);
				actor->moveGlobalOrientationQuat(rot);
			}

			return true;
		}

		void LeaveNode(ICmpSpatialNode* node, IEntity* entity) {}
	};

	//////////////////////////////////////////////////////////////////////////

	void CPhysicsManager::UpdateDynamicBindings()
	{
		PhysUpdateDynamic tr;
		gEnv->TransformGraph->AcceptTraverser(&tr);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPhysicsManager::UpdateKinematicBindings()
	{
		PhysUpdateKinematic tr;
		gEnv->TransformGraph->AcceptTraverser(&tr);
	}

	//////////////////////////////////////////////////////////////////////////
} // namespace