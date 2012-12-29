/*========================================================
* ITimeSource.h
* @author Sergey Mikhtonyuk
* @date 28 May 2009
=========================================================*/
#ifndef _ITIMESOURCE_H__
#define _ITIMESOURCE_H__

namespace Time
{
	/// Represents the time source (like the OS system timer, or high res. clock of processor)
	/** @ingroup Time */
	class ITimeSource
	{
	public:
		/// Returns the number of 'ticks' in the current moment
		virtual void GetTicks(__int64& ticks) const = 0;

		/// Returns the number of ticks per second
		virtual void GetResoulution(__int64& res) const = 0;
	};

} // namespace

#endif	// _ITIMESOURCE_H__