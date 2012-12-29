/*========================================================
* CEffectManager.cpp
* @author Sergey Mikhtonyuk
* @date 19 August 2009
=========================================================*/
#include "CEffectManager.h"
#include "../Core.Logging/ILogger.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "../Core/CommonPlugin.h"
#include "CEffect.h"
#include "CEffectInstance.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Core;
	using namespace SCOM;
	using namespace FileSystem;
	//////////////////////////////////////////////////////////////////////////

	CEffectManager::CEffectManager()
	{
		LogTrace("Creating effect manager");
	}

	//////////////////////////////////////////////////////////////////////////

	CEffectManager::~CEffectManager()
	{
		LogTrace("Destroying effect manager");

		mDefaultEffect.Release();

		ASSERT_SOFT(!mEffects.size());

		if(!mEffects.size())
			for(EffectMapCIter it = mEffects.begin(); it != mEffects.end(); ++it)
				LogErrorAlways("[Memory leak] Effect %s was not released before shutdown", it->second->GetURL()->Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectManager::FindOrLoadEffect(const Utils::URL &url, IEffect** outEffect) 
	{
		*outEffect = 0;

		// Make full path
		Utils::URL nurl(
			gEnv->FileSystem->PathCombine(
				"../Resources/Meshes/Effects/DeferredLighting", 
				url.Name.c_str()
				));

		// Try find loaded
		EffectMapIter it = mEffects.find(nurl.Name);
		if(it != mEffects.end())
		{
			*outEffect = it->second;
			(*outEffect)->AddRef();
			return;
		}

		// Create effect
		CEffect* pe;
		scom_new<CEffect>(&pe);
		pe->FinalConstruct(nurl);
		mEffects.insert(std::make_pair(nurl.Name, pe));
		*outEffect = pe;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectManager::CreateEffectInstance(IEffect *pEffect, const SEffectCaps &caps, IEffectInstance** outInstance)
	{
		*outInstance = 0;
		SEffectCaps resCaps = caps;
		CEffect* cEffect = static_cast<CEffect*>(pEffect);

		// Get the intersection of caps sets
		for(SEffectCaps::iterator cit = resCaps.begin(); cit != resCaps.end(); ++cit)
		{
			if(!pEffect->GetEffectDescription()->getCapSupport(cit->cap))
				resCaps.setSupportState(cit->cap, false);
		}
		
		// Check for existing instance
		IEffectInstance* inst = cEffect->FindInstance(resCaps);
		if(inst)
		{
			*outInstance = inst;
			(*outInstance)->AddRef();
			return;
		}

		// Validate caps


		// Create instance
		CEffectInstance* cinst;
		scom_new<CEffectInstance>(&cinst);
		cinst->FinalConstruct(pEffect, resCaps);

		// Add instance to collection
		cEffect->AddInstance(cinst);
		*outInstance = cinst;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectManager::GetDefaultEffect(IEffect** outEffect)
	{
		*outEffect = 0;

		/// \todo Load default effect name from settings
		if(!mDefaultEffect)
			FindOrLoadEffect(Utils::URL("default.fxd"), mDefaultEffect.wrapped());

		*outEffect = mDefaultEffect;
		(*outEffect)->AddRef();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectManager::CloseResourceHandle(IEffect* effect)
	{
		EffectMapIter it = mEffects.find(effect->GetURL()->Name);
		ASSERT_STRICT(it != mEffects.end());
		mEffects.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectManager::OnDeviceLost()
	{
		for(EffectMapCIter it = mEffects.begin(); it != mEffects.end(); ++it)
			it->second->OnDeviceLost();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectManager::OnDeviceReset()
	{
		for(EffectMapCIter it = mEffects.begin(); it != mEffects.end(); ++it)
			it->second->OnDeviceReset();
	}	

	//////////////////////////////////////////////////////////////////////////
} // namespace