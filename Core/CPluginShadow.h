/*========================================================
* CPluginShadow.h
* @author Sergey Mikhtonyuk
* @date 16 November 2008
=========================================================*/
#ifndef _CPLUGINSHADOW_H__
#define _CPLUGINSHADOW_H__

#include "IPluginShadow.h"
#include "../Core.COM/Implementations.h"
#include <hash_set>
#include "../Core.Utils/GuidHashCmp.h"
#include <string>
#include <vector>
#include "../Core.COM/Module.h"


namespace Core
{

	/// Implements IPluginShadow interface
	/** Implementation of proxy object for plug-in 
	  *
	  * @ingroup Core */
	class NOVTABLE CPluginShadow : 
		public SCOM::ComRootObject<>,
		public IPluginShadow
	{
	public:
		DECLARE_IMPLEMENTATION(CPluginShadow)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IPluginShadow)
		END_INTERFACE_MAP()

		CPluginShadow();
		virtual	~CPluginShadow();

		const std::string& PluginName() { return mPluginName; }
		const std::string& ModuleName() { return mModuleName; }

		bool Exports(const SCOM::GUID &clsid);
		bool Provides(const std::string &expoint);
		bool Extends(const std::string &expoint);

		SCOM::HResult CreateInstance(SCOM_RIID clsid, SCOM_RIID riid, void** ppv);
		SCOM::HResult CreateInstance(SCOM_RIID riid, void** ppv);

		size_t getExtensionCount() { return mExtensions.size(); }
		IExtension* getExtension(size_t index) { return mExtensions[index]; }
		size_t getExtensionPointCount() { return mExtensionPoints.size(); }
		IExtensionPoint* getExtensionPoint(size_t index) { return mExtensionPoints[index]; }

		IExtensionPoint* FindExtensionPoint(const std::string& name);

	/* internal: */
		void			FinalConstruct(const std::string &pluginName, int version);
		SCOM::HResult	LoadModule();
		void			Shutdown();

	/* internal: */
		int				mVersion;
		std::string		mPluginName;
		std::string		mModuleName;
		SCOM::Module	mModule;

		typedef std::hash_set<SCOM::GUID, GUIDHash> TExportTable;

		/// Provides quick look-up for exported classes
		TExportTable					mExportTable;
		std::vector<IExtension*>		mExtensions;
		std::vector<IExtensionPoint*>	mExtensionPoints;
	};

} // namespace

#endif // _CPLUGINSHADOW_H__