/*========================================================
* typetraits.h
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#ifndef _RTYPETRAITS_H__
#define _RTYPETRAITS_H__

#include "TypeTag.h"

namespace Reflection
{

	const char* get_type_name(TypeTag tag);

	//////////////////////////////////////////////////////////////////////////
	template<class T> struct r_type_traits 
	{ 
		static const TypeTag type_tag = RL_T_UNKNOWN;
	};

	//////////////////////////////////////////////////////////////////////////

	template<> struct r_type_traits<void> { static const TypeTag type_tag = RL_T_VOID; };

	template<> struct r_type_traits<char> { static const TypeTag type_tag = RL_T_CHAR; };
	template<> struct r_type_traits<unsigned char> { static const TypeTag type_tag = RL_T_UCHAR; };

	template<> struct r_type_traits<short> { static const TypeTag type_tag = RL_T_SHORT; };
	template<> struct r_type_traits<unsigned short> { static const TypeTag type_tag = RL_T_USHORT; };

	template<> struct r_type_traits<int> { static const TypeTag type_tag = RL_T_INT; };
	template<> struct r_type_traits<unsigned int> { static const TypeTag type_tag = RL_T_UINT; };

	template<> struct r_type_traits<long> { static const TypeTag type_tag = RL_T_LONG; };
	template<> struct r_type_traits<unsigned long> { static const TypeTag type_tag = RL_T_ULONG; };

	template<> struct r_type_traits<long long> { static const TypeTag type_tag = RL_T_LONGLONG; };
	template<> struct r_type_traits<unsigned long long> { static const TypeTag type_tag = RL_T_ULONGLONG; };

	template<> struct r_type_traits<bool> { static const TypeTag type_tag = RL_T_BOOL; };
	template<> struct r_type_traits<float> { static const TypeTag type_tag = RL_T_FLOAT; };
	template<> struct r_type_traits<double> { static const TypeTag type_tag = RL_T_DOUBLE; };

	//////////////////////////////////////////////////////////////////////////

	template<class T> struct r_is_user_type { enum { value = r_type_traits<T>::type_tag == RL_T_UNKNOWN }; };
	template<class T> struct r_is_user_type<T*> { enum { value = 0 }; };

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _RTYPETRAITS_H__