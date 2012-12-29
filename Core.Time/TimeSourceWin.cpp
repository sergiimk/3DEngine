/*========================================================
* TimeSourceWin.cpp
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
#include "TimeSourceWin.h"
#include <windows.h>

namespace Time
{
	//////////////////////////////////////////////////////////////////////////

	TimeSourceWin::TimeSourceWin()
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&mResolution);
	}

	/////////////////////////////////////////////////////////////////////////

	void TimeSourceWin::GetTicks(__int64& ticks) const
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&ticks);
	}

	//////////////////////////////////////////////////////////////////////////

	void TimeSourceWin::GetResoulution(__int64& res) const
	{
		res = mResolution;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace