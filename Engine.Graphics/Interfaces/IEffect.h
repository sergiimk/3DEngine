/*========================================================
* IEffect.h
* @author Sergey Mikhtonyuk
* @date 16 August 2009
=========================================================*/
#ifndef _IEFFECT_H__
#define _IEFFECT_H__

#include "IResourceInternal.h"

namespace Engine
{
	namespace Graphics
	{

		/// A template that is used to create effect instances for scene shading
		/** Effect describes a file that can be used to produce multiple shading
		 *  programs by effect caps permutation
		 *  @ingroup Graphics */
		SCOM_INTERFACE(IEffect, "b4bbc88f-c888-464f-b1a0-e4f13943733e", IResourceInternal)
		{
		public:

			/// Returns the name of file with shading program
			virtual const char* GetEffectFileName() const = 0;

			/// Returns the structure of effect capabilities and required parameters
			virtual const SEffectDesc* GetEffectDescription() const = 0;

			/// Returns the effect manager which crated this effect
			virtual IEffectManager* GetManager() = 0;
		};

	} // namespace
} // namespace

#endif // _IEFFECT_H__