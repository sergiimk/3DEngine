/*========================================================
* ISceneManager.h
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#ifndef _ISCENEMANAGER_H__
#define _ISCENEMANAGER_H__

#include "../Engine_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	/// Manages scene objects
	/** Knows about all spatial structures in the engine 
	*  and notifies them about all changes in objects'
	*  properties so that they could be properly updated
	*
	* @ingroup Engine */
	SCOM_INTERFACE(ISceneManager, "f6ab7bb9-8a79-4702-80c7-51587b9ec004", Core::SCOM::IUnknown)
	{
	public:

		/// Creates new entity
		/** New entity will have a default spatial position,
		*  its transformation node will not be linked to transformation graph,
		*  xxxxxx */
		virtual void CreateEntity(const SEntitySpawnParams& params, IEntity** outEntity) = 0;
	};

} // namespace

#endif	// _ISCENEMANAGER_H__