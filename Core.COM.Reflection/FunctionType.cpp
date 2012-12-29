/*========================================================
* FunctionType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#include "../Core.Utils/EnvironmentDefs.h"
#include "TypeTag.h"
#include "Type.h"
#include <string>
#include <sstream>
#include <cassert>
#include "FunctionType.h"

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	FunctionType::FunctionType(GenericInvoker inv, bool isMethod, Type* rt, Type** arguments, int argc) 
		: mInvoker(inv), mIsMethod(isMethod), mReturnType(rt)
	{
		memset(mArguments, 0, sizeof(void*) * (DELEG_MAX_INVOKE_PARAMS + 1));
		memcpy(mArguments, arguments, sizeof(void*) * argc);
	}

	//////////////////////////////////////////////////////////////////////////

	FunctionType::~FunctionType()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	size_t FunctionType::Name(char* buf, size_t size) const 
	{
		// Return type
		size_t p = mReturnType->Name(buf, size);
		size -= p;

		if(size > 2)
		{
			buf[p++] = ' ';
			buf[p] = '\0';
			--size;
		}

		// Prefix
		if(mIsMethod)
		{
			size_t pt =(*mArguments)->Name(&buf[p], size);
			size -= pt;
			p += pt;

			if(size < 4) return p;
			buf[p - 1]=':'; buf[p++]=':'; buf[p++]='*'; buf[p++]='('; buf[p]='\0';
			size -= 3;
		}
		else
		{
			if(size < 1) return p;
			buf[p++]='('; buf[p]='\0';
			--size;
		}

		
		Type** pparg = (Type**)mArguments;
		if(mIsMethod) ++pparg;

		// Arguments
		bool adjust = false;
		while(*pparg) 
		{
			adjust = true;

			// Place type name
			p += (*pparg)->Name(&buf[p], size);
			size -= p;

			if(size < 2) break;

			buf[p++]=','; buf[p++]=' '; buf[p]='\0';
			size += 2;

			++pparg;
		}

		// Postfix
		if(size < 1) return p;
		if(adjust) p -= 2;
		buf[p++]=')'; buf[p]='\0';
		--size;

		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t FunctionType::FullName(char* buf, size_t size) const 
	{
		return Name(buf, size);
	}

	//////////////////////////////////////////////////////////////////////////

	bool FunctionType::ToString(void * value, std::string& out) const
	{
		char buf[300];
		Name(buf, 300);
		out = std::string(buf);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void FunctionType::Invoke(DelegateBase* deleg, void** args, void* result) const
	{
		mInvoker(deleg, args, result);
	}

	//////////////////////////////////////////////////////////////////////////

	bool FunctionType::Equal(const Type* other) const
	{
		if(	getArchType() != other->getArchType())
			return false;

		assert(false);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	int FunctionType::getArgumentNumber() const
	{ 
		int c = 0; 
		Type** pparg = (Type**)mArguments;
		while(*pparg) 
		{
			++c; ++pparg;
		}
		return c;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace