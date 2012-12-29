/*========================================================
* test.cpp
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/

#include "CTestGame.h"
#include "../Engine/Interfaces/EginePlugin.h"

Engine::EnginePlugin*		Engine::EnginePlugin::Instance;
Core::GlobalEnvironment*	Core::gEnv;
Engine::GlobalEnvironment*	Engine::gEnv;

// {f0b39d90-0386-4888-83dd-6ebc98651aaa} 
static const Core::SCOM::GUID CLSID_CTestGame = 
{ 0xf0b39d90, 0x0386, 0x4888, { 0x83, 0xdd, 0x6e, 0xbc, 0x98, 0x65, 0x1a, 0xaa } };

BEGIN_MODULE_MAP()
	OBJECT_ENTRY(CLSID_CTestGame, CTestGame)
	OBJECT_ENTRY_I(Engine::CLSID_EnginePlugin, UUIDOF(Core::IPlugin), Engine::EnginePlugin)
END_MODULE_MAP()