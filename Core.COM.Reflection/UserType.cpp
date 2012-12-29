/*========================================================
* UserType.cpp
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#include "TypeTag.h"
#include <string>
#include <cassert>
#include "classdesc.h"
#include "UserType.h"
#include "ParsingDescriptor.h"
#include "ConstructDescriptor.h"
#include "AssignmentDescriptor.h"

#include <algorithm>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////

	UserType::UserType(class_desc_base* desc) : mClassDesc(desc)
	{
		mDescriptors = desc->intialize(mDescSize);
		sortDescs();
	}

	//////////////////////////////////////////////////////////////////////////

	UserType::~UserType()
	{
		for(int i = 0; i != mDescSize; ++i)
		{
			delete mDescriptors[i];
			mDescriptors[i] = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void* UserType::CreateInstance() const
	{
		// Find service
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == RL_DESC_SERVICE_CONSTRUCT)
				return ((ConstructDescriptor*)mDescriptors[i])->CreateInstance();
			
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void UserType::DestroyInstance(void* v) const
	{
		// Find service
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == RL_DESC_SERVICE_CONSTRUCT)
				((ConstructDescriptor*)mDescriptors[i])->DestroyInstance(v);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t UserType::Name(char *buf, size_t size) const 
	{
		int pos = 0;
		for(int i = 0; mClassDesc->name[i] != '\0'; ++i)
			if(mClassDesc->name[i] == ':')
				pos = i + 1;

		strcpy_s(buf, size, &mClassDesc->name[pos]);
		return strlen(buf);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t UserType::FullName(char *buf, size_t size) const 
	{
		strcpy_s(buf, size, mClassDesc->name);
		return strlen(buf);
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::Equal(const Type* other) const
	{
		if(	getArchType() != other->getArchType())
			return false;

		assert(false);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	void UserType::Assign(void *to, void *val) const
	{
		// Find service
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == RL_DESC_SERVICE_ASSIGN)
				((AssignmentDescriptor*)mDescriptors[i])->Assign(to, val);

		memcpy(to, val, Size());
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::ToString(void *value, std::string &out) const
	{
		// Find service
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == RL_DESC_SERVICE_PARSING)
				return ((ParsingDescriptor*)mDescriptors[i])->ToString(value, out);

		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::TryParse(void * value, const char* str) const
	{
		// Find service
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == RL_DESC_SERVICE_PARSING)
				return ((ParsingDescriptor*)mDescriptors[i])->TryParse(value, str);

		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool UserType::SupportsService(DescriptorType type) const
	{
		for(size_t i = mFirstService; i != mDescSize; ++i)
			if(mDescriptors[i]->getDescriptorType() == type)
				return true;

		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	void UserType::sortDescs()
	{
		if(!mDescriptors) return;
		struct cmp_tag
		{
			bool operator()(ClassDescriptor* lhs, ClassDescriptor* rhs)
			{ return lhs->getDescriptorType() < rhs->getDescriptorType(); }
		};
		std::sort(&mDescriptors[0], &mDescriptors[mDescSize], cmp_tag());

		DescriptorType lt = RL_DESC_BASE;
		mFirstField = mFirstMethod = mFirstAccessor = mFirstService = mDescSize;
		for(size_t i = 0; i != mDescSize; ++i)
		{
			if(lt != RL_DESC_FIELD && mDescriptors[i]->getDescriptorType() == RL_DESC_FIELD)
			{
				mFirstField = i;
				lt = RL_DESC_FIELD;
			}
			else if(lt != RL_DESC_METHOD && mDescriptors[i]->getDescriptorType() == RL_DESC_METHOD)
			{
				mFirstMethod = i;
				lt = RL_DESC_METHOD;
			}
			else if(lt != RL_DESC_ACCESSOR && mDescriptors[i]->getDescriptorType() == RL_DESC_ACCESSOR)
			{
				mFirstAccessor = i;
				lt = RL_DESC_ACCESSOR;
			}
			else if(lt < RL_DESC_SERVICE_PARSING && mDescriptors[i]->getDescriptorType() > RL_DESC_ACCESSOR)
			{
				mFirstService = i;
				lt = RL_DESC_SERVICE_PARSING;
			}
		}

		if(mFirstAccessor == mDescSize) mFirstAccessor = mFirstService;
		if(mFirstMethod == mDescSize) mFirstMethod = mFirstAccessor;
		if(mFirstField == mDescSize) mFirstField = mFirstMethod;
	}

	//////////////////////////////////////////////////////////////////////////

	BaseClass* UserType::getBaseClass(size_t index) const
	{
		assert(index < mFirstField && mDescriptors[index]->getDescriptorType() == RL_DESC_BASE);
		return (BaseClass*)mDescriptors[index];
	}

	//////////////////////////////////////////////////////////////////////////

	Field* UserType::getField(size_t index) const
	{
		index += mFirstField;
		assert(index < mFirstMethod && mDescriptors[index]->getDescriptorType() == RL_DESC_FIELD);
		return (Field*)mDescriptors[index];
	}

	//////////////////////////////////////////////////////////////////////////

	Method* UserType::getMethod(size_t index) const
	{
		index += mFirstMethod;
		assert(index < mDescSize && mDescriptors[index]->getDescriptorType() == RL_DESC_METHOD);
		return (Method*)mDescriptors[index];
	}

	//////////////////////////////////////////////////////////////////////////

	Accessor* UserType::getAccessor(size_t index) const
	{
		index += mFirstAccessor;
		assert(index < mDescSize && mDescriptors[index]->getDescriptorType() == RL_DESC_ACCESSOR);
		return (Accessor*)mDescriptors[index];
	}

	//////////////////////////////////////////////////////////////////////////

	BaseClass* UserType::FindBaseClass(const char* name, bool recursive) const
	{
		for(size_t i = 0; i != mFirstField; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_BASE);
				return (BaseClass*)mDescriptors[i];
			}
		}

		if(!recursive) return 0;

		for(size_t i = 0; i != mFirstField; ++i)
		{
			Type* bt = mDescriptors[i]->getType();
			assert(bt->getArchType() == RL_ARCH_USERDEFINED);
			BaseClass* ret = ((UserType*)bt)->FindBaseClass(name, recursive);
			if(ret) return ret;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	Field* UserType::FindField(const char* name, bool recursive) const
	{
		for(size_t i = mFirstField; i != mFirstMethod; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_FIELD);
				return (Field*)mDescriptors[i];
			}
		}

		if(!recursive) return 0;

		for(size_t i = 0; i != mFirstField; ++i)
		{
			Type* bt = mDescriptors[i]->getType();
			assert(bt->getArchType() == RL_ARCH_USERDEFINED);
			Field* ret = ((UserType*)bt)->FindField(name, recursive);
			if(ret) return ret;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	Method* UserType::FindMethod(const char* name, bool recursive) const
	{
		for(size_t i = mFirstMethod; i != mFirstAccessor; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_METHOD);
				return (Method*)mDescriptors[i];
			}
		}

		if(!recursive) return 0;

		for(size_t i = 0; i != mFirstField; ++i)
		{
			Type* bt = mDescriptors[i]->getType();
			assert(bt->getArchType() == RL_ARCH_USERDEFINED);
			Method* ret = ((UserType*)bt)->FindMethod(name, recursive);
			if(ret) return ret;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	Accessor* UserType::FindAccessor(const char* name, bool recursive) const
	{
		for(size_t i = mFirstAccessor; i != mDescSize; ++i)
		{
			if(strcmp(name, mDescriptors[i]->getName()) == 0)
			{
				assert(mDescriptors[i]->getDescriptorType() == RL_DESC_ACCESSOR);
				return (Accessor*)mDescriptors[i];
			}
		}

		if(!recursive) return 0;

		for(size_t i = 0; i != mFirstField; ++i)
		{
			Type* bt = mDescriptors[i]->getType();
			assert(bt->getArchType() == RL_ARCH_USERDEFINED);
			Accessor* ret = ((UserType*)bt)->FindAccessor(name, recursive);
			if(ret) return ret;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace