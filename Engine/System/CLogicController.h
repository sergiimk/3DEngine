/*========================================================
* CLogicController.h
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#ifndef _CLOGICCONTROLLER_H__
#define _CLOGICCONTROLLER_H__

#include "../Interfaces/ILogicController.h"
#include "../../Core.COM/Implementations.h"
#include <hash_set>

//////////////////////////////////////////////////////////////////////////

namespace std
{
	/// STLPort hash specialization for logic components
	/** @ingroup Engine */
	template<>
	struct hash<Engine::ICmpLogic*> 
	{
		size_t operator()(Engine::ICmpLogic* l) const 
		{
			return (size_t)l;
		}
	};
}

//////////////////////////////////////////////////////////////////////////


namespace Engine
{

	/// Implementation of logic controller
	/** @ingroup Engine */
	class NOVTABLE CLogicController : 
		public Core::SCOM::ComRootObject<>,
		public ILogicController
	{
	public:
		
		DECLARE_IMPLEMENTATION(CLogicController)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ILogicController)
		END_INTERFACE_MAP()
	
		void RegisterLogicComponent(ICmpLogic* logic);

		void UnRegisterLogicComponent(ICmpLogic* logic);

		void Notify(double time_delta);

	private:
		typedef std::hash_set<ICmpLogic*> TComponentSet;
		TComponentSet mComponents;
	};

} // namespace

#endif // _CLOGICCONTROLLER_H__
