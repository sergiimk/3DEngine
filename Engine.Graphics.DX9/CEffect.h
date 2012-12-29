/*========================================================
* CEffect.h
* @author Sergey Mikhtonyuk
* @date 19 August 2009
=========================================================*/
#ifndef _CEFFECT_H___
#define _CEFFECT_H___

#include "CBaseResource.h"
#include "../Engine.Graphics/Interfaces/IEffect.h"
#include "../Engine.Graphics/Interfaces/IEffectInstance.h"
#include "../Engine.Graphics/Interfaces/EffectTypes.h"
#include "DirectX.h"
#include "managers.h"
#include "../Core.COM/Implementations.h"
#include <string>
#include <hash_map>

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	struct CapsHash {
		size_t operator() (const SEffectCaps* caps) const
		{ return caps->hash(); }
	};

	struct CapsCmp {
		size_t operator() (const SEffectCaps* caps1, const SEffectCaps* caps2) const
		{ return (*caps1) == (*caps2); }
	};
	//////////////////////////////////////////////////////////////////////////

	/// Implementation of effect
	/** @ingroup DX9 */
	class NOVTABLE CEffect : 
		public Core::SCOM::ComRootObject<>,
		public CBaseResource<IEffect>
	{
	public:
		DECLARE_IMPLEMENTATION(CEffect)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IEffect)
			INTERFACE_ENTRY(IGraphicsResource)
			INTERFACE_ENTRY(IResourceInternal)
		END_INTERFACE_MAP()

		CEffect();
		~CEffect();
		void						FinalConstruct(const Utils::URL &url);
		const char*					GetEffectFileName() const;
		const SEffectDesc*			GetEffectDescription() const;

		IEffectInstance*			FindInstance(const SEffectCaps& caps) const;
		void						AddInstance(IEffectInstance* inst);

		IEffectManager*				GetManager()		{ return g_EffectManager; }

		void						Load();
		void						Unload();
		void						OnDeviceLost();
		void						OnDeviceReset();

	private:
		typedef std::hash_map<	const SEffectCaps*, 
								IEffectInstance*,
								CapsHash,
								CapsCmp >			TInstanceMap;


		SEffectDesc					mDesc;
		TInstanceMap				mInstances;
		std::string					mEffectFile;

	};

} // namespace

#endif // _CEFFECT_H___