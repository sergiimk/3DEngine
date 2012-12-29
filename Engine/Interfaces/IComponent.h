/*========================================================
* IComponent.h
* @author Sergey Mikhtonyuk
* @date 29 June 2009
=========================================================*/
#ifndef _ICOMPONENT_H__
#define _ICOMPONENT_H__

#include "../Engine_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	/// Base interface to entity components
	/** Components are used to add properties and functionality to
	 *  the game objects in dynamic way. It also accomplishes strict
	 *  separation of concerns and blob interfaces.
	 *  @ingroup Engine */
	SCOM_INTERFACE(IComponent, "e9ffbd55-b103-4033-ac0a-ba0b9edadf2f", Core::SCOM::IUnknown)
	{
	public:
		
		/// Returns the component name
		virtual const char* getComponentName()	const = 0;

		/// Returns the entity which this one is component of
		virtual IEntity*	getEntity()			const = 0;

		/// Called by component manager to finish the component attachment to entity
		/** @param entity owner of the component
		 *  @param desc component description
		 *  @return if component will return false this means binding failed, and it can't be bound to this entity */
		virtual bool		Bind(IEntity* entity, SComponentDesc* desc)    = 0;
	};


	//////////////////////////////////////////////////////////////////////////


	/// Base type for all component descriptions, used by component manager to check the Component type.
	/** @ingroup Engine */
	struct SComponentDesc
	{
		const Core::SCOM::GUID* ComponentID;

		/** @param componentID ClassID of the component implementation */
		SComponentDesc(const Core::SCOM::GUID* componentID) : ComponentID(componentID) { }
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ICOMPONENT_H__
