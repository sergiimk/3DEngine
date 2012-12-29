/*========================================================
* ConstructDescriptor.h
* @author Sergey Mikhtonyuk
* @date 09 July 2009
=========================================================*/
#ifndef _CONSTRUCTDESCRIPTOR_H__
#define _CONSTRUCTDESCRIPTOR_H__

#include "ClassDescriptor.h"
#include "typeof.h"

namespace Reflection
{

	/// Describes that class supports CreateInstance() and DestroyInstance() operations
	/** @ingroup Reflection */
	class ConstructDescriptor : public ClassDescriptor
	{
	public:
		typedef void* (*TCtor)();
		typedef void (*TDtor)(void*);

		ConstructDescriptor(TCtor c, TDtor d, Type* owner)
			: ClassDescriptor("io_support", type_of<void>(), owner, RL_DESC_SERVICE_CONSTRUCT),
			mCtor(c), mDtor(d)
		{
		}

		/// Creates type instance
		void* CreateInstance() const
		{
			return mCtor();
		}

		/// Creates type instance
		void DestroyInstance(void* v) const
		{
			mDtor(v);
		}

	private:
		TCtor mCtor;
		TDtor mDtor;
	};

} // namespace

#endif // _CONSTRUCTDESCRIPTOR_H__