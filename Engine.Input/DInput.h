/*========================================================
* DInput.h
* @author Eugene Kuznetsov
* @date 25 November 2008
=========================================================*/
#ifndef _DINPUT_H__
#define _DINPUT_H__

#include <dinput.h>
#include <windows.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#define DIRelease(x)									\
{														\
	if(x)												\
	{													\
	x->Release();										\
	x = 0;												\
	}													\
}

#define HR(x)																\
{																			\
	HRESULT hr = x;															\
	assert(SUCCEEDED(x));													\
	if(FAILED(hr))															\
	{																		\
		throw("Cannot create DInput");										\
	}																		\
}

#endif // _DINPUT_H__