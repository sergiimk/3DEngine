/*========================================================
* CSceneManager.cpp
* @author Sergey Mikhtonyuk
* @date 02 May 2009
=========================================================*/
#include "CSceneManager.h"
#include "../Scene/CEntity.h"
#include "../Interfaces/SEntitySpawnParams.h"
#include "../Interfaces/GlobalEnvironment.h"
#include "../Interfaces/IComponent.h"
#include "../Interfaces/IComponentRegistry.h"
#include "../../Core.Logging/ILogger.h"
#include <memory>

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CSceneManager::CSceneManager()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CSceneManager::~CSceneManager()
	{
		// Release all entities in the list
		EntityList::iterator it = mEntities.begin();
		while(it != mEntities.end())
		{
			(*it)->Release();
			++it;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CSceneManager::CreateEntity(const SEntitySpawnParams& params, IEntity** outEntity)
	{
		if(outEntity) *outEntity = 0;

		// Create entity
		CEntity* ent;
		scom_new<CEntity>(&ent);
		ent->Init(params);

		if(params.ComponentDescs.size())
		{
			size_t size = params.ComponentDescs.size();
			IComponent** cmpnts = new IComponent*[size];
			memset(cmpnts, 0, sizeof(void*) * size);

			// Create components
			for(size_t i = 0; i != size; ++i)
			{
				// Try to create
				if(SCOM_FAILED(gEnv->ComponentRegistry->CreateComponent(*params.ComponentDescs[i]->ComponentID, &cmpnts[i])))
				{
					LogErrorAlways("Failed to create initial entity component");
					// Release all
					ent->Release();
					
					for(size_t j = 0; j != size; ++j)
						if(cmpnts[j]) cmpnts[j]->Release();

					delete[] cmpnts;

					return;
				}
			}

			// Bind components
			for(size_t i = 0; i != size; ++i)
			{
				if(!cmpnts[i]->Bind(ent, params.ComponentDescs[i]))
				{
					LogErrorAlways("Failed to bind initial entity component");

					// Release all
					ent->Release();

					for(size_t j = 0; j != size; ++j)
						if(cmpnts[j]) cmpnts[j]->Release();

					delete[] cmpnts;

					return;
				}

				ent->AddComponent(cmpnts[i]);
				cmpnts[i]->Release();
				cmpnts[i] = 0;				
			}

			delete[] cmpnts;
		}

		// Add new entity to the list
		mEntities.insert(ent);

		// Return new entity
		if(outEntity) *outEntity = ent;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace