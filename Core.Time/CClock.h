/*========================================================
* CClock.h
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
#ifndef _CCLOCK_H__
#define _CCLOCK_H__

#include "IClock.h"

namespace Time
{
	/// Common implementation of IClock
	/** @ingroup Time */
	class CClock : public IClock
	{
	public:
		CClock();

		ITimeSource* getTimeSource() const;

		void setTimeSource(ITimeSource* src);

		void Update();

		void Reset();

		double getTimeDelta() const;

		double getScale() const;

		void setScale(double scale);

		/// Used to propagate time value from the top-level clock to it's children
		void AcceptValue(double delta);

		void Attach(IClock* chld);

		void Detach(IClock* chld);

		int getChildClockNum() const;

		IClock* getChildClock(int index) const;

	private:

		__int64			mTicks;
		__int64			mPrevTicks;
		__int64			mFirstTicks;
		double			mDelta;
		double			mScale;

		CClock*			mParent;
		CClock*			mChildren[MAX_CHILD_CLOCKS];

		ITimeSource*	mTimeSource;
	};

} // namespace

#endif	// _CCLOCK_H__