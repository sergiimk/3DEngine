#include "main.h"
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
ILayer*		g_layer1;
ILayer*		g_layer2;

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
	g_layer1 = _layer;

	scom_new<CLayer>(&_layer);
	_layer->FinalConstruct(pRenderer);
	g_layer2 = _layer;

	size_t ncommands;
	PathCommand *commands;
	size_t npoints;
	VML::Vector2 *points;

	//////////////////////////////////////////////////////////////////////////
	// Border
	//////////////////////////////////////////////////////////////////////////
	PathCommand cmds0[] = 
	{
		PC_MOVE,
		PC_BEZIER_2, PC_LINE,
		PC_BEZIER_2, PC_LINE,
		PC_BEZIER_2, PC_LINE,
		PC_BEZIER_2, PC_CLOSE,
	};
	ncommands = 9;
	commands = cmds0;

	float w = 120.0f;
	float h = 70.0f;
	float r = 10.0f;
	VML::Vector2 points0[] = 
	{
		VML::Vector2(w - r,	h),
		VML::Vector2(w,		h),		VML::Vector2(w,		h - r),
		VML::Vector2(w,		-h + r),
		VML::Vector2(w,		-h),	VML::Vector2(w - r,	-h),
		VML::Vector2(-w + r,-h),
		VML::Vector2(-w,	-h),	VML::Vector2(-w,	-h + r),
		VML::Vector2(-w,	h - r),
		VML::Vector2(-w,	h),		VML::Vector2(-w + r,	h),
	};
	npoints = 12;
	points = points0;

	IPath* path = g_layer1->AddNewComponent();
	IPathBuffer* buff = path->getPathBuffer();
	buff->setPoints(points, npoints);
	buff->setCommands(commands, ncommands);
	path->setProperty(PP_FILL_STYLE, FS_GRAD_Y);
	path->setProperty(PP_FILL_COLOR1, 0xff000000);
	path->setProperty(PP_FILL_COLOR2, 0xff000000);
	path->setProperty(PP_STROKE_STYLE, SS_NONE);
	path->setProperty(PP_STROKE_COLOR1, 0xff000000);
	path->setProperty(PP_STROKE_COLOR2, 0xff000000);
	path->setStrokeWidth(2.0f);


	//////////////////////////////////////////////////////////////////////////
	// Text
	//////////////////////////////////////////////////////////////////////////
	PathCommand cmds2[] = 
	{
		PC_MOVE, PC_LINE, PC_LINE, PC_LINE, PC_CLOSE,
		PC_MOVE, PC_LINE, PC_LINE, PC_LINE, PC_CLOSE,
		PC_MOVE, PC_LINE, PC_LINE, PC_LINE, PC_CLOSE,
	};
	ncommands = 15;
	commands = cmds2;

	w = 30.0f;
	h = 20.0f;
	r = 5.0f;
	VML::Vector2 points2[] = 
	{
		VML::Vector2(-w, h), VML::Vector2(w, h), VML::Vector2(w, -h), VML::Vector2(-w, -h),
		VML::Vector2(-w + r, h - r), VML::Vector2(w - r, h - r), VML::Vector2(w - r, -h + r), VML::Vector2(-w + r, -h + r),
		VML::Vector2(-w + r*3, h - r*3), VML::Vector2(w - r*3, h - r*3), VML::Vector2(w - r*3, -h + r*3), VML::Vector2(-w + r*3, -h + r*3),
	};
	npoints = 12;
	points = points2;

	path = g_layer2->AddNewComponent();
	buff = path->getPathBuffer();
	buff->setPoints(points, npoints);
	buff->setCommands(commands, ncommands);
	path->setProperty(PP_FILL_STYLE, FS_SOLID);
	path->setProperty(PP_FILL_COLOR1, 0xa06060ff);
	path->setProperty(PP_FILL_COLOR2, 0xa06060ff);
	path->setProperty(PP_STROKE_STYLE, SS_LINE_SOLID);
	path->setProperty(PP_STROKE_COLOR1, 0xf060c0ff);
	path->setProperty(PP_STROKE_COLOR2, 0xffff0000);
	path->setStrokeWidth(2.0f);


	//////////////////////////////////////////////////////////////////////////
	// Border
	//////////////////////////////////////////////////////////////////////////
	PathCommand cmds1[] = 
	{
		PC_MOVE,
		PC_BEZIER_2, PC_LINE,
		PC_BEZIER_2, PC_LINE,
		PC_BEZIER_2, PC_LINE,
		PC_BEZIER_2, PC_CLOSE,

		PC_MOVE,
		PC_LINE, PC_LINE, PC_LINE, PC_CLOSE,
	};
	ncommands = 14;
	commands = cmds1;

	w = 100.0f;
	h = 50.0f;
	r = 10.0f;
	VML::Vector2 points1[] = 
	{
		VML::Vector2(w - r,	h),
		VML::Vector2(w,		h),				VML::Vector2(w,			h - r),
		VML::Vector2(w,		-h + r),
		VML::Vector2(w,		-h),			VML::Vector2(w - r,		-h),
		VML::Vector2(-w + r,	-h),
		VML::Vector2(-w,		-h),		VML::Vector2(-w,		-h + r),
		VML::Vector2(-w,		h - r),
		VML::Vector2(-w,		h),			VML::Vector2(-w + r,	h),

		VML::Vector2(-30.0f, 20.0f), VML::Vector2(30.0f, 20.0f), VML::Vector2(30.0f, -20.0f), VML::Vector2(-30.0f, -20.0f),
	};
	npoints = 16;
	points = points1;

	path = g_layer2->AddNewComponent();
	buff = path->getPathBuffer();
	buff->setPoints(points, npoints);
	buff->setCommands(commands, ncommands);
	path->setProperty(PP_FILL_STYLE, FS_GRAD_Y);
	path->setProperty(PP_FILL_COLOR1, 0x50c8c8c8);
	path->setProperty(PP_FILL_COLOR2, 0xfffafafa);
	path->setProperty(PP_STROKE_STYLE, SS_LINE_SOLID);
	path->setProperty(PP_STROKE_COLOR1, 0xff707070);
	path->setProperty(PP_STROKE_COLOR2, 0xffff0000);
	path->setStrokeWidth(2.0f);

	g_layer1->AddUser();
	g_layer2->AddUser();

	return S_OK;
}



VOID Cleanup()
{
	g_layer1->RemoveUser();
	g_layer1->Release();

	g_layer2->RemoveUser();
	g_layer2->Release();

	pRenderer->Release();
	pFS->Release();

	mod_dx9.Shutdown();
	mod_file_system.Shutdown();
}

VOID GameMain()
{
	/*if(KEYDOWN(VK_F1)) pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if(KEYDOWN(VK_F2)) pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if(KEYDOWN(VK_F5)) pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	if(KEYDOWN(VK_F6)) pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	if(KEYDOWN(VK_F7)) pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	if(KEYDOWN('J'))
	{
	g_joint_style = (VG::PathCommand)((int)g_joint_style + 1);
	if(g_joint_style > VG::LJOINT_ROUND)
	g_joint_style = VG::LJOINT_TOFIRST;
	Sleep(100);
	}

	if(KEYDOWN('S'))
	{
	g_stroke_style = (VG::StrokeStyle)((int)g_stroke_style + 1);
	if(g_stroke_style > VG::SS_LINE_GRAD_Y)
	g_stroke_style = VG::SS_LINE_GRAD_LENGTH;
	Sleep(100);
	}

	if(KEYDOWN('1')) g_ending_style = VG::LEND_BUTT;
	if(KEYDOWN('2')) g_ending_style = VG::LEND_ROUND;
	if(KEYDOWN('3')) g_ending_style = VG::LEND_SQUARE;

	if(KEYDOWN('W')) g_line_widh += 0.001f;
	if(KEYDOWN('Q')) g_line_widh -= 0.001f;
	*/


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
