/*========================================================
* CCmpPhysicalBody.cpp
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#include "CCmpPhysicalBody.h"
#include "../Interfaces/IEntity.h"
#include "../Interfaces/GlobalEnvironment.h"
#include "../Interfaces/IPhysicsManager.h"
#include "../../Core.Logging/ILogger.h"
#include <NxPhysics.h>

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CCmpPhysicalBody::CCmpPhysicalBody()
		: mActor(0), mEntity(0), mBinding(PHYS_BINDING_AUTO)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	bool CCmpPhysicalBody::Bind(Engine::IEntity *entity, SComponentDesc* desc)
	{
		mEntity = entity;
		SPhysicalBodyDesc* pbd = (SPhysicalBodyDesc*)desc;
		
		if(pbd->ActorDescs)
		{
			NxActor* actor = gEnv->PhysXScene->createActor(*pbd->ActorDescs);
			
			if(!actor)
			{
				LogError("Failed to create physical body for : %s", entity->getName());
				return false;
			}
			
			mActor = actor;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace