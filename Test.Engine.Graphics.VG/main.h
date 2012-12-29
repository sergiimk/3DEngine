#ifndef _MAIN_H__
#define _MAIN_H__

#include <Windows.h>
#include "../Core/IPlugin.h"
#include "../Core/GlobalEnvironment.h"
#include "../Core.COM/Module.h"
#include "../Core.FileSystem/FileSystem.h"
#include "../Engine.Graphics/Graphics.h"
#include "../Engine.Graphics.VG/VGLib_impl.h"
#include <vector>

using namespace Core;
using namespace SCOM;
using namespace FileSystem;
using namespace Engine::Graphics;
using namespace VG;

//////////////////////////////////////////////////////////////////////////
// Globals
//////////////////////////////////////////////////////////////////////////

extern IRenderer*	pRenderer;
extern ILayer*		g_layer;

extern VG::PathCommand	g_joint_style;
extern VG::PathCommand	g_ending_style;
extern VG::StrokeStyle	g_stroke_style;
extern float			g_line_widh;
extern float			g_dist_tolerance;
extern VML::Vector3 	g_cameraPos;

VOID Render();
HRESULT InitGeometry();
void BuildTiger();

const int iWidth = 800;
const int iHeight = 600;
const bool fullScreen = false;


#define KEYDOWN(vk_key)  ((GetAsyncKeyState(vk_key) && 0x80000) ? true : false)
#define KEYUP(vk_key)  ((GetAsyncKeyState(vk_key) && 0x80000) ? false : true)


#endif // _MAIN_H__