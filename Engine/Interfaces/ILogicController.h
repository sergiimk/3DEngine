/*========================================================
* ILogicController.h
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#ifndef _ILOGICCONTROLLER_H__
#define _ILOGICCONTROLLER_H__

#include "../Engine_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{

	/// Logic controller drives the process of ICmpLogic 'think' notifications
	/** On logic component creation (when think type is not THINK_NEVER) component
	 *  will be registered in this controller and will recieve scheduled think notifications
	 *  @ingroup  */
	SCOM_INTERFACE(ILogicController, "6718d7fe-7a34-4a93-a8b2-b43947044a98", Core::SCOM::IUnknown)
	{
	public:

		/// Adds logic component to notification queue
		virtual void RegisterLogicComponent(ICmpLogic* logic) = 0;

		/// Removes logic component from notification queue
		virtual void UnRegisterLogicComponent(ICmpLogic* logic) = 0;

		/// Perform notifications
		virtual void Notify(double time_delta) = 0;
			
	};

} // namespace

#endif // _ILOGICCONTROLLER_H__