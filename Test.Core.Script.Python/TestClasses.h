/*========================================================
* TestClasses.h
* @author Sergey Mikhtonyuk
* @date 06 July 2009
=========================================================*/
#ifndef _TESTCLASSES_H__
#define _TESTCLASSES_H__

//////////////////////////////////////////////////////////////////////////

#include "../Core.COM/Module.h"
#include "../Core.COM/Intellectual.h"
#include "../Core.Script.Python/Scripting.h"
#include "../Core.COM.Reflection/Reflection.h"
#include <iostream>
#include "../Core.Math/VML.h"
#include "../Core.Math/Utility/VML_reflect.h"

//////////////////////////////////////////////////////////////////////////

using namespace Core;
using namespace SCOM;
using namespace Script;
using namespace Reflection;

//////////////////////////////////////////////////////////////////////////

class TestClass
{
public:
	TestClass()
	{
		methodID = 0;
		data = sInstCount++;
		str = (char*)"some string";
	}

	~TestClass()
	{
		++sDelCount;
	}

	int data;
	bool bval;
	int methodID;
	static int sInstCount;
	static int sDelCount;
	char* str;

	void Method1()
	{
		methodID = 1;
	}

	void Method2()
	{
		methodID = 2;
	}

	virtual double Method3(int a, double b)
	{
		methodID = 3;
		double c = a * b;
		return c;
	}

};

REFLECT_TYPE(TestClass)

//////////////////////////////////////////////////////////////////////////

class TestPlayer
{
public:
	VML::Vector3 mPosition;

	VML::Vector3* mPositionPtr;


	const VML::Vector3& getPosition() const { return mPosition; }

	void setPosition(const VML::Vector3& pos) { mPosition = pos; }

	VML::Vector3* getPositionPtr() const { return mPositionPtr; }

	void setPositionPtr(VML::Vector3* pos) { mPositionPtr = pos; }


	TestPlayer() : mPosition(0), mPositionPtr(&mPosition) { }
};

//////////////////////////////////////////////////////////////////////////

inline void* new_tc()
{
	VML::AlignedAllocator<TestPlayer> a;
	void* p = a.allocate(1);
	new(p) TestPlayer();
	return p;
}

inline void del_tc(void* v)
{
	TestPlayer* vv = (TestPlayer*)v;
	vv->~TestPlayer();
	VML::AlignedAllocator<TestPlayer> a;
	a.deallocate(vv, 1);
} 

REFLECT_TYPE(TestPlayer)

//////////////////////////////////////////////////////////////////////////

struct TestInh_Base
{
	static int flag;

	int getFlag() const { return flag; }

	virtual void VirtFunc(int f) { flag = f; }
};

struct TestInh_Derived : public TestInh_Base
{
	void VirtFunc(int f) { flag = f - 1; }
};

REFLECT_TYPE(TestInh_Base)
REFLECT_TYPE(TestInh_Derived)

//////////////////////////////////////////////////////////////////////////

#endif // _TESTCLASSES_H__