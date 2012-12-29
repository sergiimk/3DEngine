/*========================================================
* DataDescriptor.h
* @author Sergey Mikhtonyuk
* @date 25 June 2009
=========================================================*/
#ifndef _DATADESCRIPTOR_H__
#define _DATADESCRIPTOR_H__

#include "ClassDescriptor.h"

namespace Reflection
{
	/// Abstraction above field and accessor for uniform use
	/** @ingroup Reflection */
	class DataDescriptor : public ClassDescriptor
	{
	public:
		DataDescriptor(const char* name, Type* type, Type* owner, DescriptorType dt)
			: ClassDescriptor(name, type, owner, dt)
		{
		}

		/// Copies the field value to buffer
		virtual void getValue(void* inst, void* buffer) const = 0;

		/// Sets the value from one in the buffer
		virtual void setValue(void* inst, void* buffer) const = 0;
	};

} // namespace

#endif // _DATADESCRIPTOR_H__