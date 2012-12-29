/*========================================================
* stringutils.h
* @author Sergey Mikhtonyuk
* @date 30 March 2009
=========================================================*/
#ifndef _STRINGUTILS_H__
#define _STRINGUTILS_H__

#include <functional>
#include <string>
#include <string.h>

//////////////////////////////////////////////////////////////////////////

//! Equality comparer for char*
/** @ingroup Utils */
struct CStrCmp_Eq : public std::binary_function<const char*, const char*, bool>
{
	bool operator () (const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) == 0;
	}
};

//////////////////////////////////////////////////////////////////////////

//! Less comparer for char*
/** @ingroup Utils */
struct CStrCmp_Less : public std::binary_function<const char*, const char*, bool>
{
	bool operator () (const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

//////////////////////////////////////////////////////////////////////////

/// Hashing predicate for case sensitive (normal) strings 
/** @ingroup Utils */
struct CStrHashNorm
{
	size_t operator() (const char* s) const 
		{
		unsigned long h = 0; 
		for ( ; *s; ++s)
		{
			char c = *s;
			h = 5 * h + c;
		}
		return size_t(h);
	}
};

//////////////////////////////////////////////////////////////////////////

//! Equality comparer for std::string
/** @ingroup Utils */
struct StrCmp_Eq : public std::binary_function<std::string, std::string, bool>
{
	bool operator () (const std::string& s1, const std::string& s2) const
	{
		return s1 == s2;
	}
};

//////////////////////////////////////////////////////////////////////////

//! Less comparer for char*
/** @ingroup Utils */
struct StrCmp_Less : public std::binary_function<std::string, std::string, bool>
{
	bool operator() (const std::string& s1, const std::string& s2) const
	{
		return s1 < s2;
	}
};

//////////////////////////////////////////////////////////////////////////

/// Hashing predicate for case sensitive (normal) std strings 
/** @ingroup Utils */
struct StrHashNorm
{
	size_t operator() (const std::string& s) const 
	{
		CStrHashNorm hasher;
		return hasher(s.c_str());
	}
};

//////////////////////////////////////////////////////////////////////////


#endif // _STRINGUTILS_H__