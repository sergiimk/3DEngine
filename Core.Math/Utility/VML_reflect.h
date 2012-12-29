/*========================================================
* VML_reflect.h
* @author Sergey Mikhtonyuk
* @date 07 July 2009
=========================================================*/
#ifndef _VML_REFLECT_H__
#define _VML_REFLECT_H__

#include "../../Core.COM.Reflection/Reflection.h"
#include "../VML.h"
#include "VML_ios.h"

//////////////////////////////////////////////////////////////////////////

inline void* new_vec3()
{
	VML::AlignedAllocator<VML::Vector3> a;
	void* p = a.allocate(1);
	new(p) VML::Vector3();
	return p;
}

inline void del_vec3(void* v)
{
	VML::Vector3* vv = (VML::Vector3*)v;
	vv->~Vector3();
	VML::AlignedAllocator<VML::Vector3> a;
	a.deallocate(vv, 1);
} 

//////////////////////////////////////////////////////////////////////////

REFLECT_TYPE(VML::Vector3)

//////////////////////////////////////////////////////////////////////////

#endif // _VML_REFLECT_H__