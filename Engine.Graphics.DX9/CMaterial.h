/*========================================================
* CMaterial.h
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#ifndef __CMATERIAL_H__
#define __CMATERIAL_H__

#include "CBaseResource.h"
#include "../Engine.Graphics/Interfaces/IMaterial.h"
#include "../Engine.Graphics/Interfaces/IEffect.h"
#include "../Engine.Graphics/Interfaces/IEffectInstance.h"
#include "../Engine.Graphics/Interfaces/ITexture.h"
#include "DirectX.h"
#include "managers.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"
#include "../Engine.Graphics.Parsers/MaterialParser/MaterialParser.h"
#include <string>
#include <vector>

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	//////////////////////////////////////////////////////////////////////////

	/// Concrete class of material
	/** @ingroup DX9 */
	class NOVTABLE CMaterial : 
		public Core::SCOM::ComRootObject<>,
		public CBaseResource<IMaterial>,
		public IMaterialParsingCallback
	{
	public:
		DECLARE_IMPLEMENTATION(CMaterial)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IMaterial)
			INTERFACE_ENTRY(IGraphicsResource)
			INTERFACE_ENTRY(IResourceInternal)
		END_INTERFACE_MAP()
	
		CMaterial();
		~CMaterial();
		void FinalConstruct(const Utils::URL &url);

		const char*					GetName() const;
		IEffect*					GetEffect(size_t stage) const;
		void						SetEffect(size_t stage, IEffect* effect);
		IEffectInstance*			GetEffectInstance(size_t stage) const;
		void						SetEffectInstance(size_t stage, IEffectInstance* inst);
		SMaterialBindings*			GetBindings();

		IMaterialManager*			GetManager()		{ return g_MaterialManager; }

		void						Load();
		void						Unload();
		void						OnDeviceLost();
		void						OnDeviceReset();

		//////////////////////////////////////////////////////////////////////////
		void OnError(const char* msg);
		void OnMaterialName(const char* name);
		void OnEffectDefinition(size_t stage, const char* effect);
		void OnFloatBinding(EEffectParam param, float val);
		void OnTextureBinding(EEffectParam param, const char* path);
		void OnColorBinding(EEffectParam param, const VML::Vector4& val);
		//////////////////////////////////////////////////////////////////////////

	private:
		SMaterialBindings					mBindings;
		std::string							mName;
		Core::SCOM::ComPtr<IEffect>			mEffects[NUM_EFFECT_STAGES];
		Core::SCOM::ComPtr<IEffectInstance> mEffectInstances[NUM_EFFECT_STAGES];
	};	

} // namespace

#endif