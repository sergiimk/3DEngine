/*========================================================
* DelegateBase.h
* @author Sergey Mikhtonyuk
* @date 19 September 2009
=========================================================*/
#ifndef _DELEGATEBASE_H__
#define _DELEGATEBASE_H__

namespace Reflection
{
	#define DELEG_MAX_INVOKE_PARAMS 8

	class DelegateBase
	{
	};

	typedef void (*GenericInvoker)(DelegateBase*, void**, void*);

} // namespace

#endif // _DELEGATEBASE_H__