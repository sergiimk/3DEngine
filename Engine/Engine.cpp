/*========================================================
* Engine.cpp
* @author Sergey Mikhtonyuk
* @date 12 December 2008
=========================================================*/

#include "System/CEngine.h"
#include "MainLoop/CFSFrameWrapper.h"
#include "System/CSceneManager.h"
#include "Scene/CCmpAppearance.h"
#include "Scene/CCmpSpatialNode.h"
#include "Scene/CCmpPhysicalBody.h"
#include "../Core/CommonPlugin.h"
#include "Engine.h"

#include "Engine_classid.h"

Core::CommonPlugin* Core::CommonPlugin::Instance;
Core::GlobalEnvironment* Core::gEnv;

namespace Engine
{
		
	BEGIN_MODULE_MAP()
		OBJECT_ENTRY(CLSID_CCmpSpatialNode, CCmpSpatialNode)
		OBJECT_ENTRY(CLSID_CCmpAppearance, CCmpAppearance)
		OBJECT_ENTRY(CLSID_CCmpPhysicalBody, CCmpPhysicalBody)
		OBJECT_ENTRY(CLSID_CEngine, CEngine)
		OBJECT_ENTRY(CLSID_CFSFrameWrapper, CFSFrameWrapper)
		OBJECT_ENTRY_I(Core::CLSID_CommonPlugin, UUIDOF(Core::IPlugin), Core::CommonPlugin)
	END_MODULE_MAP()

} // namespace