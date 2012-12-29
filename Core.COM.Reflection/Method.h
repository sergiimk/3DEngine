/*========================================================
* Method.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#ifndef _METHOD_H__
#define _METHOD_H__

#include "ClassDescriptor.h"
#include "FunctionType.h"


namespace Reflection
{

	/// Represents class method
	/** @ingroup Reflection */
	class Method : public ClassDescriptor
	{
	public:

		/// Ctor
		Method(const char* name, Type* type, Type* owner, DelegateBase* deleg)
			: ClassDescriptor(name, type, owner, RL_DESC_METHOD), mDelegate(deleg)
		{
		}

		/// Destructor
		~Method()
		{
			delete mDelegate;
		}

		/// Invokes the method, first argument should be class instance
		void Invoke(void** args, void* result) const
		{
			((FunctionType*)getType())->Invoke(mDelegate, args, result);
		}

	private:
		DelegateBase* mDelegate;
	};

} // namespace

#endif // _METHOD_H__