/*========================================================
* SBoundingVolume.h
* @author Sergey Mikhtonyuk
* @date 05 May 2009
=========================================================*/
#ifndef _SBOUNDINGVOLUME_H__
#define _SBOUNDINGVOLUME_H__

#include "../../Core.Math/VML.h"

namespace Engine
{
	/// Bounding volume combines properties of min-max bounding box and bounding sphere
	/** @ingroup Engine */
	struct SBoundingVolume
	{
		/// Ctor, initializes with default values
		SBoundingVolume();

		/// Ctor, initializes using bounding sphere parameters
		SBoundingVolume(const VML::Vector3& center, float radius);

		/// Ctor, initializes using min max bounding box parameters
		SBoundingVolume(const VML::Vector3& min, const VML::Vector3& max);

		/// Resets bounding volume to invalid value
		void Reset();

		/// Determines if bounding volume has valid value
		bool IsValid() const;

		/// Sets data of bounding box
		void Set(const VML::Vector3& min, const VML::Vector3& max);

		/// Sets data of bounding sphere
		void Set(const VML::Vector3& center, float radius);

		/// Returns radius of bounding sphere
		float getRadius() const { return mRadius; }

		/// Returns center of bounding sphere
		const VML::Vector3& getCenter() const { return mCenter; }

		/// Returns minimum of bounding box
		const VML::Vector3& getMin() const { return mMin; }

		/// Returns maximum of bounding box
		const VML::Vector3& getMax() const { return mMax; }

		/// Start update sequence
		void BeginUpdate() const { }

		/// Includes vertex to the bounding volume (use between BeginUpdate/EndUpdate)
		void Include(const VML::Vector3& v);

		/// Ends update sequence
		void EndUpdate();

	private:

		/// Updates sphere data using box coordinates
		void UpdateSphere();

		/// Updates box using sphere coordinates
		void UpdateBox();

		VML::Vector3	mCenter;
		VML::Vector3	mMin;
		VML::Vector3	mMax;
		float			mRadius;
	};

	//////////////////////////////////////////////////////////////////////////

	inline SBoundingVolume::SBoundingVolume()
		: mCenter(0), mRadius(0), mMin(VML::VMAX), mMax(VML::VMIN)
	{ }

	//////////////////////////////////////////////////////////////////////////

	inline SBoundingVolume::SBoundingVolume(const VML::Vector3& center, float radius)
		: mCenter(center), mRadius(radius)
	{
		UpdateBox();
	}

	//////////////////////////////////////////////////////////////////////////

	inline SBoundingVolume::SBoundingVolume(const VML::Vector3& min, const VML::Vector3& max)
		: mMin(min), mMax(max)
	{
		UpdateSphere();
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::Set(const VML::Vector3& center, float radius)
	{
		mRadius = radius;
		mCenter = center;
		UpdateBox();
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::Set(const VML::Vector3& min, const VML::Vector3& max)
	{
		mMin = min;
		mMax = max;
		UpdateSphere();
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::Reset()
	{
		mCenter = VML::Vector3(0);
		mRadius = 0;
		mMin = VML::Vector3(VML::VMAX);
		mMax = VML::Vector3(VML::VMIN);
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::Include(const VML::Vector3& v)
	{
		mMin = VML::minPerElem(mMin, v);
		mMax = VML::maxPerElem(mMax, v);
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::EndUpdate()
	{
		UpdateSphere();
	}

	//////////////////////////////////////////////////////////////////////////

	inline bool SBoundingVolume::IsValid() const
	{
		return mMin <= mMax;
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::UpdateSphere()
	{
		mCenter = mMax;
		mCenter += mMin;
		mCenter *= 0.5f;

		mRadius = (mMax - mCenter).length();
	}

	//////////////////////////////////////////////////////////////////////////

	inline void SBoundingVolume::UpdateBox()
	{
		VML::Vector3 r(mRadius);
		mMin = mCenter - r;
		mMax = mCenter + r;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif	// _SBOUNDINGVOLUME_H__