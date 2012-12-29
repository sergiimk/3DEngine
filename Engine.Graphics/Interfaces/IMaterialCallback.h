/*========================================================
* IMaterialCallback.h
* @author Sergey Mikhtonyuk
* @date 13 May 2009
=========================================================*/
#ifndef _IMATERIALCALLBACK_H__
#define _IMATERIALCALLBACK_H__

#include "IMaterial.h"
#include "../../Core.Math/VML_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	namespace Graphics
	{

		/// Callback is used by materials to query all data needed to perform rendering
		/** In layer-preserving concerns one callback (like the default one in renderer) can't
		 *  provide all needed data. For example, we separated spatial management from renderer
		 *  completely, but some times we need to access such data as positions of lights that
		 *  have influence on the object, or position of the sun for directional lighting. To
		 *  provide such data and preserve layers you can use callback chaining, that means that
		 *  callbacks can form a linked list, and if query can't be satisfied by first callback,
		 *  it will be passed along the chain until it will be satisfied or fail completely
		 *  (see Chain of Responsibility pattern [GoF])
		 *
		 *  @ingroup Graphics */
		SCOM_INTERFACE(IMaterialCallback, "0270c16d-71e9-4c9f-967d-75365b06d61d", Core::SCOM::IUnknown)
		{
		public:
			/// Queries callback to supply matrix parameter of specified type
			virtual void SupplyMatrix(EEffectParam param_type, VML::Matrix4& m_out) = 0;

			/// Queries the vector parameter
			virtual void SupplyVector(EEffectParam param_type, VML::Vector4& v_out) = 0;

			/// Queries the color parameter
			virtual void SupplyColor(EEffectParam param_type, VML::Vector4& clr_out) = 0;

			/// Queries callback to supply texture parameter of specified type
			virtual void SupplyTexture(EEffectParam param_type, ITexture** ppTexture) = 0;

			/// Queries the float parameter
			virtual void SupplyFloat(EEffectParam param_type, float& f_out) = 0;

			/// Query of effect caps for instantiation
			/** This query is passed through all of the callbacks in chain
			 *  and used to collect maximum amount of caps for effect instantiation
			 *  (for example, basic callback will add normal map cap if material defines normal texture)
			 *
			 *  @param caps The caps container
			 *  @param pMaterial Material which effect is associated with
			 *  @param pEffect Effect that will be instantiated */
			virtual void FillInstanceCaps(SEffectCaps& caps, IMaterial* pMaterial, IEffect* pEffect) = 0;

			/// Returns the next callback in the chain
			virtual IMaterialCallback* getNextCallback() const = 0;

			/// Chains callback after this one
			virtual void setNextCallback(IMaterialCallback* next) = 0;
		};

	} // namespace
} // namespace

#endif	// _IMATERIALCALLBACK_H__