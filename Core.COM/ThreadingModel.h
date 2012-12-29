/*========================================================
* ThreadingModel.h
* @author Sergey Mikhtonyuk
* @date 22 April 2009
=========================================================*/
#ifndef _THREADINGMODEL_H__
#define _THREADINGMODEL_H__

#include "../Core.Utils/threading.h"

namespace Core
{
	namespace SCOM
	{
		//! Single-threading model for ComRootObject
		/** @ingroup SCOM */
		struct SingleThreadModel
		{
			static void Increment(long& l) { ++l; }
			static void Decrement(long& l) { --l; }
		};

		//! Multi-threading model for ComRootObject
		/** @ingroup SCOM */
		struct MultiThreadModel
		{
			static void Increment(long& l) { Utils::AtomicIncrement(&l); }
			static void Decrement(long& l) { Utils::AtomicDecrement(&l); }
		};	
	} // namespace
} // namespace


#endif // _THREADINGMODEL_H__