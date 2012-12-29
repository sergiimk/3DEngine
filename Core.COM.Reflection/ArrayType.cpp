/*========================================================
* ArrayType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#include "../Core.Utils/EnvironmentDefs.h"
#include "TypeTag.h"
#include "Type.h"
#include <string>
#include <sstream>
#include <cassert>
#include "ArrayType.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	ArrayType::ArrayType(Type* elemType, int elems)
		: mElem(elemType), mElemCount(elems)
	{ }

	//////////////////////////////////////////////////////////////////////////

	size_t ArrayType::Name(char *buf, size_t size) const 
	{
		size_t p = mElem->Name(buf, size);
		if(p >= size - 1) return p;
		buf[p++] = '[';
		p += sprintf_s(&buf[p], size - p, "%d", mElemCount);
		if(p >= size - 1) return p;
		buf[p++] = ']';
		buf[p] = '\0';
		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t ArrayType::FullName(char *buf, size_t size) const 
	{
		return Name(buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool ArrayType::ToString(void * value, std::string& out) const
	{
		char buf[100];
		Name(buf, 100);
		out = std::string(buf);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool ArrayType::Equal(const Type* other) const
	{
		if(	getArchType() != other->getArchType())
			return false;

		return Tag() == other->Tag();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace