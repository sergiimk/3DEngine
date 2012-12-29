/*========================================================
* ClassDescriptor.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#ifndef _CLASSDESCRIPTOR_H__
#define _CLASSDESCRIPTOR_H__

#include "Type.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	enum DescriptorType
	{
		RL_DESC_BASE,
		RL_DESC_FIELD,
		RL_DESC_METHOD,
		RL_DESC_ACCESSOR,
		RL_DESC_SERVICE_PARSING,
		RL_DESC_SERVICE_CONSTRUCT,
		RL_DESC_SERVICE_ASSIGN,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Base class for class members
	/** @ingroup Reflection */
	class ClassDescriptor
	{
	public:
		/// Ctor
		ClassDescriptor(const char* name, Type* type, Type* owner, DescriptorType dt)
			: mName(name), mType(type), mOwner(owner), mDescType(dt)
		{
		}

		virtual ~ClassDescriptor() {}

		/// Returns the name of the descriptor
		const char* getName() const { return mName; }

		/// Returns the type of the descriptor
		Type* getType() const { return mType; }

		/// Returns the type of the owner class
		Type* getOwnerClass() const { return mOwner; }

		/// Returns type of the descriptor
		DescriptorType getDescriptorType() const { return mDescType; }

	private:
		const char*		mName;
		Type*			mType;
		Type*			mOwner;
		DescriptorType	mDescType;
	};

} // namespace

#endif // _CLASSDESCRIPTOR_H__