/*========================================================
* CInterpolatorVec3Base.h
* @author Sergey Mikhtonyuk
* @date 16 July 2009
=========================================================*/
#ifndef _CINTERPOLATORVEC3BASE_H__
#define _CINTERPOLATORVEC3BASE_H__

#include "IInterpolator.h"
#include <vector>

namespace Time
{

	class CInterpolatorVec3Base : public IInterpolatorVec3
	{
	public:

		CInterpolatorVec3Base();

		~CInterpolatorVec3Base();

		ETimeMode getTimeMode() const		{ return mTimeMode; }

		void setTimeMode(ETimeMode m)		{ mTimeMode = m; }

		bool IsReady() const				{ return mKeyframes.size() > 1; }

		void Build()						{ }

		void SetKeyframes(const SKeyframeVec3* frames, size_t n);

		void ClearKeyframes();

		void AddKeyframe(const SKeyframeVec3& pnt);

		size_t getKeyframesNum() const		{ return mKeyframes.size(); }

		const SKeyframeVec3& getKeyframe(size_t index) const { return mKeyframes[index]; }

		void setKeyframe(const SKeyframeVec3& pnt, size_t index) { mKeyframes[index] = pnt; }

	protected:
		size_t findSegment(float t) const;

		void processTime(float& t) const;

	protected:
		typedef std::vector<SKeyframeVec3, VML::AlignedAllocator<SKeyframeVec3> > TKeyframeCont;
		
		TKeyframeCont mKeyframes;

		ETimeMode mTimeMode;
	};

} // namespace

#endif // _INTERPOLATORVEC3BASE_H__