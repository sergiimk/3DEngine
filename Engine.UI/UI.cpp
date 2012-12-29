/*========================================================
* UI.cpp
* @author Sergey Mikhtonyuk
* @date 20 September 2009
=========================================================*/

#include "Implementation/CUIManager.h"
#include "../Engine/Interfaces/EginePlugin.h"

Engine::EnginePlugin*		Engine::EnginePlugin::Instance;
Core::GlobalEnvironment*	Core::gEnv;
Engine::GlobalEnvironment*	Engine::gEnv;

namespace Engine
{
	namespace UI
	{
		// {36e69f9e-8a3c-421a-8720-09f527ef0217} 
		static const Core::SCOM::GUID CLSID_CUIManager = 
		{ 0x36e69f9e, 0x8a3c, 0x421a, { 0x87, 0x20, 0x09, 0xf5, 0x27, 0xef, 0x02, 0x17 } };

		BEGIN_MODULE_MAP()
			OBJECT_ENTRY_I(CLSID_CUIManager, UUIDOF(IUIManager), CUIManager)
			OBJECT_ENTRY_I(Core::CLSID_CommonPlugin, UUIDOF(Core::IPlugin), Engine::EnginePlugin)
		END_MODULE_MAP()

	} // namespace
} // namespace