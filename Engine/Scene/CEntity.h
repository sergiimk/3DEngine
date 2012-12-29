/*========================================================
* CEntity.h
* @author Sergey Mikhtonyuk
* @date 02 May 2009
=========================================================*/
#ifndef _CENTITY_H__
#define _CENTITY_H__

#include "../Interfaces/IEntity.h"
#include "../Interfaces/IEntityObserver.h"
#include "../../Core.COM/Implementations.h"
#include <string>
#include <vector>

namespace Engine
{

	/// Implementation of IEntity interface
	/** @ingroup Engine */
	class NOVTABLE CEntity :
		public Core::SCOM::ComRootObject<>,
		public IEntity
	{
	public:

		DECLARE_IMPLEMENTATION(CEntity)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IEntity)
		END_INTERFACE_MAP()

		/// Ctor
		CEntity();

		/// Destructor
		~CEntity();

		void				Init(const SEntitySpawnParams& params);

		const char*			getName()					const	{ return mName.c_str(); }

		size_t				getComponentsNum()			const	{ return mComponents.size(); }

		IComponent*			getComponent(size_t index)	const;

		IComponent*			getComponent(SCOM_RIID id)	const;

		void				AddComponent(IComponent* component);

		void				RemoveComponent(IComponent* component);

		void				ClearComponents();

		void				AddObserver(IEntityObserver* obs);

		void				RemoveObserver(IEntityObserver* obs);

	private:

		void				NotifyObservers(EEntityChangeType type, void* args);

	private:

		std::string						mName;			///< name of the entity

		std::vector<IComponent*>		mComponents;	///< components of the entity

		std::vector<IEntityObserver*>	mObservers;		///< entity observers
	};

} // namespace

#endif	// _CENTITY_H__