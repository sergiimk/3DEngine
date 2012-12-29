/*========================================================
* SEntitySpawnParams.h
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#ifndef _SENTITYSPAWNPARAMS_H__
#define _SENTITYSPAWNPARAMS_H__

#include "../Engine_fwd.h"
#include <vector>

namespace Engine
{
	/// Stores parameters for entity creation
	/** @ingroup Engine */
	struct SEntitySpawnParams
	{
		/// Name of the entity
		const char* Name;
		
		/// Descriptions of components that should be created with entity
		std::vector<SComponentDesc*> ComponentDescs;

		/// Ctor, initializes params with default values
		SEntitySpawnParams()
			:	Name("")
		{ }

		/// Resets parameters to default values, used to reuse the params for multiple entities
		void ResetDefaults()
		{
			Name = "";
			ComponentDescs.clear();
		}
	};

} // namespace

#endif	// _SENTITYSPAWNPARAMS_H__