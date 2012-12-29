/*========================================================
* CApplication.cpp
* @author Sergey Mikhtonyuk
* @date 22 May 2009
=========================================================*/
#include "CApplication.h"
#include "../Engine.Graphics/Graphics.h"

#define NOMINMAX
#include <Windows.h>

#include <NxPhysics.h>

namespace Engine
{
	namespace Common
	{
		using namespace Core;
		using namespace SCOM;
		using namespace Graphics;
		//////////////////////////////////////////////////////////////////////////
		LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		//////////////////////////////////////////////////////////////////////////

		void CApplication::Initialize(Engine::IMainLoop *pMainLoop)
		{
			sInstance = this;

			CreateWnd();
			LogInfo("Starting application plug-in");

			// Init input controller
			gEnv->InputController->Initialize(0, 0, mHinstance, mHwnd);

			// Init renderer
			SRendererParams p; p.MainWindow = mHwnd;
			p.ScreenWidth = mWidth; p.ScreenHeight = mHeight; p.FullScreen = false; p.BackBufferFormat = FMT_X8R8G8B8;
			gEnv->Renderer->Init(p);

			// Set environment
			gEnv->GeometryManager = gEnv->Renderer->GetGeometryManager();
			gEnv->SurfaceManager = gEnv->Renderer->GetSurfaceManager();
			gEnv->MaterialManager = gEnv->Renderer->GetMaterialManager();
			gEnv->EffectManager = gEnv->Renderer->GetEffectManager();
		}

		//////////////////////////////////////////////////////////////////////////
		
		void CApplication::SetupScene()
		{
		}

		//////////////////////////////////////////////////////////////////////////

		int CApplication::OnFrame()
		{
			if(!WinFrame())
				return -1;

			Time::IClock* clock = gEnv->MainLoop->getApplicationClock();

			gEnv->InputController->Poll();

			ProcessInput(clock->getTimeDelta());

			gEnv->LogicController->Notify(clock->getTimeDelta());

			gEnv->PhysicsManager->UpdateKinematicBindings();

			gEnv->PhysXScene->simulate((float)clock->getTimeDelta());
			gEnv->PhysXScene->flushStream();

				gEnv->PhysicsManager->UpdateDynamicBindings();

				gEnv->TransformGraph->Update();

				Render(clock->getTimeDelta());

			gEnv->PhysXScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
			
			Sleep(0);

			return 0;
		}

		//////////////////////////////////////////////////////////////////////////

		void CApplication::ProcessInput(double frameDelta)
		{ }

		//////////////////////////////////////////////////////////////////////////

		void CApplication::Render(double frameDelta)
		{
			gEnv->Renderer->Clear(SRFC_CLEAR_DEPTH | SRFC_CLEAR_COLOR | SRFC_CLEAR_STENCIL, 0xffff0000);
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		CApplication* CApplication::sInstance;

		//////////////////////////////////////////////////////////////////////////

		void CApplication::CreateWnd()
		{
			static TCHAR szAppName[] = TEXT ("Test Engine");
			WNDCLASSEX   wndclassex = { 0 };

			mHinstance = GetModuleHandle(0);

			wndclassex.cbSize        = sizeof(WNDCLASSEX);
			wndclassex.style         = CS_HREDRAW | CS_VREDRAW;
			wndclassex.lpfnWndProc   = WndProc;
			wndclassex.cbClsExtra    = 0;
			wndclassex.cbWndExtra    = 0;
			wndclassex.hInstance     = (HINSTANCE)mHinstance;
			wndclassex.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
			wndclassex.hCursor       = LoadCursor (NULL, IDC_ARROW);
			wndclassex.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
			wndclassex.lpszMenuName  = NULL;
			wndclassex.lpszClassName = szAppName;
			wndclassex.hIconSm       = wndclassex.hIcon;

			if (!RegisterClassEx (&wndclassex))
			{
				MessageBox (NULL, TEXT ("RegisterClassEx failed!"), szAppName, MB_ICONERROR);
				return;
			}

			mHwnd = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW, 
									szAppName, 
									TEXT ("Test GE"),
									WS_OVERLAPPEDWINDOW,
									0, 
									0, 
									100, 
									100, 
									NULL, 
									NULL,
									(HINSTANCE)mHinstance,
									NULL); 

			//////////////////////////////////////////////////////////////////////////
			RECT wndRect;
			RECT clientRect;
			GetWindowRect((HWND)mHwnd, &wndRect);
			GetClientRect((HWND)mHwnd, &clientRect);

			int iWinWidth = mWidth + (wndRect.right - wndRect.left) - (clientRect.right - clientRect.left);
			int iWinHeight = mHeight + (wndRect.bottom - wndRect.top) - (clientRect.bottom - clientRect.top);

			MoveWindow((HWND)mHwnd, wndRect.left, wndRect.top, iWinWidth, iWinHeight, TRUE);

			//////////////////////////////////////////////////////////////////////////

			ShowWindow ((HWND)mHwnd, SW_SHOWNORMAL);
			UpdateWindow ((HWND)mHwnd);
		}

		//////////////////////////////////////////////////////////////////////////

		bool CApplication::WinFrame()
		{
			MSG msg;
			if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if(msg.message == WM_QUIT)
					return false;
			}
			return true;
		}

		//////////////////////////////////////////////////////////////////////////

		LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_CREATE:
				return (0);

			case WM_PAINT:
				ValidateRect((HWND)CApplication::Instance()->getHWnd(), 0);
				return (0);

			case WM_DESTROY:
				PostQuitMessage (0);
				return (0);
			}
			return DefWindowProc (hwnd, message, wParam, lParam);
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace