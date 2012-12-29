/*========================================================
* CInterpolatorQuatBase.cpp
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#include "CInterpolatorQuatBase.h"
#include <math.h>

namespace Time
{

	//////////////////////////////////////////////////////////////////////////

	CInterpolatorQuatBase::CInterpolatorQuatBase()
		: mTimeMode(TIME_CLAMP)
	{

	}

	//////////////////////////////////////////////////////////////////////////

	CInterpolatorQuatBase::~CInterpolatorQuatBase()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorQuatBase::SetKeyframes(const Time::SKeyframeQuat *frames, size_t n)
	{
		mKeyframes.resize(n);
		memcpy(&mKeyframes[0], frames, sizeof(SKeyframeQuat) * n);
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorQuatBase::ClearKeyframes()
	{
		mKeyframes.clear();
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorQuatBase::AddKeyframe(const Time::SKeyframeQuat &pnt)
	{
		mKeyframes.push_back(pnt);
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CInterpolatorQuatBase::findSegment(float t) const
	{
		// Binary search
		int l = 0, r = (int)mKeyframes.size() - 1, m;

		while(l != r - 1)
		{
			m = (l + r) / 2;
			if( mKeyframes[m].time >= t )
				r = m;
			else
				l = m;
		}

		return l;
	}

	//////////////////////////////////////////////////////////////////////////

	void CInterpolatorQuatBase::processTime(float &t) const
	{
		if(t >= 0.0f && t <= 1.0f) return;

		switch(mTimeMode)
		{
		case TIME_CLAMP:
			t = t > 1.0f ? 1.0f : 0.0f;
			break;

		case TIME_WRAP:
			t = t - floor(t);
			break;

		case TIME_MIRROR:
			{
				float f = floor(t);
				t -= f;
				int i = (int)f % 2;
				t = i ? 1.0f - t : t;
			}
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////

}