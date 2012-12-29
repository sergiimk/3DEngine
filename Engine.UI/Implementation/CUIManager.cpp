/*========================================================
* CUIManager.cpp
* @author Sergey Mikhtonyuk
* @date 20 September 2009
=========================================================*/
#include "CUIManager.h"
#include "../../Engine.Graphics.VG/VGLib_impl.h"
#include "../../Engine/Interfaces/EginePlugin.h"

using namespace VG;

namespace Engine
{
	namespace UI
	{
		//////////////////////////////////////////////////////////////////////////

		void CUIManager::CreateLayer(VG::ILayer** outLayer)
		{
			*outLayer = 0;

			CLayer* pLayer;
			scom_new<CLayer>(&pLayer);
			pLayer->FinalConstruct(gEnv->Renderer);

			*outLayer = pLayer;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace