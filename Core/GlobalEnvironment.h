/*========================================================
* GlobalEnvironment.h
* @author Sergey Mikhtonyuk
* @date 19 April 2009
=========================================================*/
#ifndef _GLOBALENVIRONMENT_H__
#define _GLOBALENVIRONMENT_H__

#include "Core_fwd.h"

namespace Core
{
	namespace FileSystem { class IFileSystem; }

	//! This struct is used for convenient access to subsystems
	/** Environment table serves for quick access to frequently used subsystems,
	*  it frees user from multiple slow queries to core.
	*
	*  It allows:
	*  - to access core subsystems, that are the same for all applications
	*  - to extend environment by subclassing and register new environment in core
	*    after this all modules instantiated afterwards will receive new pointer.
	*    This is done to define environments in layer-preserving way
	*
	*  When extending environment be sure to copy all previous content to 
	*  extended one before registering it.
	*
	*  @ingroup Core */
	struct GlobalEnvironment
	{
		ICore*						Core;			///< Core instance
		IPluginManager*				PluginManager;	///< Plug-in manager instance
		Logging::ILogger*			Logger;			///< Logger instance
		FileSystem::IFileSystem*	FileSystem;		///< FileSystem instance
	};


	//////////////////////////////////////////////////////////////////////////
	//					All plug-ins should save it							//
	extern GlobalEnvironment* gEnv;											//
	//////////////////////////////////////////////////////////////////////////

} // namespace


#endif // _GLOBALENVIRONMENT_H__