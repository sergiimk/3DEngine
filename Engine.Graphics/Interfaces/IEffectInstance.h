/*========================================================
* IEffectInstance.h
* @author Sergey Mikhtonyuk
* @date 19 August 2009
=========================================================*/
#ifndef _IEFFECTINSTANCE_H__
#define _IEFFECTINSTANCE_H__

#include "IResourceInternal.h"

namespace Engine
{
	namespace Graphics
	{

		/// Result of effect compilation with specific set of capabilities (caps)
		/** @ingroup Graphics */
		SCOM_INTERFACE(IEffectInstance, "efd0a950-b871-469d-9ee6-98c9a1806602", Core::SCOM::IUnknown)
		{
		public:

			/// Returns the instantiated effect
			virtual IEffect* GetSrcEffect() const = 0;

			/// Returns the capability set of effect instance
			virtual const SEffectCaps* GetInstanceCaps() const = 0;

			/// Returns the parameter set required by effect instance
			virtual const SEffectParams* GetInstanceParameters() const = 0;

			/// Initiates the parameter update
			/// \todo refactor
			virtual void UpdateParameters() = 0;
		
			/// Begins rendering sequence, sequence can consist of multiple passes
			/** @return number of passes in the sequence */
			virtual unsigned int BeginSequence() = 0;

			/// Ends running sequence
			virtual void EndSequence() = 0;

			/// Begins specified rendering pass
			virtual void BeginPass(unsigned int pass) = 0;

			/// Ends rendering pass
			virtual void EndPass() = 0;
		};

	} // namespace
} // namespace

#endif // _IEFFECTINSTANCE_H__