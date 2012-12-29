/*========================================================
* testmain.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
=========================================================*/

#include "TestClasses.h"

#define BOOST_TEST_MODULE Python_script_test
#include <boost/test/unit_test.hpp>

Module py("Core.Script.Python.dll");
ComPtr<IScriptManager> mgr;

void TestSetup()
{
	TestClass::sInstCount = 0;
	TestClass::sDelCount = 0;
	py.CreateInstance(UUID_PPV(IScriptManager, mgr.wrapped()));
	mgr->Init();
}

void TestTearDown()
{
	mgr->Shutdown();
	mgr.Release();
}

BOOST_AUTO_TEST_SUITE( PyTest );

BOOST_AUTO_TEST_CASE( InitShytdownTest )
{
	TestSetup();
	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( PlainPyTest )
{
	TestSetup();

	mgr->RunScript("py_plain");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( ObjectCreateDestroyTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_simple");

	TestTearDown();	

	BOOST_CHECK_EQUAL(TestClass::sInstCount, 2);
	BOOST_CHECK_EQUAL(TestClass::sDelCount, 2);
}

BOOST_AUTO_TEST_CASE( MethodsTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_methods");

	TestTearDown();	

	BOOST_CHECK_EQUAL(TestClass::sInstCount, 2);
	BOOST_CHECK_EQUAL(TestClass::sDelCount, 2);
}


BOOST_AUTO_TEST_CASE( MembersTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_members");

	TestTearDown();	

	BOOST_CHECK_EQUAL(TestClass::sInstCount, 2);
	BOOST_CHECK_EQUAL(TestClass::sDelCount, 2);
}

BOOST_AUTO_TEST_CASE( ArgumentsTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_arguments");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( VectorTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_vector");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( UserTypeArgumentsTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestPlayer>());
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_utargs");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( PointerArgsTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestPlayer>());
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_ptrargs");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( CustomizationTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_customization");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( InheritanceTest )
{
	TestSetup();

	mgr->ExportType("Sekai", (UserType*)type_of<TestInh_Derived>());
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_inheritance");

	TestTearDown();	
}

BOOST_AUTO_TEST_CASE( FuncImportTest )
{
	TestSetup();

	mgr->RunScript("py_funcaccess");

	int a = 13;

	int r;

	ScriptInvArg args[] = { { &a, type_of<int>() } };
	ScriptInvArg ret = { &r, type_of<int>() };

	ComPtr<IScriptFunction> sf;
	mgr->FindFunction("py_funcaccess.run", sf.wrapped());
	sf->Invoke(args, 1, &ret);

	sf.Release();
	TestTearDown();	

	BOOST_CHECK_EQUAL(r, 12);
}

BOOST_AUTO_TEST_CASE( ClassImportTest )
{
	TestSetup();

	mgr->RunScript("py_classaccess");

	ComPtr<IScriptObjectInstance> tc1, tc2;
	mgr->CreateObjectInstance("py_classaccess.TestClass", tc1.wrapped());
	mgr->CreateObjectInstance("py_classaccess.TestClass", tc2.wrapped());

	int d = 10;
	ScriptInvArg args[] = { &d, type_of<int>() };
	int r = -1;
	ScriptInvArg ret = { &r, type_of<int>() };

	tc1->InvokeMethod("getData", 0, 0, &ret);
	BOOST_CHECK_EQUAL(r, 0);

	tc1->InvokeMethod("setData", args, 1, 0);

	tc1->InvokeMethod("getData", 0, 0, &ret);
	BOOST_CHECK_EQUAL(r, 10);
	tc1->GetFieldValue("mData", &ret);
	BOOST_CHECK_EQUAL(r, 10);

	tc2->GetFieldValue("mData", &ret);
	BOOST_CHECK_EQUAL(r, 0);

	tc1.Release();
	tc2.Release();
	TestTearDown();	
}


BOOST_AUTO_TEST_SUITE_END();