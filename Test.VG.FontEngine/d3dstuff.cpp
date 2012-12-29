#include "main.h"
#include <crtdbg.h>

#define USE_PERFHUD

ID3DXFont * g_font;

VG::Layer		g_layers[LAYER_NUM];
VG::PathCommand g_joint_style;
VG::PathCommand g_ending_style;
VG::StrokeStyle g_stroke_style;
float g_line_widh;
float g_dist_tolerance;


HRESULT InitD3D(HWND hWnd)
{
	HRESULT hRes = 0;
	if((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = iWidth;
	d3dpp.BackBufferHeight = iHeight;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	if(fullScreen)
	{
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
		d3dpp.Windowed = FALSE;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		RECT wndRect;
		RECT clientRect;
		GetWindowRect(hWnd, &wndRect);
		GetClientRect(hWnd, &clientRect);

		int iWinWidth = iWidth + (wndRect.right - wndRect.left) - (clientRect.right - clientRect.left);
		int iWinHeight = iHeight + (wndRect.bottom - wndRect.top) - (clientRect.bottom - clientRect.top);

		MoveWindow(hWnd, wndRect.left, wndRect.top, iWinWidth, iWinHeight, TRUE);

		D3DDISPLAYMODE d3ddm;
		pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;
	}

	/*=======================================================================
	 =  Get adapter
	 =======================================================================*/
	unsigned int AdapterToUse = D3DADAPTER_DEFAULT;
	D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;

	#ifdef USE_PERFHUD
	// Look for 'NVIDIA PerfHUD' adapter 
	// If it is present, override default settings
	for (unsigned int Adapter = 0; Adapter < pD3D->GetAdapterCount(); ++Adapter)  
	{ 
		D3DADAPTER_IDENTIFIER9	Identifier; 

		if(SUCCEEDED(pD3D->GetAdapterIdentifier(Adapter, 0, &Identifier)) && strstr(Identifier.Description,"PerfHUD") != 0)
		{ 
			AdapterToUse=Adapter; 
			DeviceType=D3DDEVTYPE_REF; // REF is a fake, no worries :)
			break; 
		} 
	} 
	#endif

	/*=======================================================================
	 =  Verifying hardware support for specified formats
	 =======================================================================*/
	if(	FAILED(hRes = pD3D->CheckDeviceType(AdapterToUse, DeviceType, d3dpp.BackBufferFormat, d3dpp.BackBufferFormat, d3dpp.Windowed)) )
		return E_FAIL;

	/*=======================================================================
	 =  Check for requested vertex processing and pure device
	 =======================================================================*/
	D3DCAPS9 caps;
	if(FAILED(pD3D->GetDeviceCaps(AdapterToUse, DeviceType, &caps)))
		return E_FAIL;

	DWORD devBehaviorFlags = 0;
	devBehaviorFlags |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? 
										D3DCREATE_HARDWARE_VERTEXPROCESSING : 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	/*=======================================================================
	 =  If pure device and HW T&L supported
	 =======================================================================*/
	/*if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE && devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		devBehaviorFlags |= D3DCREATE_PUREDEVICE;*/


	/*=======================================================================
	 =  Check multi sample support
	 =======================================================================*/
	d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dpp.MultiSampleQuality = 0;
	if(SUCCEEDED(pD3D->CheckDeviceMultiSampleType(AdapterToUse, DeviceType, d3dpp.BackBufferFormat, d3dpp.Windowed, d3dpp.MultiSampleType, &d3dpp.MultiSampleQuality)))
		if(SUCCEEDED(pD3D->CheckDeviceMultiSampleType(AdapterToUse, DeviceType, d3dpp.AutoDepthStencilFormat, d3dpp.Windowed, d3dpp.MultiSampleType, &d3dpp.MultiSampleQuality)))
			--d3dpp.MultiSampleQuality;
		else
			d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;


	/*=======================================================================
	 =  Create device
	 =======================================================================*/
	if(FAILED(hRes = pD3D->CreateDevice(	AdapterToUse, 
											DeviceType, 
											hWnd,
											devBehaviorFlags,
											&d3dpp, &pD3DDevice)))
		return hRes;


	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

HRESULT InitGeometry()
{
	BuildScene();

	g_dist_tolerance = 1.0f;
	g_line_widh = 0.1f;
	g_joint_style = VG::LJOINT_MITER;
	g_stroke_style = VG::SS_LINE_GRAD_WIDTH;

	D3DXFONT_DESC lf;
	ZeroMemory(&lf, sizeof(D3DXFONT_DESCA));
	lf.Height = 18;
	lf.Width = 6;
	lf.Weight = 500;
	lf.CharSet = DEFAULT_CHARSET;
	wcscpy(lf.FaceName, L"Courier New");
	D3DXCreateFontIndirect(pD3DDevice, &lf, &g_font);

	return S_OK;
}



VOID Cleanup()
{
	if(g_font)
		g_font->Release();
	if(pD3DDevice)
		pD3DDevice->Release();
	if(pD3D)
		pD3D->Release();
}

VOID SetCamera()
{
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &Position, &LookAt, &CameraUp);
	pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, CameraFOV, (float)iWidth / (float)iHeight, 1.0f, 10000.0f);
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
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




VOID GameMain()
{
	if(KEYDOWN(VK_F1)) pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
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


	if(KEYDOWN('A'))
	{
		Position.z += 5.5f;
		SetCamera();
	}
	if(KEYDOWN('Z'))
	{
		Position.z -= 5.5f;
		SetCamera();
	}
	if(KEYDOWN(VK_UP))		CameraRotation.x += 0.01f;
	if(KEYDOWN(VK_DOWN))	CameraRotation.x -= 0.01f;
	if(KEYDOWN(VK_LEFT))	CameraRotation.y += 0.01f;
	if(KEYDOWN(VK_RIGHT))	CameraRotation.y -= 0.01f;

	if(KEYDOWN('9'))	g_dist_tolerance -= 0.05f;
	if(KEYDOWN('0'))	g_dist_tolerance += 0.05f;
	if(KEYDOWN('7'))	g_dist_tolerance -= 0.001f;
	if(KEYDOWN('8'))	g_dist_tolerance += 0.001f;

	g_dist_tolerance = max(0.0000001f, g_dist_tolerance);

	Render();
}



INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"VG Test", NULL };
	RegisterClassEx( &wc );

	HWND hWnd = CreateWindow( L"VG Test", L"VG Test",
		WS_OVERLAPPEDWINDOW, 100, 100, 256, 256,
		NULL, NULL, wc.hInstance, NULL );

	if(FAILED(InitD3D(hWnd))) return 1;

	SetCamera();

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	if(FAILED(InitGeometry())) return 1;

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
