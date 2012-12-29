/*========================================================
* CCore.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
=========================================================*/
#ifndef _CORE_H__
#define _CORE_H__

#include "ICore.h"
#include "GlobalEnvironment.h"
#include "../Core.COM/Implementations.h"

namespace Core
{

	/// Core class implementation
	/** Implements facade class to all subsystems
	 *  @ingroup Core */
	class NOVTABLE CCore : 
		public SCOM::ComRootObject<>,
		public ICore
	{
	public:

		DECLARE_IMPLEMENTATION2(CCore, SCOM::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ICore)
		END_INTERFACE_MAP()

		/// Ctor
		CCore();

		/// Destructor
		virtual ~CCore();

		void Initialize(const char* paramsFile);

		void StartExecution(int argc, char *argv[]);

		GlobalEnvironment* Environment() const { return pCurrentEnvironment; }

		void RegisterEnvironment(GlobalEnvironment* newEnv);

		/// Execution wrapped with exception handlers
		void	StartExecution_actual(int argc, char *argv[]);

	private:
		GlobalEnvironment	mEnvironment;			///< Base global environment structure
		GlobalEnvironment*	pCurrentEnvironment;	///< Current environment pointer
	};

}

#endif // _CORE_H__