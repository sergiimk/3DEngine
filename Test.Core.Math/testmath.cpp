/*========================================================
* testmath.cpp
* @author Sergey Mikhtonyuk
* @date 24 April 2009
=========================================================*/
#include "../Core.Math/VML.h"

#define BOOST_TEST_MODULE Math_lib_test
#include <boost/test/unit_test.hpp>
#include <vector>

using namespace VML;


BOOST_AUTO_TEST_SUITE( MathTest );

BOOST_AUTO_TEST_CASE( TestInit )
{
	Vector3 v1(VMAX);
	Vector4 v2(VMAX);
	Point3	p1(VMIN);
	Quat	q1(v2);
	Matrix3 m1(v1, v1, v1);
	Matrix4 m2(v2, v2, v2, v2);
	Transform3 t1(m1, v1);
}

BOOST_AUTO_TEST_CASE( TestEquivalence )
{
	Vector4 a(1.0f, 10000.1f, 0.001f, 0.0000001f);
	Vector4 b(1.5f, 10000.2f, 0.002f, 0.00000009f);
	//		50-30%	~1%		100-50%		~10%

	Matrix4 m1(a, a, a, a);
	Matrix4 m2(b, b, b, b);

	BOOST_CHECK(equivalent(m1, m2, 0.5f));
	BOOST_CHECK(!equivalent(m1, m2, 0.4f));

	BOOST_CHECK(equivalentRelative(m1, m2, 1.0f));
	BOOST_CHECK(!equivalentRelative(m1, m2, 0.99f));


	Vector3 v1(0,0,0);
	Vector3 v2(0, -1, -1);

	BOOST_CHECK(v1 >= v2);
	BOOST_CHECK(v2 <= v1);
	BOOST_CHECK(!(v1 > v2));
	BOOST_CHECK(!(v1 < v2));
}

BOOST_AUTO_TEST_CASE( TestLengthOps )
{
	Vector3 v1(2.0f, 0, 0);

	v1.clampLength(3.5f);
	BOOST_CHECK_CLOSE_FRACTION((float)v1.length(), 2.0f, 0.01f);

	v1.clampLength(1.5f);
	BOOST_CHECK_CLOSE_FRACTION((float)v1.length(), 1.5f, 0.01f);

	v1.setLength(2.0f);
	BOOST_CHECK_CLOSE_FRACTION((float)v1.length(), 2.0f, 0.01f);

	Vector4 v2(2.0f, 0, 0, 0);

	v2.clampLength(3.5f);
	BOOST_CHECK_CLOSE((float)v2.length(), 2.0f, 0.01f);

	v2.clampLength(1.5f);
	BOOST_CHECK_CLOSE((float)v2.length(), 1.5f, 0.01f);

	v2.setLength(2.0f);
	BOOST_CHECK_CLOSE((float)v2.length(), 2.0f, 0.01f);

	v1 = clampLength(v1, 1.0f);
	BOOST_CHECK_CLOSE((float)v1.length(), 1.0f, 0.01f);

	v1 = setLength(v1, 5.5f);
	BOOST_CHECK_CLOSE((float)v1.length(), 5.5f, 0.01f);

	v1.setX(0.0000001f);
	v1 = setLength(v1, 5.5f);
	BOOST_CHECK_SMALL((float)v1.length(), 0.01f);
}

BOOST_AUTO_TEST_CASE( TestQuat )
{
	Quat rz = Quat::rotationZ(3.1415f / 2.0f);
	Quat rx = Quat::rotationX(3.1415f / 2.0f);
	Quat rzx = rx * rz;
	Vector3 p(1, 0, 0);
	
	p = rotate(rzx, p);
	BOOST_CHECK(equivalent(p, Vector3(0, 0, 1)));

	p = rotate(conj(rzx), p);
	BOOST_CHECK(equivalent(p, Vector3(1, 0, 0)));
}

BOOST_AUTO_TEST_CASE( testTransforms )
{
	Vector4 pos(0, 0, 20.0f, 1.0f);

	Matrix4 proj = Matrix4::perspectiveLH(3.1415f / 2.0f, 1.0f, 10.0f, 30.f);

	pos = proj * pos;
	pos /= pos.getW();

}

BOOST_AUTO_TEST_CASE( testAllocator )
{
	std::vector<Matrix4, VML::AlignedAllocator<Matrix4> > vm;
	vm.push_back(Matrix4::identity());
	Matrix4 m = Matrix4::translation(Vector3(5, 0, 0));
	
	vm.back() = m * vm.back();
	BOOST_CHECK(equivalent(m, vm.back()));
}

BOOST_AUTO_TEST_SUITE_END();