/*========================================================
* Type.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _TYPE_H__
#define _TYPE_H__

#include "TypeTag.h"
#include <string>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Reflected type of the object
	/** @ingroup Reflection */
	class Type
	{
	public:
		virtual ~Type() { }

		/// Writes type name to the buffer with specified size
		/** @return number of characters written */
		virtual size_t Name(char* buf, size_t size) const = 0;

		/// Writes fully-qualified type name to the buffer with specified size
		/** @return number of characters written */
		virtual size_t FullName(char* buf, size_t size) const = 0;

		/// Tag of the type
		virtual TypeTag Tag() const = 0;

		/// Size of the type object
		virtual size_t Size() const = 0;

		/// Assigns value to variable
		virtual void Assign(void* to, void* val) const = 0;

		/// Converts value of this type to string
		virtual bool ToString(void * value, std::string& out) const = 0;

		/// Tries to reconstruct value from string
		virtual bool TryParse(void * value, const char* str) const = 0;

		/// Returns the arch-type of this type
		virtual ArchType getArchType() const = 0;

		/// Compares types for equality
		virtual bool Equal(const Type* other) const = 0;

		/// Creates instance of user type
		virtual void* CreateInstance() const = 0;

		/// Destroys instance of user type
		virtual void DestroyInstance(void* v) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _TYPE_H__