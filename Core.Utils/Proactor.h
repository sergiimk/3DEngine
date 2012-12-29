/*========================================================
* CProactor.h
* @author Sergey Mikhtonyuk
* @date 14 December 2008
=========================================================*/
/** @defgroup Utils Utils
 *  Utility classes
 *  @ingroup Core */
#ifndef _CPROACTOR_H__
#define _CPROACTOR_H__

#include "NonCopyable.h"
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/date_time.hpp>
#include <algorithm>
#include <deque>

namespace Utils
{

	/// Implements parallel programming Proactor pattern, template parameter determines the number of threads
	/** @ingroup Utils 
	 *  Proactor pattern provides the task queue which is used
	 *  to invoke time consuming methods in background thread, after task completion,
	 *  you will be notified about it by provided callback. To invoke callbacks in main thread
	 *  call DispatchMessages() from main thread's loop */
	template<size_t ThreadNum>
	class Proactor : NonCopyable
	{
	protected:
		/// State of the task in the proactor
		enum TaskState { TS_NEW = 0, TS_PROCESSING, TS_DONE };

		typedef boost::function<void ()> TCallback;

		/// Structure representing the task
		struct Task
		{
			TCallback	Operation;
			TCallback	Handler;
			TaskState	State;
		};

		/// Container type
		typedef std::deque<Task*> TContainer;

	public:
		Proactor() { }
		virtual ~Proactor() { }

		/// Schedule the async operation with it's completion handler. 
		void ScheduleOperation(const TCallback& operation, const TCallback& handler);

		/// Blocks current thread until all tasks will finish
		void WaitAllTasks();

		/// Executes the calls to handlers, called from main thread
		void DispatchMessages();

		/// Returns true if no unprocessed task found
		bool AllTasksCompleted();

	protected:
		/// Main worker threads' function
		void ThreadFunction();

		/// Searches for available task
		Task* GetTaskToProcess();

		/// Predicate for task removal
		static bool TaskDone(Task *pTask);

	protected:
		typedef boost::mutex			TMutex;
		TContainer						mTasks;
		boost::thread					mThreads[ThreadNum];

		TMutex							mMutex;
		boost::condition_variable		mENewTask;
		boost::condition_variable		mETaskCompl;
	};


	/*=======================================================================
	=  Implementation
	=======================================================================*/
	template<size_t ThreadNum>
	void Proactor<ThreadNum>::ScheduleOperation(const TCallback &operation, const TCallback &handler)
	{ // THREAD: main, OPS: lock-write, events

		{ // Locking and updating queue (write-lock)
			boost::lock_guard<TMutex> l(mMutex);

			Task* un = new Task();
			un->Operation = operation; un->Handler = handler; un->State = TS_NEW;
			mTasks.push_front(un);
		}

		// Launching the waiting thread
		mENewTask.notify_one();

		if(!mThreads[0].joinable())
			for(size_t i = 0; i < ThreadNum; ++i)
				mThreads[i] = boost::thread(boost::bind(&Proactor<ThreadNum>::ThreadFunction, this));
	}


	//////////////////////////////////////////////////////////////////////////


	template<size_t ThreadNum>
	void Proactor<ThreadNum>::WaitAllTasks()
	{ // THREAD: main, OPS: read-lock, wait event
		boost::lock_guard<TMutex> lock(mMutex);

		while(!AllTasksCompleted())
		{
			mETaskCompl.wait(lock);
		}
	}


	//////////////////////////////////////////////////////////////////////////


	template<size_t ThreadNum>
	bool Proactor<ThreadNum>::TaskDone(Task *pTask)
	{
		if(pTask->State == TS_DONE)
		{
			pTask->Handler();
			delete pTask;
			return true;
		}
		return false;
	}


	//////////////////////////////////////////////////////////////////////////


	template<size_t ThreadNum>
	void Proactor<ThreadNum>::DispatchMessages()
	{ // THREAD: main, OPS: write-lock
		boost::lock_guard<TMutex> l(mMutex);

		// Separate done
		TContainer::iterator done;
		done = std::remove_if(mTasks.begin(), mTasks.end(), TaskDone);

		// Remove done
		if(done != mTasks.end())
			mTasks.erase(done, mTasks.end());
	}



	/*=======================================================================
	=  Thread routine
	=======================================================================*/
	template<size_t ThreadNum>
	void Proactor<ThreadNum>::ThreadFunction()
	{ // THREAD: background, OPS: read-lock
		Task* myWork = 0;
		for(;;)
		{
			// Check for tasks
			{ 
				boost::unique_lock<TMutex> l(mMutex);

				while(mTasks.size() == 0 || !(myWork = GetTaskToProcess()))
				{
					mENewTask.wait(l);
				}

				myWork->State = TS_PROCESSING;
			}

			// Perform operation
			myWork->Operation();

			// Marking completed task
			myWork->State = TS_DONE;

			// Notify about task completion
			mETaskCompl.notify_all();
		}
	}


	/*=======================================================================
	=  Service
	=======================================================================*/
	template<size_t ThreadNum>
	typename Proactor<ThreadNum>::Task* Proactor<ThreadNum>::GetTaskToProcess()
	{ // THREAD: background, OPS: read
		for(TContainer::reverse_iterator it = mTasks.rbegin(); it != mTasks.rend(); ++it)
			if((*it)->State == TS_NEW) return *it;
		return 0;
	}


	//////////////////////////////////////////////////////////////////////////


	template<size_t ThreadNum>
	bool Proactor<ThreadNum>::AllTasksCompleted()
	{ // THREAD: background, OPS: read
		for(TContainer::reverse_iterator it = mTasks.rbegin(); it != mTasks.rend(); ++it)
			if((*it)->State != TS_DONE) return false;
		return true;
	}

} // namespace

#endif // _CPROACTOR_H__