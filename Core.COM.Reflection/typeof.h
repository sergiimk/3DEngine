/*========================================================
* typeof.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _TYPEOF_H__
#define _TYPEOF_H__

#include "Type.h"
#include "TypeTag.h"
#include "TypeTraits.h"
#include "classdesc.h"
#include "../Core.Utils/EnvironmentDefs.h"
#include <sstream>
#include <cassert>

#include "BuiltInType.h"
#include "ArrayType.h"
#include "PointerType.h"
#include "UserType.h"
#include "FunctionType.h"

#include "Delegate/Delegate.h"

#include "../Core.Utils/IfThenElse.h"
#include "../Core.Utils/TypeTraits.h"


namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	template<class T>
	struct _type_of_builtin_ {
	static Type* get() { 
		static BuiltInType<T> type;
		return &type; }
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	struct _type_of_user_ {
		static Type* get() { 
			static class_desc<T> cd;
			static UserType ut(&cd);
			return &ut; }
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	struct _type_of_ {
		static Type* get() 
		{ 
			return Utils::IfThenElse<	r_is_user_type<T>::value, 
										_type_of_user_<T>, 
										_type_of_builtin_<T>>::value::get();
		}
	};

	//////////////////////////////////////////////////////////////////////////

	template<class PT>
	struct _type_of_pointer_ {
		static Type* get() { static PointerType pt(_type_of_<PT>::get());
			return &pt; }
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	struct _type_of_<T*> {
		static Type* get() { return _type_of_pointer_<T>::get(); }
	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	Type* type_of() { return _type_of_<T>::get(); }

	template<class T>
	Type* type_of(const T&) { return _type_of_<T>::get(); }

	template<class T, int S>
	Type* type_of(T (&)[S]) { static ArrayType at(type_of<T>(), S);
		return &at; }

	template<class T, class C>
	Type* type_of(T C::*) { return type_of<T>(); }

	//////////////////////////////////////////////////////////////////////////
	#include "Generated/invokers.inc"
	#include "Generated/invcreators.inc"
	//////////////////////////////////////////////////////////////////////////
	#define CONST_METH
	#include "Generated/invcreators_method.inc"
	#undef CONST_METH
	#define CONST_METH const
	#include "Generated/invcreators_method.inc"
	#undef CONST_METH

	#include "Generated/makedeleg.inc"
	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _TYPEOF_H__