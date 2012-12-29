/*========================================================
* classdesc.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#ifndef _CLASSDESC_H__
#define _CLASSDESC_H__

namespace Reflection
{
	class ClassDescriptor;

	//////////////////////////////////////////////////////////////////////////
	
	template<class T>
	void* create_instance()
	{ return new T(); }

	template<class T>
	void destroy_instance(void* v)
	{ delete (T*)v; }

	template<class T>
	void assign(void* to, void* val)
	{ *(T*)to = *(T*)val; }

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	struct class_desc_base
	{
		virtual ClassDescriptor** intialize(size_t& ndesc) = 0;
		char*		name;
		TypeTag		tag;
		size_t		size;
	};
	//////////////////////////////////////////////////////////////////////////

	template<class T>
	struct class_desc : public class_desc_base
	{
		ClassDescriptor** intialize(size_t& ndesc) 
		{ name = "Unknown"; tag = RL_T_UNKNOWN; size = sizeof(T); ndesc = 0; return 0; }
	};

	//////////////////////////////////////////////////////////////////////////

	#define REFLECT_TYPE(type)														\
	namespace Reflection															\
	{																				\
		template<>																	\
		struct class_desc<type> : public class_desc_base							\
		{																			\
			friend class UserType;													\
		private:																	\
			ClassDescriptor** intialize(size_t& ndesc);								\
		};																			\
	}

	//////////////////////////////////////////////////////////////////////////

	#define _IMPLEMENT_REFLECTION_EMPTY(type, _tag)									\
	namespace Reflection															\
	{																				\
		ClassDescriptor** class_desc<type>::intialize(size_t& ndesc)				\
		{ name = #type; size = sizeof(type); tag = _tag; ndesc = 0; return 0; }		\
	}

	#define IMPLEMENT_REFLECTION_STRUCT_EMPTY(type) _IMPLEMENT_REFLECTION_EMPTY(type, RL_T_STRUCT)
	#define IMPLEMENT_REFLECTION_CLASS_EMPTY(type) _IMPLEMENT_REFLECTION_EMPTY(type, RL_T_CLASS)

	//////////////////////////////////////////////////////////////////////////

	#define _IMPLEMENT_REFLECTION(type, _tag)										\
	namespace Reflection															\
	{																				\
		ClassDescriptor** class_desc<type>::intialize(size_t& ndesc)				\
		{																			\
			name = #type; size = sizeof(type); tag = _tag;							\
			typedef type _Class; ndesc = 0;											\
			static ClassDescriptor* mems[] = {

	#define IMPLEMENT_REFLECTION_STRUCT(type) _IMPLEMENT_REFLECTION(type, RL_T_STRUCT)
	#define IMPLEMENT_REFLECTION_CLASS(type) _IMPLEMENT_REFLECTION(type, RL_T_CLASS)

	//////////////////////////////////////////////////////////////////////////

	#define END_REFLECTION()														\
			};																		\
			return mems;															\
		}																			\
	}

	//////////////////////////////////////////////////////////////////////////

	#define MAP_FIELD(name, field)														\
		new Field((++ndesc, name), type_of(&_Class::field), type_of<_Class>(), offsetof(_Class, field)),

	#define MAP_METHOD(name, method)													\
		new Method((++ndesc, name), type_of(&_Class::method), type_of<_Class>(), MakeGenericDelegate(&_Class::method)),

	#define MAP_ACCESSOR_R(name, gt, getter, st, setter)								\
		new Accessor((++ndesc, name), type_of<_Class>(), type_of((gt)&_Class::getter), type_of((st)&_Class::setter), MakeGenericDelegate((gt)&_Class::getter), MakeGenericDelegate((st)&_Class::setter)),

	#define MAP_ACCESSOR(name, getter, setter)											\
		new Accessor((++ndesc, name), type_of<_Class>(), type_of(&_Class::getter), type_of(&_Class::setter), MakeGenericDelegate(&_Class::getter), MakeGenericDelegate(&_Class::setter)),

	#define MAP_BASE(type)																\
		new BaseClass((++ndesc, #type), type_of<type>(), type_of<_Class>()),

	#define MAP_PARSABLE()																\
		new ParsingDescriptorImpl<_Class>((++ndesc, type_of<_Class>())),

	#define MAP_CREATABLE2(create, destroy)												\
		new ConstructDescriptor((++ndesc, create), destroy, type_of<_Class>()),

	#define MAP_CREATABLE()																\
		MAP_CREATABLE2(create_instance<_Class>, destroy_instance<_Class>)

	#define MAP_CUSTOM_ASSIGN2(as)														\
		new AssignmentDescriptor((++ndesc, as), type_of<_Class>()),

	#define MAP_CUSTOM_ASSIGN()															\
		MAP_CUSTOM_ASSIGN2(assign<_Class>)

	//////////////////////////////////////////////////////////////////////////

	#define IMPLEMENT_REFLECTION_ENUM(type)											\
		_IMPLEMENT_REFLECTION(type, RL_T_ENUM)										\
			MAP_PARSABLE()															\
			MAP_CREATABLE()															\
		END_REFLECTION()

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _CLASSDESC_H__