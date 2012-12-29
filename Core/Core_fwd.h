/*========================================================
* Core_fwd.h
* @author Sergey Mikhtonyuk
* @date 29 June 2009
=========================================================*/
#ifndef _CORE_FWD_H__
#define _CORE_FWD_H__

namespace Core
{

	class ICore;
	class IPlugin;
	class IPluginManager;
	class IPluginShadow;
	class IExtension;
	class IStartListener;
	class IExtensionPoint;

	namespace Logging { class ILogger; }

	struct GlobalEnvironment;

} // namespace

#endif // _CORE_FWD_H__