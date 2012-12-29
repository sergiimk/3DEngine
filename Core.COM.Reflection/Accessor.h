/*========================================================
* Accessor.h
* @author Sergey Mikhtonyuk
* @date 23 June 2009
=========================================================*/
#ifndef _ACCESSOR_H__
#define _ACCESSOR_H__

#include "DataDescriptor.h"
#include "FunctionType.h"

namespace Reflection
{

	/// Descriptor of data hidden behind get/set methods
	/** @ingroup Reflection */
	class Accessor : public DataDescriptor
	{
	public:

		/// Ctor
		Accessor(	const char* name, Type* owner, Type* getter, Type* setter, 
					DelegateBase* dgetter, DelegateBase* dsetter)
			:	DataDescriptor(name, ((FunctionType*)getter)->getReturnType(), owner, RL_DESC_ACCESSOR), 
				mGetter((FunctionType*)getter), 
				mSetter((FunctionType*)setter),
				mDelegGetter(dgetter),
				mDelegSetter(dsetter)

		{
		}

		/// Destructor
		~Accessor()
		{
			delete mDelegGetter;
			delete mDelegSetter;
		}

		/// Checks if data is read-only (no setter)
		bool isReadOnly() const { return mSetter == 0; }

		/// Gets the value through getter
		void getValue(void* inst, void* buffer) const
		{
			void* args[] = { &inst };
			mGetter->Invoke(mDelegGetter, args, buffer);
		}

		/// Sets the value through setter
		void setValue(void* inst, void* buffer) const
		{
			assert(!isReadOnly());
			if(isReadOnly()) return;

			void* args[] = { &inst, buffer };
			mSetter->Invoke(mDelegSetter, args, 0);
		}

		/// Returns type of getter function
		FunctionType* getGetterType() const { return mGetter; }

		/// Returns type of setter function
		FunctionType* getSetterType() const { return mSetter; }

	private:
		FunctionType* mGetter;
		FunctionType* mSetter;
		DelegateBase* mDelegGetter;
		DelegateBase* mDelegSetter;
	};

} // namespace

#endif // _ACCESSOR_H__
