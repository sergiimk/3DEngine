/*========================================================
* IInterpolator.h
* @author Sergey Mikhtonyuk
* @date 18 June 2009
=========================================================*/
#ifndef _IINTERPOLATOR_H__
#define _IINTERPOLATOR_H__

#include "../Core.COM/Interfaces.h"
#include "../Core.Math/VML.h"

namespace Time
{
	//////////////////////////////////////////////////////////////////////////

	/// Types of time addressing
	/** @ingroup Time */
	enum ETimeMode
	{
		TIME_CLAMP,		///< clamps the t value in range [0..1]
		TIME_WRAP,		///< wraps the value (example: t = 3.2 -> t = 0.2)
		TIME_MIRROR,	///< reverses the time flow for exceeding values (example: t = 1.2 -> t = 0.8, t = 2.2 -> t = 0.2)
	};

	//////////////////////////////////////////////////////////////////////////

	enum EInterpolatorType
	{
		_IPT_V3_BEGIN,

		IPT_V3_LINEAR,			///< Linear interpolation between the key frames
		IPT_V3_CATMULL_ROM,		///< Fast but not accurate spline interpolation
		IPT_V3_CUBIC_SPLINE,	///< Accurate spline interpolation using precomputed tangents

		_IPT_V3_END,
		_IPT_QUAT_BEGIN,

		IPT_QUAT_LINEAR,		///< Linear interpolation
		IPT_QUAT_SPHERICAL,		///< Slerp
		IPT_QUAT_ADAPTIVE,		///< Lerp on small angles and slerp for large

		_IPT_QUAT_END,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Interpolation object interface
	/** @ingroup Time */
	SCOM_INTERFACE(IInterpolator, "c77e8da5-c4f1-4e9f-9ec7-1a0e8a52cd3d", Core::SCOM::IUnknown)
	{
	public:

		/// Returns the type of interpolator
		virtual EInterpolatorType getType() const = 0;

		/// Gets the current time mode
		virtual ETimeMode getTimeMode() const = 0;

		/// Sets the current time addressing mode
		virtual void setTimeMode(ETimeMode m) = 0;

		/// Checks if interpolator is initialized and can be used
		virtual bool IsReady() const = 0;

		/// Updates internals of interpolator after some changes
		virtual void Build() = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Key frame type for Vector3 interpolator
	/** @ingroup Time */
	struct SKeyframeVec3
	{
		VML::Vector3	data;	// watch for proper alignment
		float			time;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Interpolation object for Vector3 type
	/** @ingroup Time */
	SCOM_INTERFACE(IInterpolatorVec3, "95bc32b8-7508-4738-8cab-6b98b32df6b5", IInterpolator)
	{
	public:

		/// Init key frame data from array of n entries
		virtual void SetKeyframes(const SKeyframeVec3* frames, size_t n) = 0;

		/// Clear all key frame data
		virtual void ClearKeyframes() = 0;

		/// Add new key frame to the end
		virtual void AddKeyframe(const SKeyframeVec3& pnt) = 0;

		/// Returns the number of key frames
		virtual size_t getKeyframesNum() const = 0;

		/// Returns the key frame by its index
		virtual const SKeyframeVec3& getKeyframe(size_t index) const = 0;

		/// Modifies the key frame
		virtual void setKeyframe(const SKeyframeVec3& pnt, size_t index) = 0;

		/// Interpolates the data (check IsReady() first)
		virtual VML::Vector3 Interpolate(float t) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Key frame type for Quat interpolator
	/** @ingroup Time */
	struct SKeyframeQuat
	{
		VML::Quat		data;	// watch for proper alignment
		float			time;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Interpolation object for Quat type
	/** @ingroup Time */
	SCOM_INTERFACE(IInterpolatorQuat, "95bc32b8-7508-4738-8cab-6b98b32df6b5", IInterpolator)
	{
	public:

		/// Init key frame data from array of n entries
		virtual void SetKeyframes(const SKeyframeQuat* frames, size_t n) = 0;

		/// Clear all key frame data
		virtual void ClearKeyframes() = 0;

		/// Add new key frame to the end
		virtual void AddKeyframe(const SKeyframeQuat& pnt) = 0;

		/// Returns the number of key frames
		virtual size_t getKeyframesNum() const = 0;

		/// Returns the key frame by its index
		virtual const SKeyframeQuat& getKeyframe(size_t index) const = 0;

		/// Modifies the key frame
		virtual void setKeyframe(const SKeyframeQuat& pnt, size_t index) = 0;

		/// Interpolates the data (check IsReady() first)
		virtual VML::Quat Interpolate(float t) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _IINTERPOLATOR_H__