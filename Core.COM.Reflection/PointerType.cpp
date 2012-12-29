/*========================================================
* PointerType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#include "TypeTag.h"
#include "Type.h"
#include <string>
#include <sstream>
#include <cassert>
#include "PointerType.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	size_t PointerType::Name( char* buf, size_t size ) const
	{
		size_t p = mPointed->Name(buf, size);
		buf[p++] = '*';
		buf[p] = '\0';
		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t PointerType::FullName( char* buf, size_t size ) const
	{
		return Name(buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool PointerType::Equal( const Type* other ) const
	{
		if(	getArchType() != other->getArchType())
			return false;

		return getPointedType()->Equal(((PointerType*)other)->getPointedType());
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace