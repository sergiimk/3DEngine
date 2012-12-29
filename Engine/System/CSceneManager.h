/*========================================================
* CSceneManager.h
* @author Sergey Mikhtonyuk
* @date 02 May 2009
=========================================================*/
#ifndef _CSCENEMANAGER_H__
#define _CSCENEMANAGER_H__

#include "../Scene/CEntity.h"
#include "../Interfaces/ISceneManager.h"
#include "../../Core.COM/Implementations.h"
#include "../../Core.COM/Intellectual.h"
#include <hash_set>

//////////////////////////////////////////////////////////////////////////

namespace std
{
	/// STLPort hash specialization for entities
	/** @ingroup Engine */
	template<>
	struct hash<Engine::CEntity*> 
	{
		size_t operator()(Engine::CEntity* e) const 
		{
			return (size_t)e;
		}
	};
}

//////////////////////////////////////////////////////////////////////////

namespace Engine
{

	/// Implementation of ISceneManager interface
	/** @ingroup Engine */
	class NOVTABLE CSceneManager : 
		public Core::SCOM::ComRootObject<>,
		public ISceneManager
	{
	public:
		
		DECLARE_IMPLEMENTATION(CSceneManager)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ISceneManager)
		END_INTERFACE_MAP()

		/// Ctor
		CSceneManager();

		/// Destructor
		~CSceneManager();

		void CreateEntity(const SEntitySpawnParams& params, IEntity** outEntity);

	private:
		typedef std::hash_set<CEntity*> EntityList;

		EntityList mEntities;		///< holds all entities in the game
	};

} // namespace

#endif	// _SCENEMANAGER_H__