/*========================================================
* UserType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _USERTYPE_H__
#define _USERTYPE_H__

#include "ClassDescriptor.h"
#include "Reflection_fwd.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////
	
	/// Type specification for user-defined types (classes, structures and enums)
	/** @ingroup Reflection */
	class UserType : public Type
	{
	public:
		UserType(class_desc_base* desc);

		~UserType();

		size_t Name(char* buf, size_t size) const;

		size_t FullName(char* buf, size_t size) const;

		TypeTag Tag() const { return mClassDesc->tag; }

		size_t Size() const { return mClassDesc->size; }

		void Assign(void* to, void* val) const;

		bool ToString(void * value, std::string& out) const;

		bool TryParse(void * value, const char* str) const;

		ArchType getArchType() const { return RL_ARCH_USERDEFINED; }

		bool Equal(const Type* other) const;

		void* CreateInstance() const;

		void DestroyInstance(void* v) const;

		bool SupportsService(DescriptorType type) const;

		/// Returns number of base classes of this type
		size_t getBaseClassNumber() const { return mFirstField; }

		/// Returns number of fields of this type
		size_t getFieldNumber() const { return mFirstMethod - mFirstField; }

		/// Returns number of methods of this type
		size_t getMethodNumber() const { return mFirstAccessor - mFirstMethod; }

		/// Returns number of accessors of this type
		size_t getAccessorNumber() const { return mFirstService - mFirstAccessor; }

		/// Returns the specified base class
		BaseClass* getBaseClass(size_t index) const;

		/// Returns the specified field
		Field* getField(size_t index) const;

		/// Returns the specified method
		Method* getMethod(size_t index) const;

		/// Returns the specified accessor
		Accessor* getAccessor(size_t index) const;

		// Searches the base class by its name
		/** @param recursive specifies if indirect base classes should be considered */
		BaseClass* FindBaseClass(const char* name, bool recursive = true) const;

		// Searches the field by its name
		/** @param recursive specifies if inherited fields should be considered */
		Field* FindField(const char* name, bool recursive = true) const;

		// Searches the method by its name
		/** @param recursive specifies if inherited methods should be considered */
		Method* FindMethod(const char* name, bool recursive = true) const;

		// Searches the accessor by its name
		/** @param recursive specifies if inherited accessors should be considered */
		Accessor* FindAccessor(const char* name, bool recursive = true) const;

	private:

		void sortDescs();

	private:
		ClassDescriptor**	mDescriptors;
		size_t				mDescSize;
		class_desc_base*	mClassDesc;
		size_t				mFirstField; // position of first field (end of base classes)
		size_t				mFirstMethod; // first method (and last field)
		size_t				mFirstAccessor; // first accessor (and last method)
		size_t				mFirstService; // first service descriptor (and last accessor)
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _USERTYPE_H__