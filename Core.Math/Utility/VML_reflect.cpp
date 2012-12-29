/*========================================================
* VML_reflect.cpp
* @author Sergey Mikhtonyuk
* @date 07 July 2009
=========================================================*/
#include "VML_reflect.h"

//////////////////////////////////////////////////////////////////////////

typedef float (VML::Vector3::*get)();
typedef void (VML::Vector3::*set)(float);

IMPLEMENT_REFLECTION_CLASS(VML::Vector3)
	MAP_ACCESSOR_R("x", get, getXf, set, setX)
	MAP_ACCESSOR_R("y", get, getYf, set, setY)
	MAP_ACCESSOR_R("z", get, getZf, set, setZ)
	MAP_PARSABLE()
	MAP_CREATABLE2(new_vec3, del_vec3)
END_REFLECTION()

//////////////////////////////////////////////////////////////////////////