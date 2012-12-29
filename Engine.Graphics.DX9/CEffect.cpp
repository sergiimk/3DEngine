/*========================================================
* CEffect.cpp
* @author Sergey Mikhtonyuk
* @date 19 August 2009
=========================================================*/
#include "CEffect.h"
#include "CEffectInstance.h"
#include "CEffectManager.h"
#include "../Core/CommonPlugin.h"
#include "../Core.Logging/ILogger.h"
#include "../Engine.Graphics.Parsers/EffectParser/EffectParser.h"
#include "../Engine.Graphics/RendererExceptions.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CEffect::CEffect()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffect::FinalConstruct(const Utils::URL &url)
	{
		mUrl = url;
		LogTrace("Effect resource created: %s", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	CEffect::~CEffect()
	{
		if(g_EffectManager)
			((CEffectManager*)g_EffectManager)->CloseResourceHandle(this);

		ASSERT_SOFT(mRefs == 0);
		if(mRefs)
			LogErrorAlways("[Memory leak] Effect %s still was loaded on release, missing RemoveUser call", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	const char* CEffect::GetEffectFileName() const
	{
		return mEffectFile.c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	const SEffectDesc* CEffect::GetEffectDescription() const
	{
		return &mDesc;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffect::Load()
	{
		EffectParser parser;
		if(!parser.Parse(mUrl.Name.c_str(), &mDesc, &mEffectFile))
		{
			ASSERT_SOFT(false);
			LogErrorAlways("Failed to load effect: %s", mUrl.Name.c_str());
			throw ResourceException("Failed to load effect");
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffect::Unload()
	{
		mDesc.clear();
		mEffectFile = "";
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffect::OnDeviceLost()
	{
		for(TInstanceMap::const_iterator it = mInstances.begin();
			it != mInstances.end();
			++it)
		{
			(static_cast<CEffectInstance*>(it->second))->OnDeviceLost();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffect::OnDeviceReset()
	{
		for(TInstanceMap::const_iterator it = mInstances.begin();
			it != mInstances.end();
			++it)
		{
			(static_cast<CEffectInstance*>(it->second))->OnDeviceReset();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	IEffectInstance* CEffect::FindInstance(const Engine::Graphics::SEffectCaps &caps) const
	{
		TInstanceMap::const_iterator it = mInstances.find(&caps);
		return it == mInstances.end() ? 0 : it->second;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffect::AddInstance(IEffectInstance* inst)
	{
		mInstances.insert(std::make_pair(inst->GetInstanceCaps(), inst));
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace