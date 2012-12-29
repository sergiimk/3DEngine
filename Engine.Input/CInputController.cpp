/*========================================================
* CInput.h
* @author Eugene Kuznetsov
* @date 24 November 2008
=========================================================*/

#include "CInputController.h"

namespace Engine
{
	namespace Input
	{
		CInputController::CInputController()
			: _pDInput(0), _pKeyboard(0), _pMouse(0)
		{
			ZeroMemory(_keyboardState, sizeof(_keyboardState));
			ZeroMemory(_keyboardPreviousState, sizeof(_keyboardPreviousState));
			ZeroMemory(&_mouseState, sizeof(_mouseState));
			ZeroMemory(&_mousePreviousState, sizeof(_mousePreviousState));
		}

		void CInputController::Initialize(unsigned int keyboardCoopFlags, unsigned int mouseCoopFlags, void* hInstance, void* hWnd)
		{
			HR(DirectInput8Create((HINSTANCE)hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8A, (void**)&_pDInput, 0));

			HR(_pDInput->CreateDevice(GUID_SysKeyboard, &_pKeyboard, 0));
			HR(_pKeyboard->SetDataFormat(&c_dfDIKeyboard));
			//HR(_pKeyboard->SetCooperativeLevel(hWnd, keyboardCoopFlags));
			HR(_pKeyboard->Acquire());

			HR(_pDInput->CreateDevice(GUID_SysMouse, &_pMouse, 0));
			HR(_pMouse->SetDataFormat(&c_dfDIMouse2));
			//HR(_pMouse->SetCooperativeLevel(hWnd, mouseCoopFlags));
			HR(_pMouse->Acquire());
		}

		CInputController::~CInputController()
		{
			DIRelease(_pDInput);

			if(_pKeyboard)
				_pKeyboard->Unacquire();
			
			if(_pMouse)
				_pMouse->Unacquire();

			DIRelease(_pKeyboard);
			DIRelease(_pMouse);
		}

		void CInputController::Poll()
		{
			//Saving old state of keyboard and mouse
			for (int i =0; i < 256; ++i)
				_keyboardPreviousState[i] = _keyboardState[i];
			_mousePreviousState = _mouseState;

			// Poll keyboard.
			HRESULT hr = _pKeyboard->GetDeviceState(sizeof(_keyboardState), (void**)&_keyboardState); 
			if( FAILED(hr) )
			{
				// Keyboard lost, zero out keyboard data structure.
				ZeroMemory(_keyboardState, sizeof(_keyboardState));

				// Try to acquire for next time we poll.
				hr = _pKeyboard->Acquire();
			}

			// Poll mouse.
			hr = _pMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&_mouseState); 
			if( FAILED(hr) )
			{
				// Mouse lost, zero out mouse data structure.
				ZeroMemory(&_mouseState, sizeof(_mouseState));

				// Try to acquire for next time we poll.
				hr = _pMouse->Acquire(); 
			}
		}

		bool CInputController::IsKeyDownEvent(EKeyCode key)
		{
			return ((_keyboardState[key] & 0x80) != 0 &&(_keyboardPreviousState[key] & 0x80) == 0);
		}

		bool CInputController::IsKeyPressed(EKeyCode key)
		{
			return ((_keyboardState[key] & 0x80) != 0 &&(_keyboardPreviousState[key] & 0x80) != 0);
		}

		bool CInputController::IsKeyUpEvent(EKeyCode key)
		{
			return ((_keyboardState[key] & 0x80) == 0 &&(_keyboardPreviousState[key] & 0x80) != 0);
		}

		bool CInputController::IsMouseButtonDown(int button)
		{
			return ((_mouseState.rgbButtons[button] & 0x80) != 0 && (_mousePreviousState.rgbButtons[button] & 0x80) == 0);
		}

		bool CInputController::IsMouseButtonPressed(int button)
		{
			return ((_mouseState.rgbButtons[button] & 0x80) != 0 && (_mousePreviousState.rgbButtons[button] & 0x80) != 0);
		}

		bool CInputController::IsMouseButtonUp(int button)
		{
			return ((_mouseState.rgbButtons[button] & 0x80) == 0 && (_mousePreviousState.rgbButtons[button] & 0x80) != 0);
		}

		float CInputController::GetMouseDX()
		{
			return (float)_mouseState.lX;
		}

		float CInputController::GetMouseDY()
		{
			return (float)_mouseState.lY;
		}

		float CInputController::GetMouseDZ()
		{
			return (float)_mouseState.lZ;
		}
	}
}