/*========================================================
* InterpolatorsQuat.h
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#ifndef _INTERPOLATORSQUAT_H__
#define _INTERPOLATORSQUAT_H__

#include "CInterpolatorQuatBase.h"
#include "../Core.COM/Implementations.h"

namespace Time
{
	//////////////////////////////////////////////////////////////////////////

	/// Implementation of linear interpolator for Quat
	/** @ingroup Time */
	class NOVTABLE QuatLinear : 
		public Core::SCOM::ComRootObject<>,
		public CInterpolatorQuatBase
	{
	public:

		DECLARE_IMPLEMENTATION(QuatLinear)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IInterpolatorQuat)
			INTERFACE_ENTRY(IInterpolator)
		END_INTERFACE_MAP()

		VML::Quat Interpolate(float t) const;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Implementation of spherical interpolator for Quat
	/** @ingroup Time */
	class NOVTABLE QuatSpherical : 
		public Core::SCOM::ComRootObject<>,
		public CInterpolatorQuatBase
	{
	public:

		DECLARE_IMPLEMENTATION(QuatSpherical)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IInterpolatorQuat)
			INTERFACE_ENTRY(IInterpolator)
		END_INTERFACE_MAP()

		VML::Quat Interpolate(float t) const;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Implementation of adaptive interpolator for Quat
	/** @ingroup Time */
	class NOVTABLE QuatAdaptive : 
		public Core::SCOM::ComRootObject<>,
		public CInterpolatorQuatBase
	{
	public:

		DECLARE_IMPLEMENTATION(QuatAdaptive)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IInterpolatorQuat)
			INTERFACE_ENTRY(IInterpolator)
		END_INTERFACE_MAP()

		VML::Quat Interpolate(float t) const;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace


#endif // _INTERPOLATORSQUAT_H__