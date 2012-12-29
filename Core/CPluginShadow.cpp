/*========================================================
* CPluginShadow.cpp
* @author Sergey Mikhtonyuk
* @date 16 November 2008
=========================================================*/

#include "CPluginShadow.h"
#include "../Core.Logging/ILogger.h"
#include "CPluginManager.h"
#include "IExtension.h"
#include "IExtensionPoint.h"
#include "CCore.h"
#include <boost/bind.hpp>
#include <algorithm>

namespace Core
{
	//////////////////////////////////////////////////////////////////////////

	CPluginShadow::CPluginShadow()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CPluginShadow::~CPluginShadow()
	{
		LogTrace("[Shutdown] Unloading shadow: %s", mPluginName.c_str());

		std::for_each(mExtensions.begin(), mExtensions.end(), boost::mem_fn(&IUnknown::Release));
		std::for_each(mExtensionPoints.begin(), mExtensionPoints.end(), boost::mem_fn(&IUnknown::Release));
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginShadow::FinalConstruct(const std::string &pluginName, int version)
	{
		mVersion = version;
		mPluginName = pluginName;
		mModuleName = pluginName + ".dll";
	}

	//////////////////////////////////////////////////////////////////////////

	SCOM::HResult CPluginShadow::CreateInstance(const Core::SCOM::GUID &clsid, const Core::SCOM::GUID &riid, void **ppv)
	{
		if(!mModule.IsLoaded())
		{
			SCOM::HResult hr = LoadModule();
			if(SCOM_FAILED(hr)) return hr;
		}

		SCOM::HResult hr = mModule.CreateInstance(clsid, riid, ppv);
		if(SCOM_FAILED(hr))
		{
			LogWarningAlways("CreateInstance request failed, target: %s", mPluginName.c_str());
		}
		return hr;
	}

	//////////////////////////////////////////////////////////////////////////

	SCOM::HResult CPluginShadow::CreateInstance(const Core::SCOM::GUID &riid, void **ppv)
	{
		if(!mModule.IsLoaded())
		{
			SCOM::HResult hr = LoadModule();
			if(SCOM_FAILED(hr)) return hr;
		}

		SCOM::HResult hr = mModule.CreateInstance(riid, ppv);
		if(SCOM_FAILED(hr))
		{
			LogWarningAlways("CreateInstance request failed, target: %s", mPluginName.c_str());
		}
		return hr;
	}

	//////////////////////////////////////////////////////////////////////////

	SCOM::HResult CPluginShadow::LoadModule()
	{
		LogTrace("Loading plugin module: %s", mModuleName.c_str());

		SCOM::HResult hr = mModule.Init(mModuleName.c_str());
		if(SCOM_FAILED(hr)) return hr;
		return ((CPluginManager*)gEnv->PluginManager)->OnPluginLoad(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginShadow::Shutdown()
	{
		LogTrace("[Shutdown] Shadow shutdown: %s", mPluginName.c_str());
		mModule.Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Exports(const SCOM::GUID &clsid)
	{
		return mExportTable.find(clsid) != mExportTable.end();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Provides(const std::string &expoint)
	{
		return FindExtensionPoint(expoint) != 0;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Extends(const std::string &expoint)
	{
		for(std::vector<IExtension*>::const_iterator it = mExtensions.begin();
			it != mExtensions.end(); ++it)
			if((*it)->ExtensionPoint()->UniqueID() == expoint) return true;
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	
	IExtensionPoint* CPluginShadow::FindExtensionPoint(const std::string &name)
	{
		for(std::vector<IExtensionPoint*>::const_iterator it = mExtensionPoints.begin();
			it != mExtensionPoints.end(); ++it)
			if((*it)->ID() == name) return *it;
		return 0;
	}

} // namespace