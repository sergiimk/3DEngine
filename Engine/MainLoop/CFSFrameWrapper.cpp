/*========================================================
* CFSFrameWrapper.cpp
* @author Sergey Mikhtonyuk
* @date 10 April 2009
=========================================================*/
#include "CFSFrameWrapper.h"
#include "../../Core/CommonPlugin.h"
#include "../../Core/SekaiCore.h"
#include "../../Core.FileSystem/FileSystem.h"

namespace Engine
{
	CFSFrameWrapper::CFSFrameWrapper()
	{
		assert(Core::gEnv->FileSystem);
	}

	//////////////////////////////////////////////////////////////////////////

	void CFSFrameWrapper::Initialize(Engine::IMainLoop *pMainLoop)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	int CFSFrameWrapper::OnFrame()
	{
		Core::gEnv->FileSystem->Proactor().DispatchMessages();
		return 2;
	}

} // namespace