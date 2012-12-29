/*========================================================
* Field.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#ifndef _FIELD_H__
#define _FIELD_H__

#include "DataDescriptor.h"

namespace Reflection
{
	/// Represents class field
	/** @ingroup Reflection */
	class Field : public DataDescriptor
	{
	public:

		/// Ctor
		Field(const char* name, Type* type, Type* owner, size_t offset)
			: DataDescriptor(name, type, owner, RL_DESC_FIELD), mOffset(offset)
		{
		}

		void getValue(void* inst, void* buffer) const
		{
			void* pobj = (char*)inst + mOffset;
			getType()->Assign(buffer, pobj);
		}

		void setValue(void* inst, void* buffer) const
		{
			void* pobj = (char*)inst + mOffset;
			getType()->Assign(pobj, buffer);
		}

		/// Converts value to string
		bool ToString(void * value, std::string& out) const
		{
			void* pobj = (char*)value + mOffset;
			return getType()->ToString(pobj, out);
		}

		/// Restores value from string
		bool TryParse(void * inst, const char* str) const
		{
			void* pobj = (char*)inst + mOffset;
			return getType()->TryParse(pobj, str);
		}

	private:
		size_t			mOffset;
	};

} // namespace

#endif // _FIELD_H__