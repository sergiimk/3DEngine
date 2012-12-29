/*========================================================
* ICmpLogic.h
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#ifndef _ICMPLOGIC_H__
#define _ICMPLOGIC_H__

#include "IComponent.h"
#include "../Engine_fwd.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	/// Think strategy flags
	/** @ingroup Engine */
	enum EThinkFlags
	{
		THINK_EACH_FRAME,	///< System should call think function each frame
		THINK_SCHEDULED,	///< System should call think function when NextThinkTime will come
		THINK_NEVER,		///< Component will be removed from thinking queue
	};

	//////////////////////////////////////////////////////////////////////////

	/// Think stats of entity
	/** @ingroup Engine */
	struct SThinkContext
	{
		/// Control flags for logic system
		EThinkFlags		Flags;
		
		/// Next scheduled think time (will be decreased each frame and called when reaches zero)
		double			NextThinkTime;	

		/// Time since think was called last
		double			TimeSinceLastThink;	
	};

	//////////////////////////////////////////////////////////////////////////

	/// Logical component of the entity
	/** @ingroup Engine */
	SCOM_INTERFACE(ICmpLogic, "7c8e207b-f567-4a40-be94-52f697b4eef1", IComponent)
	{
	public:
	
		/// Returns the think context of the entity
		virtual SThinkContext* getThinkContext() = 0;

		/// Sets the new think type
		virtual void setThinkFlag(EThinkFlags flag) = 0;

		/// Starts logic processing
		virtual void Think() = 0;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ICMPLOGIC_H__