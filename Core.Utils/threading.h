/*========================================================
* threading.h
* @author Sergey Mikhtonyuk
* @date 22 April 2009
=========================================================*/
#ifndef _THREADING_H__
#define _THREADING_H__

//////////////////////////////////////////////////////////////////////////

#include "EnvironmentDefs.h"

#if defined (COMPILER_MSC)
#	include <intrin.h>
#endif

//////////////////////////////////////////////////////////////////////////

namespace Utils
{

	//////////////////////////////////////////////////////////////////////////

	/// Thread-safe increment
	/** @ingroup Utils */
	inline void AtomicIncrement(volatile long* pl)
	{
		#if defined (COMPILER_MSC)
			_InterlockedIncrement(pl);
		#else
			#error no suitable implementation for your compiler
		#endif
	}

	//////////////////////////////////////////////////////////////////////////

	/// Thread-safe decrement
	/** @ingroup Utils */
	inline void AtomicDecrement(volatile long* pl)
	{
		#if defined (COMPILER_MSC)
			_InterlockedDecrement(pl);
		#else
			#error no suitable implementation for your compiler
		#endif
	}

} // namespace

#endif // _THREADING_H__