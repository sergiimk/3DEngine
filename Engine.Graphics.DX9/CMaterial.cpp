/*========================================================
* CMaterial.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "CMaterial.h"
#include "CMaterialManager.h"
#include "../Engine.Graphics/Interfaces/IEffectManager.h"
#include "../Engine.Graphics/RendererExceptions.h"
#include "../Core/CommonPlugin.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "../Core.Logging/ILogger.h"

#include "../Engine.Graphics/Interfaces/ISurfaceManager.h"
#include "../Engine.Graphics/Interfaces/ITexture.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CMaterial::CMaterial()
	{
	}
	
	//////////////////////////////////////////////////////////////////////////

	void CMaterial::FinalConstruct(const Utils::URL &url)
	{
		mUrl = url;
		LogTrace("Material resource created: %s", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	CMaterial::~CMaterial()
	{
		if(g_MaterialManager && mUrl.Name.length())
			((CMaterialManager*)g_MaterialManager)->CloseResourceHandle(this);

		ASSERT_SOFT(mRefs == 0);
		if(mRefs)
			LogErrorAlways("[Memory leak] Material %s still was loaded on release, missing RemoveUser call", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	const char* CMaterial::GetName() const
	{
		return mName.c_str();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::Load()
	{
		if(mUrl.Name.length())
		{
			/// Bound to material file - parse parameters
			MaterialParser parser;

			if(!parser.Parse(mUrl.Name.c_str(), this))
			{
				ASSERT_SOFT(false);
				LogErrorAlways("Failed to load material: %s", mUrl.Name.c_str());
				throw ResourceException("Failed to load material");
			}
		}
		/// else - Manual material persists all settings across the load\unload cycle

		//if(!mEffect)
		//	g_EffectManager->GetDefaultEffect(mEffect.wrapped());

		for(int i = 0; i != NUM_EFFECT_STAGES; ++i)
			if(mEffects[i])
				mEffects[i]->AddUser();

		mBindings.setInUse(true);
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::Unload()
	{
		mBindings.setInUse(false);
		for(int i = 0; i != NUM_EFFECT_STAGES; ++i)
		{
			if(mEffects[i])
				mEffects[i]->RemoveUser();

			mEffectInstances[i].Release();

			if(mUrl.Name.length())
				mEffects[i].Release();
		}
			

		if(mUrl.Name.length())
		{
			mName = "";
			mBindings.clear();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	IEffect* CMaterial::GetEffect(size_t stage) const
	{
		ASSERT_STRICT(stage < NUM_EFFECT_STAGES);
		return mEffects[stage];
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::SetEffect(size_t stage, IEffect* effect)
	{
		ASSERT_STRICT(stage < NUM_EFFECT_STAGES);

		if(IsLoaded() && mEffects[stage])
			mEffects[stage]->RemoveUser();

		mEffects[stage] = effect;
		mEffectInstances[stage].Release();
	}

	//////////////////////////////////////////////////////////////////////////

	IEffectInstance* CMaterial::GetEffectInstance(size_t stage) const
	{
		ASSERT_STRICT(stage < NUM_EFFECT_STAGES);
		return mEffectInstances[stage];
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::SetEffectInstance(size_t stage, IEffectInstance *inst)
	{
		ASSERT_STRICT(stage < NUM_EFFECT_STAGES);
		mEffectInstances[stage] = inst;

		if(inst)
		{
			ASSERT_STRICT(inst->GetSrcEffect() == mEffects[stage]);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	SMaterialBindings* CMaterial::GetBindings()
	{
		return &mBindings;
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnDeviceLost()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnDeviceReset()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnError(const char* msg)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnMaterialName(const char* name)
	{
		mName = name;
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnEffectDefinition(size_t stage, const char* effect)
	{
		ASSERT_STRICT(stage < NUM_EFFECT_STAGES);

		g_EffectManager->FindOrLoadEffect(Utils::URL(effect), mEffects[stage].wrapped());
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnFloatBinding(EEffectParam param, float val)
	{
		mBindings.addFloatBinding(param, val);
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnTextureBinding(EEffectParam param, const char* path)
	{
		mBindings.addTextureBinding(param, path, g_SurfaceManager);
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterial::OnColorBinding(EEffectParam param, const VML::Vector4& val)
	{
		mBindings.addColorBinding(param, val);
	}

	//////////////////////////////////////////////////////////////////////////


} // namespace
