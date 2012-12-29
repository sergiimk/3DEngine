/*========================================================
* TestClasses.h
* @author Sergey Mikhtonyuk
* @date 02 January 2009
=========================================================*/
#ifndef _TEST_CLASSES_H__
#define _TEST_CLASSES_H__

#include "../Core.COM.Reflection/Reflection.h"
#include "../Core.COM/Implementations.h"
#include "../Core.Math/VML.h"
#include "../Core.Math/Utility/VML_ios.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
inline int F1() { return 1; }
inline int F2() { return 2; }
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
REFLECT_TYPE(VML::Vector3)
//////////////////////////////////////////////////////////////////////////

enum TestEnum
{
	VAL_1,
	VAL_2,
};

std::ostream& operator<<(std::ostream& os, const TestEnum& cc);
std::istream& operator>>(std::istream& os, TestEnum& cc);

REFLECT_TYPE(TestEnum)

//////////////////////////////////////////////////////////////////////////

class TestClass
{
public:
	static int a;
	int b;
	TestEnum e;
	double d;

	void F1() { b = 666; }

	virtual int& F3() { return b; }

	static void FS1(int a, double b, float c) { a = 777; }
};

//////////////////////////////////////////////////////////////////////////

class TestClass2
{
public:
	int b;
	VML::Vector3 v;
	
	int getB() const 
	{ 
		return b; 
	}
	void setB(const int& _b) { b = _b; }

	VML::Vector3 getV() const { return v; }
	VML::Vector3& getVref() { return v; }
	const VML::Vector3& getVcref() const { return v; }
	void setV(const VML::Vector3& _v) { v = _v; }
};

//////////////////////////////////////////////////////////////////////////

class TestClass3
{
public:
	int a;
	int getA() const { return a; }
};

std::ostream& operator<<(std::ostream& os, const TestClass3& cc);
std::istream& operator>>(std::istream& os, TestClass3& cc);

REFLECT_TYPE(TestClass3)

//////////////////////////////////////////////////////////////////////////

class TestClass4
{
public:
	int a;
	int& getA() { return a; }
	void setA(int _a) { a = _a; }
};

std::ostream& operator<<(std::ostream& os, const TestClass4& cc);
std::istream& operator>>(std::istream& os, TestClass4& cc);

REFLECT_TYPE(TestClass4)

//////////////////////////////////////////////////////////////////////////

class EventProvider
{
public:
	int a;

	void SetA(int na) { 
		if(a != na) {
			a = na; 
			OnValueChanged.raise(na);
		}
	}

	int GetA() const { return a; }

	Reflection::Event<void (int)> OnValueChanged;
};

REFLECT_TYPE(EventProvider)

//////////////////////////////////////////////////////////////////////////

class EventListener
{
public:
	int a;

	void AChanged(int na)
	{ a = na; }
};

REFLECT_TYPE(EventListener)

//////////////////////////////////////////////////////////////////////////


#endif