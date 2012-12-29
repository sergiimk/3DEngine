/*========================================================
* CEffectManager.h
* @author Sergey Mikhtonyuk
* @date 19 August 2009
=========================================================*/
#ifndef _CEFFECTMANAGER_H__
#define _CEFFECTMANAGER_H__

#include "../Engine.Graphics/Interfaces/IEffectManager.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"
#include <hash_map>

namespace DXRenderer
{

	using namespace Engine::Graphics;

	/// Concrete effect manager
	/** @ingroup DX9 */
	class NOVTABLE CEffectManager : 
		public Core::SCOM::ComRootObject<>,
		public IEffectManager
	{
	public:
		DECLARE_IMPLEMENTATION(CEffectManager)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IEffectManager)
			INTERFACE_ENTRY(IResourceManager)
		END_INTERFACE_MAP()

		CEffectManager();
		~CEffectManager();

		void FindOrLoadEffect(const Utils::URL &url, IEffect** outEffect);

		void CreateEffectInstance(IEffect *pEffect, const SEffectCaps &caps, IEffectInstance** outInstance);

		void GetDefaultEffect(IEffect** outEffect);

		void		CloseResourceHandle(IEffect* effect);

		void		OnDeviceLost();
		void		OnDeviceReset();

	private:
		typedef std::hash_map<std::string, IEffect*>	EffectMap;
		typedef EffectMap::iterator						EffectMapIter;
		typedef EffectMap::const_iterator				EffectMapCIter;

		EffectMap						mEffects;
		Core::SCOM::ComPtr<IEffect>		mDefaultEffect;
	};	

} // namespace

#endif // _CEFFECTMANAGER_H__