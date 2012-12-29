/*========================================================
* managers.h
* @author Sergey Mikhtonyuk
* @date 09 April 2009
=========================================================*/
#ifndef _DXRENDERER_MANAGERS_H__
#define _DXRENDERER_MANAGERS_H__

#include "../Engine.Graphics/Graphics_fwd.h"

namespace DXRenderer
{
	
	extern Engine::Graphics::IRenderer*			g_Renderer;
	extern Engine::Graphics::IGeometryManager*	g_GeometryManager;
	extern Engine::Graphics::ISurfaceManager*	g_SurfaceManager;
	extern Engine::Graphics::IMaterialManager*	g_MaterialManager;
	extern Engine::Graphics::IEffectManager*	g_EffectManager;

} // namespace

#endif	// _DXRENDERER_MANAGERS_H__