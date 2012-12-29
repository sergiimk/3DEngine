#include "main.h"



LPDIRECT3D9             pD3D		= NULL;
LPDIRECT3DDEVICE9       pD3DDevice	= NULL;

////Camera////
D3DXMATRIX	ObjectAllign;
D3DXVECTOR3 Position(0.0f, 0.0f, -50.0f);
D3DXVECTOR3 LookAt(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CameraUp(0.0f, 1.0f, 0.0f);
D3DXVECTOR3	CameraRotation(0.0f, 0.0f, 0.0f);
FLOAT		CameraFOV = D3DX_PI/4;

float GetTolerance(float dist)
{
	/*static VG::PathPoint stops[10] = 
	{
		{ 0.0f,		0.01f },
		{ 100.0f,	0.05f },
		{ 300.0f,	1.0f },
		{ 500.0f,	3.0f },
		{ 800.0f,	8.0f },
		{ 1000.0f,	14.0f },
		{ 1500.0f,	25.0f },
		{ 2000.0f,	100.0f },
		{ 3000.0f,	200.0f },
		{ 4000.0f,	400.0f },
	};

	if(dist <= stops[0].x) return stops[0].y;
	if(dist >= stops[9].x) return stops[9].y;

	for(int i = 1; i != 10; ++i)
	{
		if(dist < stops[i].x)
			return stops[i-1].y + ((dist - stops[i-1].x) / (stops[i].x - stops[i-1].x)) * (stops[i].y - stops[i-1].y);
	}

	throw 1;*/
	return 0.0001f;
}

VOID Render()
{
	static __int64 _lastFrameTime, currTime, cps;
	static float _deltaT;

	static D3DXMATRIX t;
	D3DXMatrixTranslation(&ObjectAllign, 0.0f, 0.0f, 0);
	D3DXMatrixRotationYawPitchRoll(&t, 0, 0, D3DX_PI);
	D3DXMatrixMultiply(&ObjectAllign, &ObjectAllign, &t);


	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
					  D3DCOLOR_XRGB(100,100,255), 1.0f, 0x0);


	if( SUCCEEDED( pD3DDevice->BeginScene() ) ) ///////////////////////////////////////////////////
	{
		pD3DDevice->SetVertexShader(NULL);

		// Set properties
		g_dist_tolerance = GetTolerance(fabs(Position.z));
		for(int l = 0; l < LAYER_NUM; ++l)
		{
			for(size_t i = 0; i < g_layers[l].Components().size(); ++i)
			{
				g_layers[l].Components()[i]->SetProperty(VG::PP_DEFAULT_JOINT, g_joint_style);
				g_layers[l].Components()[i]->SetProperty(VG::PP_DEFAULT_ENDING, g_ending_style);
				g_layers[l].Components()[i]->DistanceTolerance() = g_dist_tolerance;
			}
		}


		// Calculate paths
		size_t triangles = 0;
		for(int l = 0; l < LAYER_NUM; ++l)
		{
			g_layers[l].Recalculate();
			triangles += g_layers[l].TriangleCount();
		}

		// Draw layers
		D3DXMATRIX m;
		D3DXMatrixRotationYawPitchRoll(&m, CameraRotation.y, CameraRotation.x, CameraRotation.z);
		D3DXMatrixMultiply(&m, &ObjectAllign, &m);
		pD3DDevice->SetTransform(D3DTS_WORLD, &m);

		for(int l = 0; l < LAYER_NUM; ++l)
		{
			g_layers[l].Draw(pD3DDevice);
		}


		// FPS
		wchar_t buf[1000];
		RECT rect = {0, 0, iWidth, iHeight};
		swprintf(buf, 1000, L"FPS: %d \nSec: %f \nTriangles: %d \nDistance: %f \nTolerance: %f", 
			int(1.0f / _deltaT), 
			_deltaT, 
			triangles,
			fabs(Position.z),
			g_dist_tolerance);
		g_font->DrawText(NULL, buf, -1, &rect, DT_TOP | DT_LEFT, 0xff80ff80);
		
		pD3DDevice->EndScene();//////////////////////////////////////////////////////////
	}

	pD3DDevice->Present(NULL, NULL, NULL, NULL);

	BOOL ok = QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	assert(ok);
	ok = QueryPerformanceFrequency((LARGE_INTEGER*)&cps);
	assert(ok);

	_deltaT = float(currTime - _lastFrameTime) / cps;
	_lastFrameTime = currTime;
}

