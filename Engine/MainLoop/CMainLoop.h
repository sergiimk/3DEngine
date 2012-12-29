/*========================================================
* CMainLoop.h
* @author Sergey Mikhtonyuk
* @date 12 December 2008
=========================================================*/
#ifndef _CMAINLOOP_H__
#define _CMAINLOOP_H__

#include "../Interfaces/IMainLoop.h"
#include "../Interfaces/IFrameListener.h"
#include "../../Core.Time/SystemTimeSource.h"
#include "../../Core.Time/CClock.h"
#include "../../Core.COM/Implementations.h"
#include "../../Core.COM/Intellectual.h"
#include <vector>

namespace Core { class IExtension; }

namespace Engine
{

	/// Implementation of IMainLoop interface
	/** @ingroup Engine */
	class NOVTABLE CMainLoop : 
		public Core::SCOM::ComRootObject<>,
		public IMainLoop
	{
	public:
		DECLARE_IMPLEMENTATION2(CMainLoop, Core::SCOM::ComClassFactorySingleton)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IMainLoop)
		END_INTERFACE_MAP()

		CMainLoop();
		~CMainLoop();

		void Start();
		__int64 getFrameNumber() const;
		Time::IClock* getApplicationClock() const;

	protected:
		void	InitTime();
		void	LoadExtenders();
		int		GetPriorityOfListener(Core::IExtension *pEx);
		void	Loop();

	protected:
		typedef std::vector< std::pair<int, IFrameListener*> > TListenerList;
		TListenerList	mListeners;

		__int64					mFrameNum;
		Time::CClock			mClock;
		Time::SystemTimeSource	mTimeSource;
	};



} // namespace


#endif // _CMAINLOOP_H__