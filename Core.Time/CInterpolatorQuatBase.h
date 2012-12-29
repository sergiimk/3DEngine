/*========================================================
* CInterpolatorQuatBase.h
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#ifndef _CINTERPOLATORQUATBASE_H__
#define _CINTERPOLATORQUATBASE_H__

#include "IInterpolator.h"
#include <vector>

namespace Time
{

	class CInterpolatorQuatBase : public IInterpolatorQuat
	{
	public:

		CInterpolatorQuatBase();

		~CInterpolatorQuatBase();

		ETimeMode getTimeMode() const		{ return mTimeMode; }

		void setTimeMode(ETimeMode m)		{ mTimeMode = m; }

		bool IsReady() const				{ return mKeyframes.size() > 1; }

		void Build()						{ }

		void SetKeyframes(const SKeyframeQuat* frames, size_t n);

		void ClearKeyframes();

		void AddKeyframe(const SKeyframeQuat& pnt);

		size_t getKeyframesNum() const		{ return mKeyframes.size(); }

		const SKeyframeQuat& getKeyframe(size_t index) const { return mKeyframes[index]; }

		void setKeyframe(const SKeyframeQuat& pnt, size_t index) { mKeyframes[index] = pnt; }

	protected:
		size_t findSegment(float t) const;

		void processTime(float& t) const;

	protected:
		typedef std::vector<SKeyframeQuat, VML::AlignedAllocator<SKeyframeQuat> > TKeyframeCont;

		TKeyframeCont mKeyframes;

		ETimeMode mTimeMode;
	};

} // namespace

#endif // _CINTERPOLATORQUATBASE_H__