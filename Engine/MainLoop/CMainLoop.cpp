/*========================================================
* CMainLoop.cpp
* @author Sergey Mikhtonyuk
* @date 12 December 2008
=========================================================*/

#include "CMainLoop.h"
#include "../../Core/SekaiCore.h"
#include "../../Core/CommonPlugin.h"
#include "../../Core.Logging/ILogger.h"
#include <sstream>
#include <algorithm>

namespace Engine
{
	using namespace Core;
	using namespace SCOM;

	//////////////////////////////////////////////////////////////////////////

	CMainLoop::CMainLoop() : mFrameNum(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CMainLoop::~CMainLoop()
	{
		for(size_t i = 0; i != mListeners.size(); ++i)
			mListeners[i].second->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMainLoop::Start()
	{
		LogTrace("Initializing main loop");
		InitTime();
		LoadExtenders();
		Loop();
		LogTrace("Shutting down main loop");
	}

	//////////////////////////////////////////////////////////////////////////

	void CMainLoop::InitTime()
	{
		mClock.setTimeSource(&mTimeSource);
	}

	//////////////////////////////////////////////////////////////////////////

	template<class T1, class T2>
	inline bool sort_pair_first(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
	{
		return left.first < right.first;
	}

	//////////////////////////////////////////////////////////////////////////

	void CMainLoop::LoadExtenders()
	{
		IPluginShadow* myShadow = CommonPlugin::Instance->PluginShadow();
		IExtensionPoint* myPoint = myShadow->FindExtensionPoint("framelisteners");

		size_t nextensions = myPoint->getExtensionCount();
		mListeners.reserve(nextensions);

		for(size_t i = 0; i != nextensions; ++i)
		{
			IFrameListener* l;
			IExtension* extension = myPoint->getExtension(i);
			extension->Extender()->CreateInstance(extension->ImplClassID(), UUID_PPV(IFrameListener, &l));

			int priority = GetPriorityOfListener(extension);

			if(l && priority != -1)
			{
				mListeners.push_back(std::make_pair(priority, l));
			}
			else
			{
				LogErrorAlways("Failed to initialize frameListener: %s", 
								extension->Extender()->PluginName().c_str());
			}
		}

		std::sort(mListeners.begin(), mListeners.end(), sort_pair_first<int, IFrameListener*>);

		LogTrace("Inializing frame listeners");
		for(size_t i = 0; i != mListeners.size(); ++i)
			mListeners[i].second->Initialize(this);
	}

	//////////////////////////////////////////////////////////////////////////

	int CMainLoop::GetPriorityOfListener(IExtension *pEx)
	{
		const char* prior = pEx->getParameter("priority");
		if(!prior) return -1;

		int p = -1;
		std::istringstream iss(prior);
		iss >> p;

		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	void CMainLoop::Loop()
	{
		LogTrace("Starting main loop with %d listener(s)", mListeners.size());
		size_t dontcares;
		mClock.Update();

		// Frame loop
		while(true)
		{
			dontcares = 0;
			mClock.Update();

			// Polling all listeners
			for(size_t i = 0; i != mListeners.size(); )
			{
				int t = mListeners[i].second->OnFrame();
				
				switch(t)
				{
				case -1:	return; // Tear the loop
				case 1:		mListeners.erase(mListeners.begin() + i); continue; // Remove listener
				case 2:		++dontcares; // Count don't care ones
				default:	 ++i;
				};
			}

			++mFrameNum;

			if (dontcares == mListeners.size())
				return;

		} // Frame loop
	}

	//////////////////////////////////////////////////////////////////////////

	__int64 CMainLoop::getFrameNumber() const
	{
		return mFrameNum;
	}

	//////////////////////////////////////////////////////////////////////////

	Time::IClock* CMainLoop::getApplicationClock() const
	{
		return (Time::IClock*)&mClock;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace