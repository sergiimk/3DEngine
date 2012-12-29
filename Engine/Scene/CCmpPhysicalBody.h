/*========================================================
* CCmpPhysicalBody.h
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#ifndef _CCMPPHYSICALBODY_H__
#define _CCMPPHYSICALBODY_H__

#include "../Interfaces/ICmpPhysicalBody.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{
	/// Implementation of ICmpPhysicalBody component
	/** @ingroup Engine */
	class NOVTABLE CCmpPhysicalBody : 
		public Core::SCOM::ComRootObject<>,
		public ICmpPhysicalBody
	{
	public:
		
		DECLARE_IMPLEMENTATION(CCmpPhysicalBody)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ICmpPhysicalBody)
			INTERFACE_ENTRY(IComponent)
		END_INTERFACE_MAP()
	
		CCmpPhysicalBody();

		const char*			getComponentName()				const { return "PhysicalBody"; }

		IEntity*			getEntity()						const { return mEntity; }

		NxActor*			getActor()						const { return mActor; }

		EPhysicsBinding		getBindingType()				const { return mBinding; }

		void				setBindingType(EPhysicsBinding type)  { mBinding = type; }

		bool				Bind(Engine::IEntity *entity, SComponentDesc* desc);

	private:
		IEntity*		mEntity;	///< associated entity
		NxActor*		mActor;		///< PhysX actor
		EPhysicsBinding	mBinding;	///< settings of binding with physics simulation
	};

} // namespace

#endif // _CCMPPHYSICALBODY_H__