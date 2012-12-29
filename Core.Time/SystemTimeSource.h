/*========================================================
* SystemTimeSource.h
* @author Sergey Mikhtonyuk
* @date 12 June 2009
=========================================================*/
#ifndef _SYSTEMTIMESOURCE_H__

#include "../Core.Utils/EnvironmentDefs.h"



#if defined(OS_WINDOWS)
#	include "TimeSourceWin.h"

	namespace Time
	{
		typedef TimeSourceWin SystemTimeSource;
	} // namespace

#else
#	error No suitable time source for this OS
#endif

#endif