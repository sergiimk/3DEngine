/*========================================================
* testmain.cpp
* @author Sergey Mikhtonyuk
* @date 23 July 2009
=========================================================*/
#include "TestClasses.h"
#include "../Core.COM/Intellectual.h"
#include <sstream>

using namespace Core::SCOM;

#define BOOST_TEST_MODULE SCOM_lib_test
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( SCOMTest );

BOOST_AUTO_TEST_CASE( TestGUIDBinding )
{
	const GUID& g = UUIDOF(ITest);
	GUID g2;
	g2.FromString("835ca580-8bc7-40a7-913e-49bbb4987085");

	BOOST_CHECK(g == g2);
}

BOOST_AUTO_TEST_CASE( TestGUIDFromString )
{
	// {a1efa033-613e-4110-90ce-992b81cf751f} 
	GUID g = { 0xa1efa033, 0x613e, 0x4110, { 0x90, 0xce, 0x99, 0x2b, 0x81, 0xcf, 0x75, 0x1f } };

	GUID g2;
	g2.FromString("{a1efa033-613e-4110-90ce-992b81cf751f}");
	BOOST_CHECK(g == g2);

	GUID g3;
	g3.FromString("a1efa033-613e-4110-90ce-992b81cf751f");
	BOOST_CHECK(g == g3);

	std::istringstream ss("{a1efa033-613e-4110-90ce-992b81cf751f}");
	GUID g4;
	BOOST_CHECK(!(!(ss >> g4)));
	BOOST_CHECK(g == g3);
}

BOOST_AUTO_TEST_CASE( TestGUIDToString )
{
	// {a1efa033-613e-4110-90ce-992b81cf751f} 
	GUID g = { 0xa1efa033, 0x613e, 0x4110, { 0x90, 0xce, 0x99, 0x2b, 0x81, 0xcf, 0x75, 0x1f } };
	const char* gs = "A1EFA033-613E-4110-90CE-992B81CF751F";

	char buf[37];
	g.ToString(buf);

	BOOST_CHECK(strcmp(buf, gs) == 0);

	std::ostringstream ss;
	ss << g;
	BOOST_CHECK_EQUAL(ss.str(), gs);
}

BOOST_AUTO_TEST_CASE( TestCreation )
{
	CTest* tc;
	scom_new<CTest>(&tc);
	((ITest*)tc)->Release();

	ITest* tc2;
	scom_new<CTest>(&tc2, UUIDOF(ITest));
	tc2->Release();

	IClassFactory* tc3;
	scom_new<CTest>(&tc3, UUIDOF(IClassFactory));
	BOOST_CHECK(tc3 == 0);
}

BOOST_AUTO_TEST_CASE( TestCasting )
{
	ITest* tc;
	scom_new<CTest>(&tc, UUIDOF(ITest));

	ITest2* tc2;
	interface_cast<ITest2>(tc, &tc2);
	BOOST_CHECK(tc2 != 0);
	tc2->Release();

	IClassFactory* tc3;
	interface_cast<IClassFactory>(tc, &tc3);
	BOOST_CHECK(tc3 == 0);

	tc->Release();
}

BOOST_AUTO_TEST_CASE( TestComPtr )
{
	ComPtr<ITest> tc;
	scom_new<CTest>(tc);
	BOOST_CHECK(tc);

	ComPtr<ITest2> tc2;
	scom_new<CTest, ITest2>(tc2);
	BOOST_CHECK(tc2);

	IClassFactory* t;
	interface_cast<IClassFactory>(tc2, &t);
	BOOST_CHECK(!t);

	ComPtr<IClassFactory> tc3;
	scom_new<CTest>(tc3);
	BOOST_CHECK(!tc3);
}

BOOST_AUTO_TEST_SUITE_END();