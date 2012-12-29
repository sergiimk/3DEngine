/*========================================================
* IBuffer.h
* @author Sergey Mikhtonyuk
* @date 18 July 2009
=========================================================*/
#ifndef _IBUFFER_H__
#define _IBUFFER_H__

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		enum ELockType
		{
			LOCK_NORMAL,
			LOCK_DISCARD,
			LOCK_READONLY,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Interface to graphics data buffer
		/** @ingroup Graphics */
		class IBuffer
		{
		public:

			/// Returns the buffer size
			virtual size_t Size() const = 0;

			/// Resizes the buffer
			/** @param copyData Should buffer move old data to new storage
			 *  @param ppData If buffer was locked returns new pointer to locked data */
			virtual void Resize(size_t newSize, bool copyData = false, void** ppData = 0) = 0;

			/// Locks the buffer for update
			virtual void Lock(void** ppData, ELockType type) = 0;

			/// Unlocks the data
			virtual void Unlock() = 0;
		};

	} // namespace
} // namespace

#endif // _IBUFFER_H__