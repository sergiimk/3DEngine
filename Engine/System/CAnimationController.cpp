/*========================================================
* CAnimationController.cpp
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#include "CAnimationController.h"
#include "../../Core.Time/InterpolatorsVec3.h"
#include "../../Core.Time/InterpolatorsQuat.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	Time::IInterpolator* CAnimationController::CreateInterpolator(Time::EInterpolatorType type)
	{
		Time::IInterpolator* ip = 0;

		switch(type)
		{
		case Time::IPT_V3_LINEAR:
			scom_new<Time::Vec3Linear>(&ip);
			break;
		case Time::IPT_V3_CATMULL_ROM:
			scom_new<Time::Vec3CatmullRom>(&ip);
			break;
		case Time::IPT_V3_CUBIC_SPLINE:
			scom_new<Time::Vec3CubicSpline>(&ip);
			break;
		case Time::IPT_QUAT_LINEAR:
			scom_new<Time::QuatLinear>(&ip);
			break;
		case Time::IPT_QUAT_SPHERICAL:
			scom_new<Time::QuatSpherical>(&ip);
			break;
		case Time::IPT_QUAT_ADAPTIVE:
			scom_new<Time::QuatAdaptive>(&ip);
			break;
		}

		return ip;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace