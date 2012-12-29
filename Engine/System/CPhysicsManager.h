/*========================================================
* CPhysicsManager.h
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#ifndef _CPHYSICSMANAGER_H__
#define _CPHYSICSMANAGER_H__

#include "../Interfaces/IPhysicsManager.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{

	/// Implementation of IPhysicsManager interface
	/** @ingroup Engine */
	class NOVTABLE CPhysicsManager : 
		public Core::SCOM::ComRootObject<>,
		public IPhysicsManager
	{
	public:
		
		DECLARE_IMPLEMENTATION(CPhysicsManager)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IPhysicsManager)
		END_INTERFACE_MAP()
	
		CPhysicsManager();

		~CPhysicsManager();

		void UpdateDynamicBindings();

		void UpdateKinematicBindings();
	};

} // namespace

#endif // _CPHYSICSMANAGER_H__