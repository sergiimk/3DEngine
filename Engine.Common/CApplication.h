/*========================================================
* CApplication.h
* @author Sergey Mikhtonyuk
* @date 22 May 2009
=========================================================*/
#ifndef _CAPPLICATION_H__
#define _CAPPLICATION_H__

#include "../Engine/Engine.h"
#include "../Engine/Interfaces/EginePlugin.h"
#include "../Engine.Input/IInputController.h"
#include "../Engine/Interfaces/IFrameListener.h"
#include "../Core.Time/IClock.h"
#include "../Core.Logging/ILogger.h"
#include "../Core.COM/Implementations.h"

namespace Engine
{
	namespace Common
	{

		//////////////////////////////////////////////////////////////////////////
		class NOVTABLE CApplication : 
			public Core::SCOM::ComRootObject<>,
			public IFrameListener
		{
		public:
			DECLARE_IMPLEMENTATION(CApplication)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IFrameListener)
			END_INTERFACE_MAP()

			CApplication() : mWidth(1024), mHeight(768) { }

			// Base methods
			void	Initialize(IMainLoop *pMainLoop);
			int		OnFrame();

			// Overridable methods
			virtual void	SetupScene();
			virtual void	ProcessInput(double frameDelta);
			virtual void	Render(double frameDelta);

		public:
			void* getHWnd() const { return mHwnd; }
			void* getHInst() const { return mHinstance; }
			static CApplication* Instance() { return sInstance; }

		private:
			void	CreateWnd();
			bool	WinFrame();

			static CApplication*	sInstance;
		protected:
			void*					mHwnd;
			void*					mHinstance;
			int						mWidth;
			int						mHeight;
		};
		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _CAPPLICATION_H__