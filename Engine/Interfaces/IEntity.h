/*========================================================
* IEntity.h
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#ifndef _IENTITY_H__
#define _IENTITY_H__

#include "../Engine_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	/// Entity is a root object in component-based entity system
	/** Entity is a compound objects that stores the collection of
	 *  components, which describe the entity properties and behavior.
	 *  Composition approach was chosen to avoid the overuse of inheritance 
	 *  in game object hierarchy. Entity system allows object composition from multiple
	 *  subsets, each defining its own properties and behavior (like position, appearance, physical body etc.).
	 *
	 *  @ingroup Engine */
	SCOM_INTERFACE(IEntity, "e4c4b170-848e-4324-9411-26dac5352f22", Core::SCOM::IUnknown)
	{
	public:
		/// Returns name of this entity
		virtual const char*		getName()						const	= 0;

		/// Returns the number of entity components
		virtual size_t			getComponentsNum()				const	= 0;

		/// Returns entity component by index [0; getComponentsNum())
		virtual IComponent*		getComponent(size_t index)		const	= 0;

		/// Searches component by its ID
		virtual IComponent*		getComponent(SCOM_RIID id)		const	= 0;

		/// Add component to the entity
		virtual void			AddComponent(IComponent* component)		= 0;

		/// Remove specified component from the entity
		virtual void			RemoveComponent(IComponent* component)	= 0;

		/// Removes all components from the entity
		virtual void			ClearComponents()						= 0;

		/// Adds observer to notification list
		virtual void			AddObserver(IEntityObserver* obs)		= 0;

		/// Removes specified observer from notification list
		virtual void			RemoveObserver(IEntityObserver* obs)	= 0;
	};

} // namespace

#endif	// _IENTITY_H__