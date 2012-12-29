#ifndef _MAIN_H__
#define _MAIN_H__

#include <Windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../Engine.Graphics.VG/VGLib.h"
#include <vector>

/*=======================================================================
 =  Globals
 =======================================================================*/
extern LPDIRECT3D9          pD3D;
extern LPDIRECT3DDEVICE9    pD3DDevice;
extern ID3DXFont*			g_font;

extern D3DXVECTOR3 Position;
extern D3DXVECTOR3 LookAt;
extern D3DXVECTOR3 CameraUp;
extern D3DXVECTOR3 CameraRotation;
extern FLOAT	   CameraFOV;

#define LAYER_NUM 1
extern VG::Layer		g_layers[LAYER_NUM];
extern VG::PathCommand	g_joint_style;
extern VG::PathCommand	g_ending_style;
extern VG::StrokeStyle	g_stroke_style;
extern float			g_line_widh;
extern float			g_dist_tolerance;

VOID Render();
HRESULT InitGeometry();
void BuildScene();

const int iWidth = 800;
const int iHeight = 600;
const bool fullScreen = false;


#define KEYDOWN(vk_key)  ((GetAsyncKeyState(vk_key) && 0x80000) ? true : false)
#define KEYUP(vk_key)  ((GetAsyncKeyState(vk_key) && 0x80000) ? false : true)


#endif // _MAIN_H__