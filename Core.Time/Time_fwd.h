/*========================================================
* Time_fwd.h
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
/** @defgroup Time Time
 *  @ingroup Core */
#ifndef _TIME_FWD_H__
#define _TIME_FWD_H__

namespace Time
{
	
	class ITimeSource;
	class IClock;

	enum ETimeMode;
	enum EInterpolatorType;
	class IInterpolator;
	class IInterpolatorVec3;

} // namespace

#endif	// _TIME_FWD_H__