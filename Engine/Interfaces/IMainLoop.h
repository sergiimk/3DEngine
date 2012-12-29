/*========================================================
* IMainLoop.h
* @author Sergey Mikhtonyuk
* @date 12 December 2008
=========================================================*/
#ifndef _IMAINLOOP_H__
#define _IMAINLOOP_H__

#include "../../Core.Time/Time_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	/// Interface of main loop of the engine
	/** @ingroup Engine 
	  * MainLoop object is the hart of the engine, it is used to cycle the execution, so that
	  * game will not end after one frame. During one frame MainLoop polls systems that execute:
	  * - Updates of objects' states, physics, animation
	  * - Frame rendering
	  * - Dispatching of events of asynchronous file system operations
	  * - Polls the input controllers 
	  * - Dispatches the networking messages */
	SCOM_INTERFACE(IMainLoop, "db424d4f-de02-499c-bcf5-3fd661c0719c", Core::SCOM::IUnknown)
	{
	public:

		/// Start main loop
		virtual void Start() = 0;

		// Reterns the frame number
		virtual __int64 getFrameNumber() const = 0;

		// Returns the main application clock bound to system time source
		virtual Time::IClock* getApplicationClock() const = 0;
	};



} // namespace

#endif // _IMAINLOOP_H__