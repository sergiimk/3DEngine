/*========================================================
* InterpolatorsQuat.cpp
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#include "InterpolatorsQuat.h"

namespace Time
{
	//////////////////////////////////////////////////////////////////////////

	VML::Quat QuatLinear::Interpolate(float t) const
	{
		assert(IsReady());

		processTime(t);
		size_t segm = findSegment(t); 

		const SKeyframeQuat& q0 = mKeyframes[segm];
		const SKeyframeQuat& q1 = mKeyframes[segm+1];

		float u = (t - q0.time) / (q1.time - q0.time);
		return VML::lerp(u, q0.data, q1.data);
	}

	//////////////////////////////////////////////////////////////////////////

	VML::Quat QuatSpherical::Interpolate(float t) const
	{
		assert(IsReady());

		processTime(t);
		size_t segm = findSegment(t); 

		const SKeyframeQuat& q0 = mKeyframes[segm];
		const SKeyframeQuat& q1 = mKeyframes[segm+1];

		float u = (t - q0.time) / (q1.time - q0.time);
		return VML::slerp(u, q0.data, q1.data);
	}

	//////////////////////////////////////////////////////////////////////////

	VML::Quat QuatAdaptive::Interpolate(float t) const
	{
		assert(IsReady());

		processTime(t);
		size_t segm = findSegment(t); 

		const SKeyframeQuat& q0 = mKeyframes[segm];
		const SKeyframeQuat& q1 = mKeyframes[segm+1];

		float u = (t - q0.time) / (q1.time - q0.time);

		float ctheta = VML::dot(q0.data, q1.data);

		if(ctheta > 0.8f)	return VML::lerp(u, q0.data, q1.data);
		else				return VML::slerp(u, q0.data, q1.data);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace