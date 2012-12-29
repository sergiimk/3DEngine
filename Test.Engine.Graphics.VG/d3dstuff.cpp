#include "main.h"
#include "RenderSvgImage.h"
#include "../Core.Utils/URL.h"
#include <crtdbg.h>

#define USE_PERFHUD

//VG::Layer		g_layers[LAYER_NUM];
VG::PathCommand g_joint_style;
VG::PathCommand g_ending_style;
VG::StrokeStyle g_stroke_style;
float g_line_widh;
float g_dist_tolerance;

GlobalEnvironment* Core::gEnv;
GlobalEnvironment sgEnv;
Module mod_file_system;
Module mod_dx9;
IFileSystem *pFS;

IRenderer*	pRenderer;
ILayer*		g_layer;

HRESULT Init(HWND hWnd)
{
	mod_file_system.Init("Core.FileSystem.dll");
	mod_dx9.Init("Engine.Graphics.DX9.dll");

	mod_file_system.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, &pFS));
	gEnv = &sgEnv;
	gEnv->Core = 0;
	gEnv->Logger = 0;
	gEnv->PluginManager = 0;
	gEnv->FileSystem = pFS;

	IPlugin *plug;
	mod_dx9.CreateInstance(UUID_PPV(IPlugin, &plug));
	plug->Initialize(gEnv, 0);
	plug->Release();

	mod_dx9.CreateInstance(UUID_PPV(IRenderer, &pRenderer));

	SRendererParams params;
	params.FullScreen = fullScreen;
	params.MainWindow = (WND_HANDLE)hWnd;
	params.ScreenHeight = iHeight;
	params.ScreenWidth = iWidth;
	params.BackBufferFormat = FMT_X8R8G8B8;
	pRenderer->Init(params);
	
	return InitGeometry();
}

HRESULT InitGeometry()
{
	//////////////////////////////////////////////////////////////////////////
	// Create layer
	//////////////////////////////////////////////////////////////////////////

	CLayer* _layer;
	scom_new<CLayer>(&_layer);
	_layer->FinalConstruct(pRenderer);
	g_layer = _layer;

	RenderSvgImage();

	/*IPath* path = g_layer->AddNewComponent();
	IPathBuffer* buf = path->getPathBuffer();

	VML::Vector2 points[] = {
		VML::Vector2(-89.25f, 169.0f),
		VML::Vector2(-67.25f, 173.75f),
	};

	PathCommand commands[] = {
		PC_MOVE,
		PC_LINE,
	};

	buf->setCommands(commands, 2);
	buf->setPoints(points, 2);

	path->setProperty(PP_FILL_STYLE, FS_SOLID);
	path->setProperty(PP_FILL_COLOR1, 0xff00ff00);
	path->setProperty(PP_STROKE_STYLE, SS_LINE_SOLID);
	path->setProperty(PP_DEFAULT_JOINT, LJOINT_MITER);
	path->setProperty(PP_STROKE_COLOR1, 0xffff0000);
	path->setStrokeWidth(4.0f);*/

	g_layer->AddUser();

	return S_OK;
}



VOID Cleanup()
{
	g_layer->RemoveUser();
	g_layer->Release();

	pRenderer->Release();
	pFS->Release();

	mod_dx9.Shutdown();
	mod_file_system.Shutdown();
}

VOID GameMain()
{
	if(KEYDOWN('A'))
	{
		VML::Vector3 dir(g_cameraPos);
		dir.normalize();
		dir *= 10.0f;
		g_cameraPos = g_cameraPos - dir;
	}
	if(KEYDOWN('Z'))
	{
		VML::Vector3 dir(g_cameraPos);
		dir.normalize();
		dir *= 10.0f;
		g_cameraPos = g_cameraPos + dir;
	}
	if(KEYDOWN(VK_UP))		g_cameraPos = VML::rotate(VML::Quat::rotationX(0.01f), g_cameraPos);
	if(KEYDOWN(VK_DOWN))	g_cameraPos = VML::rotate(VML::Quat::rotationX(-0.01f), g_cameraPos);
	if(KEYDOWN(VK_LEFT))	g_cameraPos = VML::rotate(VML::Quat::rotationY(0.01f), g_cameraPos);
	if(KEYDOWN(VK_RIGHT))	g_cameraPos = VML::rotate(VML::Quat::rotationY(-0.01f), g_cameraPos);

	Render();
}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}


INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 446;

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"VG Test", NULL };
	RegisterClassEx( &wc );

	HWND hWnd = CreateWindow( L"VG Test", L"VG Test",
		WS_OVERLAPPEDWINDOW, 100, 100, 256, 256,
		NULL, NULL, wc.hInstance, NULL );

	//////////////////////////////////////////////////////////////////////////
	RECT wndRect;
	RECT clientRect;
	GetWindowRect((HWND)hWnd, &wndRect);
	GetClientRect((HWND)hWnd, &clientRect);

	int iWinWidth = iWidth + (wndRect.right - wndRect.left) - (clientRect.right - clientRect.left);
	int iWinHeight = iHeight + (wndRect.bottom - wndRect.top) - (clientRect.bottom - clientRect.top);

	MoveWindow((HWND)hWnd, wndRect.left, wndRect.top, iWinWidth, iWinHeight, TRUE);

	////////////////////////////////////////////////////////////////////////// 

	if(FAILED(Init(hWnd))) return 1;

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
			GameMain();
	}

	UnregisterClass( L"VG Test", wc.hInstance );
	return 0;
}
