/*========================================================
* BuiltInType.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _BUILTINTYPE_H__
#define _BUILTINTYPE_H__

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	/// Type implementation for built-in types
	/** @ingroup Reflection */
	template<class T>
	class BuiltInType : public Type
	{
	public:
		size_t Name(char* buf, size_t size) const 
		{ 
			strcpy_s(buf, size, get_type_name(Tag())); 
			return strlen(buf);
		}

		size_t FullName(char* buf, size_t size) const 
		{
			return Name(buf, size);
		}

		TypeTag Tag() const { return r_type_traits<T>::type_tag; }

		size_t Size() const { return sizeof(T); }

		void Assign(void* to, void* val) const 
		{ 
			memcpy(to, val, sizeof(T));
		}

		bool ToString(void * value, std::string& out) const
		{
			std::ostringstream ss; 
			ss << *(T*)value; 
			out = ss.str();
			return true;
		}

		bool TryParse(void * value, const char* str) const
		{
			std::istringstream ss(str); 
			return !(!( ss >> *(T*)value));
		}

		ArchType getArchType() const
		{
			return RL_ARCH_BUILTIN;
		}

		bool Equal(const Type* other) const
		{
			if(	getArchType() != other->getArchType())
				return false;

			return Tag() == other->Tag();
		}

		void* CreateInstance() const { return new T(); }

		void DestroyInstance(void* v) const { delete ((T*)v); }
	};

	//////////////////////////////////////////////////////////////////////////

	template<>
	class BuiltInType<void> : public Type
	{
	public:
		size_t Name(char* buf, size_t size) const 
		{ 
			strcpy_s(buf, size, get_type_name(Tag())); 
			return strlen(buf);
		}
		size_t FullName(char* buf, size_t size) const { return Name(buf, size); }
		TypeTag Tag() const { return RL_T_VOID; }
		size_t Size() const { return 0; }
		void Assign(void* to, void* val) const { }
		bool ToString(void * value, std::string& out) const
		{
			out = std::string("void");
			return true;
		}
		bool TryParse(void * value, const char* str) const { return false; }
		ArchType getArchType() const { return RL_ARCH_BUILTIN; }
		bool Equal(const Type* other) const
		{
			if(	getArchType() != other->getArchType())
				return false;

			return Tag() == other->Tag();
		}
		void* CreateInstance() const { NOT_IMPLEMENTED(); return 0; }
		void DestroyInstance(void* v) const { }
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _BUILTINTYPE_H__