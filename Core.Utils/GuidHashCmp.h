/*========================================================
* GuidHashCmp.h
* @author Sergey Mikhtonyuk
* @date 19 April 2009
=========================================================*/
#ifndef _GUIDHASHCMP_H__
#define _GUIDHASHCMP_H__

/// GUID hash functor
/** @ingroup Utils */
struct GUIDHash
{
	/**
	* Simple hash for GUIDs
	* @param guid The GUID to be hashed
	* @return The hash value
	*/
	size_t operator() (const Core::SCOM::GUID& guid) const
	{
		unsigned long val;
		val = guid.Data1 * guid.Data2 * guid.Data3;
		return size_t(val);
	}

};

//////////////////////////////////////////////////////////////////////////

/// GUID 'equal' comparator
/** @ingroup Utils */
struct GUIDCmp_Eq : public std::binary_function<Core::SCOM::GUID, Core::SCOM::GUID, bool>
{
	/**
	* Comparing
	* @param v1 The first value
	* @param v2 The second value
	* @return true if the first value equal to second
	*/
	bool operator () (const Core::SCOM::GUID& v1, const Core::SCOM::GUID& v2) const
	{
		return v1 == v2;
	}
};

//////////////////////////////////////////////////////////////////////////

/// GUID 'less' comparator
/** @ingroup Utils */
struct GUIDCmp_Less : public std::binary_function<Core::SCOM::GUID, Core::SCOM::GUID, bool>
{
	/**
	* Comparing
	* @param v1 The first value
	* @param v2 The second value
	* @return true if the first value less than the second
	*/
	bool operator() (const Core::SCOM::GUID& v1, const Core::SCOM::GUID& v2) const
	{
		return v1 < v2;
	}
};

//////////////////////////////////////////////////////////////////////////

namespace std
{
	/// STLPort hash function specialization for GUID
	/** @ingroup Utils */
	template<>
	struct hash<Core::SCOM::GUID>
	{
		size_t operator()(const Core::SCOM::GUID& guid) const 
		{
			GUIDHash gh;
			return gh(guid);
		}
	};
} // namespace

//////////////////////////////////////////////////////////////////////////


#endif // _GUIDHASHCMP_H__