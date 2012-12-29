/*========================================================
* ArrayType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _ARRAYTYPE_H__
#define _ARRAYTYPE_H__

#include <stdio.h>

namespace Reflection
{

	//////////////////////////////////////////////////////////////////////////

	/// Specification for array types
	/** @ingroup Reflection */
	class ArrayType : public Type
	{
	public:
		ArrayType(Type* elemType, int elems);

		size_t Name(char* buf, size_t size) const;

		size_t FullName(char* buf, size_t size) const;

		TypeTag Tag() const { return RL_T_ARRAY; }

		size_t Size() const { return mElem->Size() * mElemCount; }

		void Assign(void* to, void* val) const { NOT_IMPLEMENTED(); }

		bool ToString(void * value, std::string& out) const;

		bool TryParse(void * value, const char* str) const { return false; }

		/// Returns the type of array elements
		Type* getElementType() const { return mElem; }

		/// Returns the number of elements in array
		int getElementNumber() const { return mElemCount; }

		ArchType getArchType() const { return RL_ARCH_ARRAY; }

		bool Equal(const Type* other) const;

		void* CreateInstance() const { NOT_IMPLEMENTED(); return 0; }

		void DestroyInstance(void* v) const { }

	private:
		int mElemCount;
		Type* mElem;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ARRAYTYPE_H__