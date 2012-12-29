/*========================================================
* TestClasses.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
=========================================================*/
#include "TestClasses.h"

//////////////////////////////////////////////////////////////////////////

int TestClass::sInstCount = 0;
int TestClass::sDelCount = 0;
int TestInh_Base::flag = 0;

IMPLEMENT_REFLECTION_CLASS(TestClass)
	MAP_FIELD("data", data)
	MAP_FIELD("bval", bval)
	MAP_FIELD("str", str)
	MAP_FIELD("methodID", methodID)
	MAP_METHOD("Method1", Method1)
	MAP_METHOD("Method2", Method2)
	MAP_METHOD("Method3", Method3)
	MAP_CREATABLE()
END_REFLECTION()

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_REFLECTION_CLASS(TestPlayer)
	MAP_FIELD("mPosition", mPosition)
	MAP_FIELD("mPositionPtr", mPositionPtr)
	MAP_ACCESSOR("Position", getPosition, setPosition)
	MAP_ACCESSOR("PositionPtr", getPositionPtr, setPositionPtr)
	MAP_METHOD("setPosition", setPosition)
	MAP_METHOD("getPosition", getPosition)
	MAP_METHOD("setPositionPtr", setPositionPtr)
	MAP_METHOD("getPositionPtr", getPositionPtr)
	MAP_CREATABLE2(new_tc, del_tc)
END_REFLECTION()

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_REFLECTION_STRUCT(TestInh_Base)
	MAP_CREATABLE()
	MAP_METHOD("getFlag", getFlag)
	MAP_METHOD("VirtFunc", VirtFunc)
END_REFLECTION()

IMPLEMENT_REFLECTION_STRUCT(TestInh_Derived)
	MAP_BASE(TestInh_Base)
	MAP_CREATABLE()
END_REFLECTION()

//////////////////////////////////////////////////////////////////////////

