/*========================================================
* CClock.cpp
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
#include "CClock.h"
#include "ITimeSource.h"
#include <cassert>
#include "../Core.Utils/EnvironmentDefs.h"
#include <memory.h>

namespace Time
{
	//////////////////////////////////////////////////////////////////////////

	CClock::CClock() : mTicks(0), mPrevTicks(0), mDelta(0), mScale(1.0), mTimeSource(0), mParent(0)
	{
		memset(mChildren, 0, sizeof(void*) * MAX_CHILD_CLOCKS);
	}

	//////////////////////////////////////////////////////////////////////////

	ITimeSource* CClock::getTimeSource() const
	{
		return mTimeSource;
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::setTimeSource(Time::ITimeSource *src)
	{
		// Clock can either be attached to another clock, or
		// directly to time source, but not both
		ASSERT_STRICT(!mParent);
		mTimeSource = src;
		Reset();
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::Update()
	{
		/// Update itself
		if(!mTimeSource) return;

		mPrevTicks = mTicks;
		mTimeSource->GetTicks(mTicks);

		if(mPrevTicks == 0) 
			mPrevTicks = mTicks;

		__int64 res;
		mTimeSource->GetResoulution(res);
		mDelta = ((double)(mTicks - mPrevTicks) / (double)res) * mScale;

		// Update children
		for(int i = 0; i != MAX_CHILD_CLOCKS; ++i)
			if(mChildren[i])
				mChildren[i]->AcceptValue(mDelta);
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::AcceptValue(double delta)
	{
		mDelta = delta * mScale;
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::Reset()
	{
		mTicks = mPrevTicks = mFirstTicks = 0;
		mDelta = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	double CClock::getTimeDelta() const
	{
		return mDelta;
	}

	//////////////////////////////////////////////////////////////////////////

	double CClock::getScale() const
	{
		return mScale;
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::setScale(double scale)
	{
		mScale = scale;
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::Attach(Time::IClock *chld)
	{
		CClock* c = static_cast<CClock*>(chld);
		if(c->mParent) c->mParent->Detach(chld);

		int i;
		for(i = 0; i != MAX_CHILD_CLOCKS; ++i)
			if(!mChildren[i])
				mChildren[i] = c;

		ASSERT_STRICT(i != MAX_CHILD_CLOCKS || mChildren[MAX_CHILD_CLOCKS - 1] == c);

		c->mParent = this;
	}

	//////////////////////////////////////////////////////////////////////////

	void CClock::Detach(IClock* chld)
	{
		CClock* c = static_cast<CClock*>(chld);
		for(int i = 0; i != MAX_CHILD_CLOCKS; ++i)
		{
			if(mChildren[i] == c)
			{
				mChildren[i] = 0;
				c->mParent = 0;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	int CClock::getChildClockNum() const
	{
		int c = 0;
		for (int i = 0; i != MAX_CHILD_CLOCKS; ++i)
			if(mChildren[i]) ++c;
		return c;
	}

	//////////////////////////////////////////////////////////////////////////

	IClock* CClock::getChildClock(int index) const
	{
		int c = 0;
		for (int i = 0; i != MAX_CHILD_CLOCKS; ++i)
		{
			if(mChildren[i])
			{
				if(c == index) return mChildren[i];
				++c;
			}
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace