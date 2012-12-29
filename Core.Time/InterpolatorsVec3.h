/*========================================================
* InterpolatorsVec3.h
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#ifndef _INTERPOLATORSVEC3_H__
#define _INTERPOLATORSVEC3_H__

#include "CInterpolatorVec3Base.h"
#include "../Core.COM/Implementations.h"

namespace Time
{

	//////////////////////////////////////////////////////////////////////////

	/// Implementation of linear interpolator for Vector3
	/** @ingroup Time */
	class NOVTABLE Vec3Linear : 
		public Core::SCOM::ComRootObject<>,
		public CInterpolatorVec3Base
	{
	public:
		
		DECLARE_IMPLEMENTATION(Vec3Linear)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IInterpolatorVec3)
			INTERFACE_ENTRY(IInterpolator)
		END_INTERFACE_MAP()
	
		VML::Vector3 Interpolate(float t) const;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Implementation of Catmull-Rom spline interpolator for Vector3
	/** @ingroup Time */
	class NOVTABLE Vec3CatmullRom : 
		public Core::SCOM::ComRootObject<>,
		public CInterpolatorVec3Base
	{
	public:

		DECLARE_IMPLEMENTATION(Vec3CatmullRom)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IInterpolatorVec3)
			INTERFACE_ENTRY(IInterpolator)
		END_INTERFACE_MAP()
	
		VML::Vector3 Interpolate(float t) const;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Implementation of cubic spline interpolator for Vector3
	/** @ingroup Time */
	class NOVTABLE Vec3CubicSpline : 
		public Core::SCOM::ComRootObject<>,
		public CInterpolatorVec3Base
	{
	public:

		DECLARE_IMPLEMENTATION(Vec3CubicSpline)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IInterpolatorVec3)
			INTERFACE_ENTRY(IInterpolator)
		END_INTERFACE_MAP()
	
		void SetKeyframes(const SKeyframeVec3* frames, size_t n);

		void ClearKeyframes();

		void AddKeyframe(const SKeyframeVec3& pnt);

		void setKeyframe(const SKeyframeVec3& pnt, size_t index);

		void Build();

		bool IsReady() const;

		VML::Vector3 Interpolate(float t) const;

	private:
		typedef std::vector<VML::Vector3, VML::AlignedAllocator<VML::Vector3> > TTangentCont;
		TTangentCont mTangents;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _INTERPOLATORSVEC3_H__