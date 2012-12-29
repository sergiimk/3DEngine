/*========================================================
* Graphics.cpp
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/

#include "DXRenderer.h"
#include "CD3DRenderer.h"
#include "../Core/CommonPlugin.h"

Core::CommonPlugin *Core::CommonPlugin::Instance;
Core::GlobalEnvironment* Core::gEnv;

namespace DXRenderer
{
	BEGIN_MODULE_MAP()
		OBJECT_ENTRY_I(CLSID_CD3DRenderer, UUIDOF(IRenderer), CD3DRenderer)
		OBJECT_ENTRY_I(Core::CLSID_CommonPlugin, UUIDOF(Core::IPlugin), Core::CommonPlugin)
	END_MODULE_MAP()

} // namespace
