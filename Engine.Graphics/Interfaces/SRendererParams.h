/*========================================================
* SRendererParams.h
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#ifndef _SRENDERERPARAMS_H__
#define _SRENDERERPARAMS_H__

#include "SSurfaceDesc.h"

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////
		typedef void*	WND_HANDLE;
		//////////////////////////////////////////////////////////////////////////

		/// Describe renderer initialization (and reset parameters)
		/** @ingroup Graphics */
		struct SRendererParams
		{
			int				ScreenWidth;		// Width of back buffer
			int				ScreenHeight;		// Height of back buffer
			bool			FullScreen;			// Should renderer run in full screen?
			EBufferFormat	BackBufferFormat;	// Format of back buffer
			WND_HANDLE		MainWindow;			// Main window handle
		};

		//////////////////////////////////////////////////////////////////////////
	} // namespace
} // namespace

#endif	// _SRENDERERPARAMS_H__