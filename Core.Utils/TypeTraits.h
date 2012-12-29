/*========================================================
* TypeTraits.h
* @author Sergey Mikhtonyuk
* @date 05 April 2009
=========================================================*/
#ifndef _TYPETRAITS_H__
#define _TYPETRAITS_H__

namespace Utils
{
	/// Determines if type is pointer
	/** @ingroup Utils */
	template<class T> struct TIsPointer { static const bool value = false; };
	template<class T> struct TIsPointer<T*> { static const bool value = true; };
	template<class T> struct TIsPointer<const T*> { static const bool value = true; };
	template<class T> struct TIsPointer<volatile T*> { static const bool value = true; };

	template<class T> struct TStripType { typedef T plain; typedef T noref; typedef T noptr; typedef T ref2ptr; };
	template<class T> struct TStripType<T&> { typedef T plain; typedef T noref; typedef T& noptr; typedef T* ref2ptr;  };
	template<class T> struct TStripType<T*> { typedef T plain; typedef T* noref; typedef T noptr; typedef T* ref2ptr; };
	template<class T> struct TStripType<const T&> { typedef T plain; typedef T noref; typedef T& noptr; typedef T* ref2ptr; };
	template<class T> struct TStripType<const T*> { typedef T plain; typedef T* noref; typedef T noptr; typedef T* ref2ptr; };
} // namespace

#endif // _TYPETRAITS_H__