/*========================================================
* CEntity.cpp
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#include "CEntity.h"
#include "../Interfaces/IComponent.h"
#include "../../Engine.Graphics/Interfaces/IMesh.h"
#include "../Interfaces/SEntitySpawnParams.h"
#include <algorithm>

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CEntity::CEntity()
	{ }

	//////////////////////////////////////////////////////////////////////////

	CEntity::~CEntity()
	{
		NotifyObservers(ECT_DESTROYING, 0);
		mObservers.clear();
		ClearComponents();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::Init(const SEntitySpawnParams& params)
	{
		mName = params.Name;
	}

	//////////////////////////////////////////////////////////////////////////

	IComponent* CEntity::getComponent(size_t index) const
	{
		return mComponents[index];
	}

	//////////////////////////////////////////////////////////////////////////

	IComponent* CEntity::getComponent(SCOM_RIID id) const
	{
		for(size_t i = 0; i != mComponents.size(); ++i)
		{
			IComponent* ppv = 0;
			mComponents[i]->QueryInterface(id, (void**) &ppv);
			
			if(ppv)
			{
				ppv->Release();
				return mComponents[i];
			}
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::AddComponent(IComponent *component)
	{
		mComponents.push_back(component);
		component->AddRef();

		NotifyObservers(ECT_COMPONENT_ADDED, component);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::RemoveComponent(Engine::IComponent *component)
	{
		std::vector<IComponent*>::iterator it = 
			std::find(mComponents.begin(), mComponents.end(), component);

		if(it != mComponents.end())
		{
			NotifyObservers(ECT_COMPONENT_REMOVED, component);
			mComponents.erase(it);
			component->Release();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::ClearComponents()
	{
		for(size_t i = 0; i != mComponents.size(); ++i)
		{
			NotifyObservers(ECT_COMPONENT_REMOVED, mComponents[i]);
			mComponents[i]->Release();
		}
		
		mComponents.clear();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::AddObserver(IEntityObserver* obs)
	{
		mObservers.push_back(obs);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::RemoveObserver(Engine::IEntityObserver *obs)
	{
		std::vector<IEntityObserver*>::iterator it = 
			std::find(mObservers.begin(), mObservers.end(), obs);

		if(it != mObservers.end())
			mObservers.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEntity::NotifyObservers(EEntityChangeType type, void *args)
	{
		for(size_t i = 0; i != mObservers.size(); ++i)
			mObservers[i]->OnEntityChanged(type, args);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace