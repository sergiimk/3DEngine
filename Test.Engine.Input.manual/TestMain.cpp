#include "../Engine.Input/Input.h"
#include "../Core.COM/Module.h"
#include "../Core.COM/Intellectual.h"
#include <iostream>
#include <Windows.h>

using namespace Core;
using namespace Engine;
using namespace Input;

SCOM::Module module("Engine.Input.dll");

void main()
{
	SCOM::ComPtr<IInputController> input;
	module.CreateInstance(UUID_PPV(IInputController, input.wrapped()));

	if(!input) std::cout<<"Failed to create input controller"<<std::endl;
	
	char title[500];
	HWND hWnd = GetConsoleWindow();
	GetWindowTextA(hWnd, title, 500);
	HINSTANCE hInst = GetModuleHandleA(title);
	
	std::cout <<"HWND = "<< hWnd <<std::endl;
	std::cout <<"HINSTANCE = "<< hInst <<std::endl;

	input->Initialize(0, 0, hInst, hWnd);
	
	while (true)
	{
		input->Poll();
		if (input->IsKeyDownEvent(KC_SPACE))
			std::cout <<"Space down!"<<std::endl;
		if (input->IsKeyUpEvent(KC_SPACE))
			std::cout <<"Space Up!"<<std::endl;
		if (input->IsKeyPressed(KC_SPACE))
			std::cout <<"Space still pressed!"<<std::endl;

		::Sleep(200);
	}	
}