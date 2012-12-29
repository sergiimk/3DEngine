#include "../Core/SekaiCore.h"
#include "../Core.COM/Interfaces.h"
#include "../Core.COM/Module.h"
#include "../Core.COM/Intellectual.h"

#include <windows.h>
#include <crtdbg.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	//_crtBreakAlloc = 38;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	using namespace Core;
	SCOM::Module module("Core.dll");

	SCOM::ComPtr<ICore> pCore;
	module.CreateInstance(CLSID_CCore, UUID_PPV(ICore, pCore.wrapped()));

	pCore->Initialize("CoreSettings.Test2.xml");
	pCore->StartExecution(__argc, __argv);

	return 0;
}

