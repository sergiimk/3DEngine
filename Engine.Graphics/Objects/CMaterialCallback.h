/*========================================================
* CMaterialCallback.h
* @author Sergey Mikhtonyuk
* @date 13 May 2009
=========================================================*/
#ifndef _CMATERIALCALLBACK_H__
#define _CMATERIALCALLBACK_H__

#include "../Graphics_fwd.h"
#include "../Interfaces/IMaterialCallback.h"
#include "../../Core.COM/Implementations.h"
#include "../../Core.COM/Intellectual.h"

namespace Engine
{
	namespace Graphics
	{

		/// Default callback implementation, answers only on queries that can be satisfied by renderer
		/** @ingroup Graphics */
		class NOVTABLE CMaterialCallback : 
			public Core::SCOM::ComRootObject<>,
			public IMaterialCallback
		{
		public:
			DECLARE_IMPLEMENTATION(CMaterialCallback)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IMaterialCallback)
			END_INTERFACE_MAP()
		
			void FinalConstruct(IRenderer* renderer);
			void SupplyMatrix(EEffectParam param_type, VML::Matrix4& m_out);
			void SupplyVector(EEffectParam param_type, VML::Vector4& v_out);
			void SupplyColor(EEffectParam param_type, VML::Vector4& clr_out);
			void SupplyTexture(EEffectParam param_type, ITexture** ppTexture);
			void SupplyFloat(EEffectParam param_type, float& f_out);
			void FillInstanceCaps(SEffectCaps& caps, IMaterial* pMaterial, IEffect* pEffect);
			
			IMaterialCallback* getNextCallback() const;
			void setNextCallback(IMaterialCallback* next);

		private:
			IRenderer*								mRenderer;
			Core::SCOM::ComPtr<IMaterialCallback>	mNextCallback;
		};

	} // namespace
} // namespace

#endif	// _CMATERIALCALLBACK_H__