/*========================================================
* ICmpPhysicalBody.h
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#ifndef _ICMPPHYSICALBODY_H__
#define _ICMPPHYSICALBODY_H__

#include "IComponent.h"
#include "../Engine_fwd.h"
#include "../Engine_classid.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	enum EPhysicsBinding
	{
		PHYS_BINDING_DISABLED,	///< No binding
		PHYS_BINDING_AUTO,		///< Automatically determines actor type and chooses binding direction
	};

	//////////////////////////////////////////////////////////////////////////

	/// Built-in entity component. Represents physical properties of the entity
	/** @ingroup Engine */
	SCOM_INTERFACE(ICmpPhysicalBody, "8a5c5eb6-ca70-4f17-8555-a76204b4ea0d", IComponent)
	{
	public:
	
		/// Returns PhysX actor
		virtual NxActor* getActor() const = 0;

		/// Returns the binding type of physics simulation
		virtual EPhysicsBinding getBindingType() const = 0;

		/// Sets the binding type of physics simulation
		virtual void setBindingType(EPhysicsBinding type) = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Appearance component description, used for component instantiation
	/** @ingroup Engine */
	struct SPhysicalBodyDesc : public SComponentDesc
	{
		NxActorDesc*		ActorDescs;		///< Description of physical body

		SPhysicalBodyDesc()
			:	SComponentDesc(&CLSID_CCmpPhysicalBody),
				ActorDescs(0)
		{}

		SPhysicalBodyDesc(NxActorDesc* actor_desc)
			:	SComponentDesc(&CLSID_CCmpPhysicalBody),
				ActorDescs(actor_desc)
		{}

		void ResetDefaults() { ActorDescs = 0; }
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ICMPPHYSICALBODY_H__