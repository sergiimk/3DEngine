/*========================================================
* PointerType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _POINTERTYPE_H__
#define _POINTERTYPE_H__

#include <string>
#include <sstream>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////
	
	/// Type specification for pointer types
	/** @ingroup Reflection */
	class PointerType : public Type
	{
	public:
		PointerType(Type* pointedType) : mPointed(pointedType)
		{ }

		size_t Name(char* buf, size_t size) const;

		size_t FullName(char* buf, size_t size) const;

		TypeTag Tag() const { return RL_T_POINTER; }

		size_t Size() const { return sizeof(void*); }

		void Assign(void* to, void* val) const 
		{ 
			memcpy(to, val, sizeof(void*));
		}

		bool ToString(void * value, std::string& out) const
		{
			std::ostringstream ss; 
			ss << "0x" << std::hex << reinterpret_cast<size_t>(*(void**)value); 
			out = ss.str();
			return true;
		}

		bool TryParse(void * value, const char* str) const { return false; }

		/// Returns the type it points to
		Type* getPointedType() const { return mPointed; }

		ArchType getArchType() const { return RL_ARCH_POINTER; }

		bool Equal(const Type* other) const;

		void* CreateInstance() const { return new void*; }

		void DestroyInstance(void* v) const { delete ((void**)v); }

	private:

		Type* mPointed;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _POINTERTYPE_H__