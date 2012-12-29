/*========================================================
* NonCopyable.h
* @author Sergey Mikhtonyuk
* @date 15 December 2008
=========================================================*/
#ifndef _NONCOPYABLE_H__
#define _NONCOPYABLE_H__

namespace Utils
{
	/// Base class for non-copyable objects
	/** @ingroup Utils */
	class NonCopyable
	{
	protected:
		///
		NonCopyable() {}
		///
		~NonCopyable() {}

	private:
		///
		NonCopyable(const NonCopyable&);
		///
		const NonCopyable& operator=(const NonCopyable&);
	};	

} // namespace


#endif // _NONCOPYABLE_H__