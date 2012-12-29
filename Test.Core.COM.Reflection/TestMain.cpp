/*============================================================================
	Test.cpp: Test suit for Reflection lib
	
	Author: Sergey Mikhtonyuk, 2008
============================================================================*/

#include "TestClasses.h"

#define BOOST_TEST_MODULE Reflection test
#include <boost/test/unit_test.hpp>

using namespace Core;
using namespace Reflection;


BOOST_AUTO_TEST_SUITE( my_suite1 );


BOOST_AUTO_TEST_CASE( testBuiltInTypes )
{
	char buf[1024];

	int a = 123;
	Type* tint = type_of<int>();
	Type* tint2 = type_of(a);

	std::string s;
	BOOST_CHECK_EQUAL((tint->ToString(&a, s), s), "123");
	BOOST_CHECK(tint->TryParse(&a, "321"));
	BOOST_CHECK_EQUAL(a, 321);

	double b = 3.14;
	Type* td = type_of(b);
	td->Name(buf, 1024);
	BOOST_CHECK(strcmp(buf, "double") == 0);
	BOOST_CHECK_EQUAL((td->ToString(&b, s), s), "3.14");
	BOOST_CHECK(td->TryParse(&b, "2.71"));
	BOOST_CHECK_EQUAL(b, 2.71);

	int arr[10];
	Type* tarr = type_of(arr);
	tarr->Name(buf, 1024);
	BOOST_CHECK(strcmp(buf, "int[10]") == 0);
	BOOST_CHECK_EQUAL(((ArrayType*)tarr)->getElementNumber(), 10);
	BOOST_CHECK_EQUAL(tarr->Size(), 10 * sizeof(int));
}

BOOST_AUTO_TEST_CASE( operatorTest )
{
	int a = 0;
	Type* tint = type_of<int>();
	Type* tint2 = type_of(a);
	Type* tdouble = type_of<double>();

	BOOST_CHECK(tint->Equal(tint2));
	BOOST_CHECK(!tint->Equal(tdouble));
}

BOOST_AUTO_TEST_CASE( enumTest )
{
	char buf[1024];

	Type* te = type_of<TestEnum>();
	TestEnum e = VAL_2;

	te->Name(buf, 1024);
	BOOST_CHECK(strcmp(buf, "TestEnum") == 0);
	BOOST_CHECK(te->Tag() == RL_T_ENUM);

	std::string s;
	BOOST_CHECK_EQUAL((te->ToString(&e, s), s), "VAL_2");
	BOOST_CHECK(te->TryParse(&e, "VAL_1"));
	BOOST_CHECK_EQUAL(e, VAL_1);
}

BOOST_AUTO_TEST_CASE( functionInitTest )
{
	FunctionType* ft1 = (FunctionType*)type_of(&F1);
	FunctionType* ft2 = (FunctionType*)type_of(&F2);

	int r;
	ft1->Invoke(&Delegate<int()>(F1), 0, &r);
	BOOST_CHECK_EQUAL(r, 1);

	ft2->Invoke(&Delegate<int()>(F2), 0, &r);
	BOOST_CHECK_EQUAL(r, 2);
}

BOOST_AUTO_TEST_CASE( methodTest )
{
	Method m("getB", type_of(&TestClass2::getB), type_of<TestClass2>(), MakeGenericDelegate(&TestClass2::getB));
	
	FunctionType* ft = (FunctionType*)m.getType();
	BOOST_CHECK_EQUAL(ft->getArgumentNumber(), 1);


	TestClass2 tc2;
	tc2.b = 114;
	TestClass2* inst = &tc2;
	int b;
	void* args[] = { &inst };
	m.Invoke(args, &b);
	BOOST_CHECK_EQUAL(b, tc2.b);


	char buf[1024];
	ft->Name(buf, 1024);
	BOOST_CHECK(strcmp(buf, "int Unknown::*()") == 0);


	ft = (FunctionType*)type_of(&TestClass::FS1);
	ft->Name(buf, 1024);
	BOOST_CHECK(strcmp(buf, "void (int, double, float)") == 0);
}

BOOST_AUTO_TEST_CASE( classmemberTest )
{
	Field fb("b", type_of<int>(), type_of<TestClass>(), offsetof(TestClass, b));
	TestClass tc;
	tc.b = 123;

	std::string s;
	BOOST_CHECK_EQUAL((fb.ToString(&tc, s), s), "123");

	Method mgetB("getB", type_of(&TestClass2::getB), type_of<TestClass2>(), MakeGenericDelegate(&TestClass2::getB));
	TestClass2 tc2;
	tc2.b = 114;
	TestClass2* inst = &tc2;
	int b;
	void* args[] = { &inst };
	mgetB.Invoke(args, &b);
	BOOST_CHECK_EQUAL(b, 114);	
}

BOOST_AUTO_TEST_CASE( metaclassTest )
{
	char buf[1024];
	UserType* t = (UserType*)type_of<TestClass3>();

	t->Name(buf, 1024);
	BOOST_CHECK(strcmp(buf, "TestClass3") == 0);
	BOOST_CHECK_EQUAL(t->Tag(), RL_T_CLASS);
	BOOST_CHECK_EQUAL(t->Size(), sizeof(TestClass3));

	BOOST_CHECK_EQUAL(t->getBaseClassNumber(), 2);
	BOOST_CHECK_EQUAL(t->getFieldNumber(), 1);
	BOOST_CHECK_EQUAL(t->getMethodNumber(), 1);
	BOOST_CHECK_EQUAL(t->getAccessorNumber(), 0);

	BaseClass* tc = t->FindBaseClass("TestClass");
	BOOST_CHECK_EQUAL(tc->getType(), type_of<TestClass>());

	BaseClass* tc2 = t->FindBaseClass("TestClass2");
	BOOST_CHECK_EQUAL(tc2->getType(), type_of<TestClass2>());

	BOOST_CHECK(t->FindBaseClass("TestClass3") == 0);

	Field* tcf = t->FindField("a");
	BOOST_CHECK_EQUAL(tcf->getType(), type_of<int>());

	Method* tcm = t->FindMethod("getA");
	BOOST_CHECK_EQUAL(tcm->getType(), type_of(&TestClass3::getA));
}

BOOST_AUTO_TEST_CASE( accessorTest )
{
	UserType* t = (UserType*)type_of<TestClass4>();
	Accessor* accA = t->FindAccessor("A");

	TestClass4 tc;
	tc.a = 1234;

	int* pa;
	accA->getValue(&tc, &pa);
	BOOST_CHECK_EQUAL(pa, &tc.a);
	BOOST_CHECK(type_of<int*>()->Equal(accA->getGetterType()->getReturnType()));

	int a = 4321;
	accA->setValue(&tc, &a);
	BOOST_CHECK_EQUAL(a, tc.a);
}

BOOST_AUTO_TEST_CASE( eventTest )
{
	EventProvider provider;
	EventListener listener;

	provider.OnValueChanged.connect(MakeDelegate(&listener, &EventListener::AChanged));
	provider.SetA(10);
	BOOST_CHECK_EQUAL(provider.a, listener.a);

	provider.OnValueChanged.disconnect(MakeDelegate(&listener, &EventListener::AChanged));
	provider.SetA(11);
	BOOST_CHECK_NE(provider.a, listener.a);
}

BOOST_AUTO_TEST_SUITE_END();