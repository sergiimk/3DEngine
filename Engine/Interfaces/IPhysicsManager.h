/*========================================================
* IPhysicsManager.h
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#ifndef _IPHYSICSMANAGER_H__
#define _IPHYSICSMANAGER_H__

#include "../../Core.COM/Interfaces.h"

namespace Engine
{

	/// Manages interactions between logical and physical components of the engine
	/** @ingroup Engine */
	SCOM_INTERFACE(IPhysicsManager, "541e36ad-f6ac-4f0e-9f13-778af90e7bf3", Core::SCOM::IUnknown)
	{
	public:
	
		/// Updates positions of all dynamic objects using the position data from simulation
		virtual void UpdateDynamicBindings() = 0;

		/// Updates positions of all kinematic objects using the position data from engine
		virtual void UpdateKinematicBindings() = 0;
	};

} // namespace

#endif // _IPHYSICSMANAGER_H__