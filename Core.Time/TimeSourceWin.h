/*========================================================
* TimeSourceWin.h
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
#ifndef _TIMESOURCEWIN_H__
#define _TIMESOURCEWIN_H__

#include "ITimeSource.h"

namespace Time
{
	/// Time source based on windows system time
	/** @ingroup  */
	class TimeSourceWin : public ITimeSource
	{
	public:
		TimeSourceWin();

		void GetTicks(__int64& ticks) const;

		void GetResoulution(__int64& res) const;

	private:
		__int64 mResolution;
	};

} // namespace

#endif	// _TIMESOURCEWIN_H__