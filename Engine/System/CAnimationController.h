/*========================================================
* CAnimationController.h
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#ifndef _CANIMATIONCONTROLLER_H__
#define _CANIMATIONCONTROLLER_H__

#include "../Interfaces/IAnimationController.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{

	/// Implementation of IAnimationController
	/** @ingroup Engine */
	class NOVTABLE CAnimationController : 
		public Core::SCOM::ComRootObject<>,
		public IAnimationController
	{
	public:
		
		DECLARE_IMPLEMENTATION(CAnimationController)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IAnimationController)
		END_INTERFACE_MAP()
	
		Time::IInterpolator* CreateInterpolator(Time::EInterpolatorType type);
	};

} // namespace

#endif // _CANIMATIONCONTROLLER_H__