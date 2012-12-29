/*========================================================
* DirectX.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef _DIRECTX_EXTERN_H__
#define _DIRECTX_EXTERN_H__

//#define D3D_DEBUG_INFO

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../Core.Utils/EnvironmentDefs.h"

#ifdef _DEBUG
	#define HR(x) if(FAILED(x)) { ASSERT_STRICT(false); }
#else
	#define HR(x) x
#endif

#endif