/*========================================================
* ICore.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
=========================================================*/

#ifndef _ICORE_H__
#define _ICORE_H__

#include "Core_fwd.h"
#include "../Core.COM/Interfaces.h"

namespace Core
{
	/// ICore interface
	/** Facade interface to all subsystems
	 *  @ingroup Core */
	SCOM_INTERFACE(ICore, "58CC46C4-647C-42d6-9D41-73A981B3A5A2", SCOM::IUnknown)
	{
	public:
		/// Initializes all subsystems, loads plugin manager that parses all plugin definitions
		/** @param paramsFile file that specifies core settings */
		virtual void Initialize(const char* paramsFile = 0) = 0;

		/// Launches execution (loads and notifies all start listeners
		/** @see IStartListener */
		virtual void StartExecution(int argc, char *argv[]) = 0;

		/// Returns current environment pointer
		virtual GlobalEnvironment* Environment() const = 0;

		/// Registers new environment for all newly-created plug-ins
		/** It inits GlobalEnvironment part as initial environment so that no substitution happened 
		*  @param newEnv	pointer to the extended environment */
		virtual void RegisterEnvironment(GlobalEnvironment* newEnv) = 0;
	};

}

#endif // _ICORE_H__
