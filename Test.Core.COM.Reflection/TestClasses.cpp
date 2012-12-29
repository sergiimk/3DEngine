#include "TestClasses.h"

IMPLEMENT_REFLECTION_CLASS_EMPTY(VML::Vector3)
IMPLEMENT_REFLECTION_ENUM(TestEnum)

IMPLEMENT_REFLECTION_CLASS(TestClass3)
	MAP_FIELD("a", a)
	MAP_BASE(TestClass)
	MAP_BASE(TestClass2)
	MAP_METHOD("getA", getA)
END_REFLECTION()

IMPLEMENT_REFLECTION_CLASS(TestClass4)
	MAP_ACCESSOR("A", getA, setA)
END_REFLECTION()


IMPLEMENT_REFLECTION_CLASS_EMPTY(EventProvider);
IMPLEMENT_REFLECTION_CLASS_EMPTY(EventListener);


int TestClass::a;

std::ostream& operator<<(std::ostream& os, const TestClass3& cc)
{
	os << "TestClass3 a=" << cc.a;
	return os;
}

std::istream& operator>>(std::istream& is, TestClass3& cc)
{
	is.setf(std::ios::failbit);
	return is;
}

std::ostream& operator<<(std::ostream& os, const TestClass4& cc)
{
	//os << "TestClass4 a=" << cc.getA();
	return os;
}

std::istream& operator>>(std::istream& is, TestClass4& cc)
{
	is.setf(std::ios::failbit);
	return is;
}

std::ostream& operator<<(std::ostream& os, const TestEnum& cc)
{
	if(cc == VAL_1) os<<"VAL_1";
	if(cc == VAL_2) os<<"VAL_2";
	return os;
}
std::istream& operator>>(std::istream& os, TestEnum& cc)
{
	std::string s;
	os >> s;
	if(s == "VAL_1") cc = VAL_1;
	else if(s == "VAL_2") cc = VAL_2;
	else os.setstate(std::ios::failbit);
	return os;
}
