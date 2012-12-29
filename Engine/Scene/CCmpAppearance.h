/*========================================================
* CCmpAppearance.h
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#ifndef _CCMPAPPEARANCE_H__
#define _CCMPAPPEARANCE_H__

#include "../Interfaces/ICmpAppearance.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{
	/// Implementation of ICmpAppearance interface
	/** @ingroup Engine */
	class NOVTABLE CCmpAppearance : 
		public Core::SCOM::ComRootObject<>,
		public ICmpAppearance
	{
	public:
		
		DECLARE_IMPLEMENTATION(CCmpAppearance)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ICmpAppearance)
			INTERFACE_ENTRY(IComponent)
		END_INTERFACE_MAP()

		CCmpAppearance();
		~CCmpAppearance();
	
		const char*			getComponentName()	const { return "Appearance"; }

		IEntity*			getEntity()			const { return mEntity; }

		Graphics::IMesh*	getMesh()			const { return mMesh; }

		bool				Bind(IEntity* entity, SComponentDesc* desc);

	private:
		IEntity*			mEntity;
		Graphics::IMesh*	mMesh;
	};

} // namespace

#endif // _CCMPAPPEARANCE_H__