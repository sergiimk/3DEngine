/*========================================================
* CInput.h
* @author Eugene Kuznetsov
* @date 24 November 2008
=========================================================*/

#ifndef _CINPUTCONTROLLER_H_
#define _CINPUTCONTROLLER_H_

#include "IInputController.h"
#include "DInput.h"
#include "../Core.COM/Implementations.h"

namespace Engine
{
	namespace Input
	{
		/// Implementation of IInputController interface
		/** @ingroup Input */
		class NOVTABLE CInputController : 
			public Core::SCOM::ComRootObject<>,
			public IInputController
		{
			DECLARE_IMPLEMENTATION2(CInputController, Core::SCOM::ComClassFactorySingleton)
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IInputController)
			END_INTERFACE_MAP()

			//Direct input initialization
			void Initialize(unsigned int keyboardCoopFlags, unsigned int mouseCoopFlags, void* hInstance, void* hWnd);

			// Keyboard and mouse poll
			void Poll();

			// Keyboard methods
			bool IsKeyDownEvent(EKeyCode key);
			bool IsKeyUpEvent(EKeyCode key);
			bool IsKeyPressed(EKeyCode key);

			//Mouse methods
			bool IsMouseButtonDown(int button);
			bool IsMouseButtonUp(int button);
			bool IsMouseButtonPressed(int button);

			float GetMouseDX();
			float GetMouseDY();
			float GetMouseDZ();

			//CTor and DTor
			CInputController();
			virtual ~CInputController();

		private:
			IDirectInput8*       _pDInput;

			IDirectInputDevice8* _pKeyboard;
			char                 _keyboardState[256];
			char                 _keyboardPreviousState[256]; 

			IDirectInputDevice8* _pMouse;
			DIMOUSESTATE2        _mouseState;
			DIMOUSESTATE2		 _mousePreviousState;
		};

	}
}
#endif