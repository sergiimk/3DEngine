/*========================================================
* IMaterial.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __IMATERIAL_H__
#define __IMATERIAL_H__

#include "IResourceInternal.h"
#include "MaterialTypes.h"

namespace Engine
{
	namespace Graphics
	{
		// Defines the maximum number of effect stages
		#define NUM_EFFECT_STAGES 2

		/// Interface to resource that stores surface parameters
		/** @ingroup Graphics */
		SCOM_INTERFACE(IMaterial, "8f608c53-fdc8-4646-ba37-20be18b077ff", IResourceInternal)
		{
		public:

			/// Returns the effect that should be used for shading for specified stage
			virtual IEffect* GetEffect(size_t stage) const = 0;

			/// Sets the new shading effect for specified stage
			/** Stages are useful for complex rendering schemes like
			 *  deferred lighting, when one object can be rendered multiple
			 *  times with different effect (first g-buffer, than lighting) */
			virtual void SetEffect(size_t stage, IEffect* effect) = 0;

			/// Returns the compiled effect for shading for specified stage
			virtual IEffectInstance* GetEffectInstance(size_t stage) const = 0;

			/// Sets the effect instance to be used for shading for specified stage
			virtual void SetEffectInstance(size_t stage, IEffectInstance* inst) = 0;

			/// Returns the bindings structure
			virtual SMaterialBindings* GetBindings() = 0;
			
			/// Returns manager that created this material
			virtual IMaterialManager* GetManager() = 0;
		};

	} // namespace
} // namespace

#endif