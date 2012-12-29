/*========================================================
* IEffectManager.h
* @author Sergey Mikhtonyuk
* @date 19 August 2009
=========================================================*/
#ifndef _IEFFECTMANAGER_H__
#define _IEFFECTMANAGER_H__

#include "IResourceManager.h"
#include "../../Core.Utils/URL.h"

namespace Engine
{
	namespace Graphics
	{
		/// Used to access effects and their caps permutations (aka shader cache)
		/** @ingroup Graphics */
		SCOM_INTERFACE(IEffectManager, "54acec8e-3448-419e-a0a5-96d8673e801a", IResourceManager)
		{
		public:
		
			/// Returns the effect objects
			virtual void FindOrLoadEffect(const Utils::URL &url, IEffect** outEffect) = 0;

			/// Creates or reuses the effect instance
			/** @param pEffect A prototype used for compilation
			 *  @param caps Compilation flags (should be a subset of effect caps)
			 *  @param outInstance Created effect instance */
			virtual void CreateEffectInstance(IEffect *pEffect, const SEffectCaps &caps, IEffectInstance** outInstance) = 0;

			/// Returns default effect
			virtual void GetDefaultEffect(IEffect** outEffect) = 0;
		};

	} // namespace
} // namespace

#endif // _IEFFECTMANAGER_H__