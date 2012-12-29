/*========================================================
* CMaterialCallback.cpp
* @author Sergey Mikhtonyuk
* @date 13 May 2009
=========================================================*/
#include "CMaterialCallback.h"
#include "../../Core.Math/VML.h"
#include "../Interfaces/IRenderer.h"
#include "../Interfaces/IRenderTarget.h"
#include "../Interfaces/SSurfaceDesc.h"

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::FinalConstruct(IRenderer *renderer)
		{
			mRenderer = renderer;
		}

		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::SupplyMatrix(EEffectParam param_type, VML::Matrix4& m_out)
		{
			assert(param_type > FXP_START_MATRIX_TYPES && param_type < FXP_END_MATRIX_TYPES);

			switch(param_type)
			{
			case FXP_MATRIX_WORLD: 
				m_out = mRenderer->GetTransform(TRANSFORM_WORLD); 
				break;
			case FXP_MATRIX_VIEW: 
				m_out = mRenderer->GetTransform(TRANSFORM_VIEW); 
				break;
			case FXP_MATRIX_PROJECTION: 
				m_out = mRenderer->GetTransform(TRANSFORM_PROJECTION); 
				break;
			case FXP_MATRIX_WORLD_VIEW_PROJECTION:
				m_out = mRenderer->GetTransform(TRANSFORM_PROJECTION) * 
						mRenderer->GetTransform(TRANSFORM_VIEW) * 
						mRenderer->GetTransform(TRANSFORM_WORLD);
				break;
			case FXP_MATRIX_WORLD_INV:
				m_out = VML::inverse( mRenderer->GetTransform(TRANSFORM_WORLD) );
				break;
			case FXP_MATRIX_VIEW_INV:
				m_out = VML::inverse( mRenderer->GetTransform(TRANSFORM_VIEW) );
				break;
			case FXP_MATRIX_WORLD_INV_TRANSPOSE:
				m_out = VML::transpose( VML::inverse( mRenderer->GetTransform(TRANSFORM_WORLD) ) );
				break;
			case FXP_MATRIX_WORLD_VIEW_INV_TRANSPOSE:
				m_out = VML::transpose( VML::inverse( 
					mRenderer->GetTransform(TRANSFORM_VIEW) *
					mRenderer->GetTransform(TRANSFORM_WORLD) ) );
				break;
			default:
				if(mNextCallback)
					mNextCallback->SupplyMatrix(param_type, m_out);
				else
					assert(false);
			};
		}

		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::SupplyVector(EEffectParam param_type, VML::Vector4& v_out)
		{
			assert(param_type > FXP_START_VECTOR_TYPES && param_type < FXP_END_VECTOR_TYPES);

			// Use material bindings for query first
			const SMaterialBindings* bindings = mRenderer->GetMaterial()->GetBindings();
			const SSurfaceDesc* sd = mRenderer->GetRenderTarget(0)->GetSurfaceParams();

			switch(param_type)
			{
			case FXP_VECTOR_RT_RESOLUTION:
				v_out = VML::Vector4((float)sd->Width, (float)sd->Height, 0, 0);
				break;
			case FXP_VECTOR_RT_RESOLUTION_INV:
				v_out = VML::Vector4(1.0f / (float)sd->Width, 1.0f / (float)sd->Height, 0, 0);
				break;
			default:
				if(bindings->getBindingState(param_type))
					v_out = bindings->getVector4Binding(param_type);
				else if(mNextCallback)
					mNextCallback->SupplyVector(param_type, v_out);
				else
					assert(false);
			};
		}

		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::SupplyColor(EEffectParam param_type, VML::Vector4& clr_out)
		{
			assert(param_type > FXP_START_COLOR_TYPES && param_type < FXP_END_COLOR_TYPES);

			// Use material bindings for query first
			const SMaterialBindings* bindings = mRenderer->GetMaterial()->GetBindings();

			if(bindings->getBindingState(param_type))
				clr_out = bindings->getColorBinding(param_type);
			else if(mNextCallback)
				mNextCallback->SupplyColor(param_type, clr_out);
			else
				assert(false);
		}

		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::SupplyTexture(EEffectParam param_type, ITexture** ppTexture)
		{
			*ppTexture = 0;
			assert(param_type > FXP_START_TEXTURE_TYPES && param_type < FXP_END_TEXTURE_TYPES);

			const SMaterialBindings* bindings = mRenderer->GetMaterial()->GetBindings();

			if(bindings->getBindingState(param_type))
			{
				*ppTexture = bindings->getTextureBinding(param_type);
			}
			else if(mNextCallback)
			{
				mNextCallback->SupplyTexture(param_type, ppTexture);
			}
			else
			{
				assert(false);
			}
		}

		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::SupplyFloat(EEffectParam param_type, float& f_out)
		{
			assert(param_type > FXP_START_FLOAT_TYPES && param_type < FXP_END_FLOAT_TYPES);

			// Use material bindings for query first
			const SMaterialBindings* bindings = mRenderer->GetMaterial()->GetBindings();

			/*switch(param_type)
			{
			default:*/
				if(bindings->getBindingState(param_type))
					f_out = bindings->getFloatBinding(param_type);
				else if(mNextCallback)
					mNextCallback->SupplyFloat(param_type, f_out);
				else
					assert(false);
			//};
		}

		//////////////////////////////////////////////////////////////////////////

		void CMaterialCallback::FillInstanceCaps(SEffectCaps& caps, IMaterial* pMaterial, IEffect* pEffect)
		{
			const SMaterialBindings* bindings = pMaterial->GetBindings();

			if(bindings->getBindingState(FXP_TEXTURE_DIFFUSE))
				caps.setSupportState(FXC_DIFFUSE_MAP, true);

			if(bindings->getBindingState(FXP_TEXTURE_NORMAL))
				caps.setSupportState(FXC_NORMAL_MAP, true);

			if(bindings->getBindingState(FXP_TEXTURE_SHININESS))
				caps.setSupportState(FXC_SHININESS_MAP, true);

			// Call next
			if(mNextCallback)
				mNextCallback->FillInstanceCaps(caps, pMaterial, pEffect);
		}

		//////////////////////////////////////////////////////////////////////////

		IMaterialCallback* CMaterialCallback::getNextCallback() const
		{
			return mNextCallback;
		}

		//////////////////////////////////////////////////////////////////////////
		
		void CMaterialCallback::setNextCallback(IMaterialCallback* next)
		{
			mNextCallback = next;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace