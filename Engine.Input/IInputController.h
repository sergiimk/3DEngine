/*========================================================
* IInputController.h
* @author Eugene Kuznetsov
* @date 9 December 2008
=========================================================*/
#ifndef _IINPUTCONTROLLER_H_
#define _IINPUTCONTROLLER_H_

#include "../Core.COM/Interfaces.h"
#include "KeyTypes.h"

namespace Engine
{
	namespace Input
	{
		/// Use input controller interface to keep track of input devices' events
		/** @ingroup Input */
		SCOM_INTERFACE(IInputController, "e79689dc-a1f4-4ff9-995d-242961496cf4", Core::SCOM::IUnknown)
		{
		public:
			/// Direct input initialization
			virtual void Initialize(unsigned int keyboardCoopFlags, unsigned int mouseCoopFlags, void* hInstance, void* hWnd) = 0;

			/// Scan the state of keyboard and mouse
			virtual void Poll() = 0;

			/// Key is pressed since last poll
			virtual bool IsKeyDownEvent(EKeyCode key) = 0;
			/// Key is released since last poll
			virtual bool IsKeyUpEvent(EKeyCode key) = 0;
			/// Key is pressed now
			virtual bool IsKeyPressed(EKeyCode key) = 0;

			///
			virtual bool IsMouseButtonDown(int button) = 0;
			///
			virtual bool IsMouseButtonUp(int button) = 0;
			///
			virtual bool IsMouseButtonPressed(int button) = 0;

			///
			virtual float GetMouseDX() = 0;
			///
			virtual float GetMouseDY() = 0;
			///
			virtual float GetMouseDZ() = 0;
		};
	}
}

#endif //_IINPUTCONTROLLER_H_