/*========================================================
* EginePlugin.h
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#ifndef _EGINEPLUGIN_H__
#define _EGINEPLUGIN_H__

#include "../../Core/CommonPlugin.h"
#include "GlobalEnvironment.h"

namespace Engine
{
	/// Similar to CommonPlugin but also resolves global environment to extended one
	/** @ingroup Engine */
	class NOVTABLE EnginePlugin : 
		public Core::SCOM::ComRootObject<>,
		public Core::IPlugin
	{
	public:
		DECLARE_IMPLEMENTATION2(EnginePlugin, Core::SCOM::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(Core::IPlugin)
		END_INTERFACE_MAP()

		EnginePlugin() 
		{
			Instance = this;
		}

		void Initialize(Core::GlobalEnvironment* pEnv, Core::IPluginShadow* pShadow)
		{
			Core::gEnv = pEnv;
			Engine::gEnv = (Engine::GlobalEnvironment*)pEnv;
			MyShadow = pShadow;
		}

		Core::IPluginShadow* PluginShadow() { return MyShadow; }
		Core::IPluginShadow* MyShadow;

		static EnginePlugin *Instance;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Class ID of engine plug-in, it is not important, because plug-in lookup is done by interface.
	// {298b5f61-a5a2-4dac-a1f8-9a2c2c05cdd1} 
	static const Core::SCOM::GUID CLSID_EnginePlugin = 
	{ 0x298b5f61, 0xa5a2, 0x4dac, { 0xa1, 0xf8, 0x9a, 0x2c, 0x2c, 0x05, 0xcd, 0xd1 } };

	//////////////////////////////////////////////////////////////////////////
} // namespace

#endif	// _EGINEPLUGIN_H__