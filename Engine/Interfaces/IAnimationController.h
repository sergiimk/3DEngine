/*========================================================
* IAnimationController.h
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#ifndef _IANIMATIONCONTROLLER_H__
#define _IANIMATIONCONTROLLER_H__

#include "../../Core.COM/Interfaces.h"
#include "../../Core.Time/Time_fwd.h"

namespace Engine
{

	/// Manages interpolator and animators
	/** @ingroup Engine */
	SCOM_INTERFACE(IAnimationController, "6242fdf2-1922-4747-b769-b5a135354bd6", Core::SCOM::IUnknown)
	{
	public:
	
		/// Creates interpolator with specified type
		virtual Time::IInterpolator* CreateInterpolator(Time::EInterpolatorType type) = 0;
	};

} // namespace

#endif // _IANIMATIONCONTROLLER_H__