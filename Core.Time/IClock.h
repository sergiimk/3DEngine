/*========================================================
* IClock.h
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
#ifndef _ICLOCK_H__
#define _ICLOCK_H__

#include "Time_fwd.h"

#define MAX_CHILD_CLOCKS 10

namespace Time
{
	/// Clock wrap time sources and provide access to time data
	/** @ingroup Time */
	class IClock
	{
	public:
		/// Gets the current time source
		virtual ITimeSource* getTimeSource() const = 0;

		/// Sets the time source, calls reset implicitly
		virtual void setTimeSource(ITimeSource* src) = 0;

		/// Updates the current time and time that passed since the last call
		virtual void Update() = 0;

		/// Sets the current time as the new starting point for timer
		virtual void Reset() = 0;

		/// Returns the time passed between two last Updates ( (Ticks - PrevTicks) / Resolution )
		virtual double getTimeDelta() const = 0;

		/// Returns current time scale
		virtual double getScale() const = 0;

		/// Sets the time scale
		virtual void setScale(double scale) = 0;

		/// Attaches a child clock
		virtual void Attach(IClock* chld) = 0;

		/// Detaches the child clock
		virtual void Detach(IClock* chld) = 0;

		/// Returns the number of child clocks
		virtual int getChildClockNum() const = 0;

		/// Returns the specified child clock
		virtual IClock* getChildClock(int index) const = 0;
	};

} // namespace

#endif	// _ICLOCK_H__