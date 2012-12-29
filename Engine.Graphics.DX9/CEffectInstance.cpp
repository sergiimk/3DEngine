/*========================================================
* CEffectInstance.cpp
* @author Sergey Mikhtonyuk
* @date 27 August 2009
=========================================================*/
#include "CEffectInstance.h"
#include "CD3DRenderer.h"
#include "../Engine.Graphics/Interfaces/IEffect.h"
#include "../Engine.Graphics/Interfaces/IMaterialCallback.h"
#include "../Engine.Graphics/Interfaces/IRenderTarget.h"
#include "../Engine.Graphics/RendererExceptions.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "../Core.Logging/ILogger.h"
#include "../Core/CommonPlugin.h"
#include "../Engine.Graphics.Parsers/Common/TypeParsing.h"
#include "../Core.Math/VML.h"
#include "CTexture.h"
#include "managers.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CEffectInstance::CEffectInstance()
		: mSrcEffect(0), mTechnique(0), mDxEffect(0), mPrevRTHeight(0), mPrevRTWidth(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CEffectInstance::~CEffectInstance()
	{
		mDxEffect->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::FinalConstruct(IEffect* effect, const SEffectCaps& caps)
	{
		ASSERT_STRICT(effect->IsLoaded());

		mCaps = caps;
		mSrcEffect = effect;

		std::string effect_path = mSrcEffect->GetURL()->Name;
		effect_path = Core::gEnv->FileSystem->PathGetParentFolder(effect_path.c_str());

		// Set geometry file path
		effect_path = Core::gEnv->FileSystem->PathCombine(effect_path.c_str(), mSrcEffect->GetEffectFileName());


		D3DXMACRO macros[FXC_NUM_CAPS];
		FillMacros(macros);

		HR(
			D3DXCreateEffectFromFileA(
				((CD3DRenderer*)g_Renderer)->GetDevice(), 
				effect_path.c_str(), 
				macros, 
				0,
				D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, 
				0, 
				&mDxEffect, 
				0 )
		);

		/// \todo add techniques to material description files
		mTechnique = mDxEffect->GetTechnique(0);

		// Associate parameters
		FillParameters();

		// Process additional semantics
		ProcessSemantics();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::FillMacros(D3DXMACRO *macros) const
	{
		int i = 0;
		for(SEffectCaps::iterator it = mCaps.begin(); it != mCaps.end(); ++it)
		{
			if(it->state)
			{
				macros[i].Name = EEffectCap_ToString(it->cap);
				macros[i].Definition = 0;
				++i;
			}
		}

		macros[i].Name = 0;
		macros[i].Definition = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::FillParameters()
	{
		const SEffectDesc* desc = mSrcEffect->GetEffectDescription(); 
		SEffectParams gathered = *desc->getGlobalParameters();
		
		/// Gather all parameters
		for(SEffectCaps::iterator it = mCaps.begin(); it != mCaps.end(); ++it)
		{
			if(it->state && desc->getCapSupport(it->cap))
			{
				const SEffectParams* scoped = desc->getScopedParameters(it->cap);
				gathered.add(*scoped);
			}
		}

		for(SEffectParams::iterator it = gathered.begin(); it != gathered.end(); ++it)
		{
			if(it->state)
			{
				// Search for parameter by name and semantics
				D3DXHANDLE hParam = mDxEffect->GetParameterByName(0, EEffectParam_ToString(it->param));
				
				if(!hParam)
					hParam = mDxEffect->GetParameterBySemantic(0, EEffectParam_ToString(it->param));

				if(!hParam)
				{
					ASSERT_SOFT(false);
					LogErrorAlways("Failed to bind parameter %s in effect %s", 
						EEffectParam_ToString(it->param),
						mSrcEffect->GetEffectFileName());
					throw ResourceException("Effect parameter binding failed");
				}

				mParamMap.push_back(ShaderParam(it->param, hParam));
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::ProcessSemantics()
	{
		IRenderTarget* pRT = g_Renderer->GetRenderTarget(0);
		if(!pRT) return;

		int rtHeight = pRT->GetSurfaceParams()->Height;
		int rtWidth = pRT->GetSurfaceParams()->Width;

		// Not changed?
		if(rtWidth == mPrevRTWidth && rtHeight == mPrevRTHeight) return;

		mPrevRTHeight = rtHeight;
		mPrevRTWidth = rtWidth;


		/// \todo optimize
		// If one or more kernel exists, convert kernel from pixel space to texel space

		// First check for kernels. Kernels are identified by having a string annotation of name "PixelsToTexels"
		D3DXHANDLE hParamToConvert;
		int iparam = 0;
		while(hParamToConvert = GetParameterBySemantics("PixelsToTexels", iparam))
		{
			D3DXHANDLE hAnnotSource = mDxEffect->GetAnnotationByName(hParamToConvert, "PixelsToTexels");
			ASSERT_STRICT(hAnnotSource);

			const char* sSource;
			mDxEffect->GetString( hAnnotSource, &sSource );
			D3DXHANDLE hConvertSource = mDxEffect->GetParameterByName( NULL, sSource );

			if( !hConvertSource )
			{
				LogWarningAlways("Specified PixelsToTexels source not found");
				return;
			}

			// Kernel source exists. Proceed. Retrieve the kernel size
			LogTrace("Converting pixel kernel to texel offsets using back buffer size");

			D3DXPARAMETER_DESC desc;
			mDxEffect->GetParameterDesc( hConvertSource, &desc );

			// Each element has 2 floats
			DWORD cKernel = desc.Bytes / ( 2 * sizeof( float ) );
			D3DXVECTOR4* pvKernel = new D3DXVECTOR4[cKernel];

			mDxEffect->GetVectorArray( hConvertSource, pvKernel, cKernel );

			// Convert
			for( DWORD i = 0; i < cKernel; ++i )
			{
				pvKernel[i].x = pvKernel[i].x / rtWidth;
				pvKernel[i].y = pvKernel[i].y / rtHeight;
			}
			// Copy back
			mDxEffect->SetVectorArray( hParamToConvert, pvKernel, cKernel );

			delete[] pvKernel;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	D3DXHANDLE CEffectInstance::GetParameterBySemantics(const char* annotation, int& start_index)
	{
		D3DXHANDLE hParam = 0;
		while( NULL != ( hParam = mDxEffect->GetParameter( 0, start_index++ ) ) )
			if( NULL != ( mDxEffect->GetAnnotationByName( hParam, annotation ) ) )
				break;
		return hParam;
	}

	//////////////////////////////////////////////////////////////////////////

	IEffect* CEffectInstance::GetSrcEffect() const
	{
		return mSrcEffect;
	}

	//////////////////////////////////////////////////////////////////////////

	const SEffectCaps* CEffectInstance::GetInstanceCaps() const
	{
		return &mCaps;
	}

	//////////////////////////////////////////////////////////////////////////

	const SEffectParams* CEffectInstance::GetInstanceParameters() const
	{
		return &mParams;
	}

	//////////////////////////////////////////////////////////////////////////

	unsigned int CEffectInstance::BeginSequence()
	{
		unsigned int passes = 0;
		mDxEffect->SetTechnique(mTechnique);
		mDxEffect->Begin(&passes, 0);
		return passes;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::EndSequence()
	{
		mDxEffect->End();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::BeginPass(unsigned int pass)
	{
		mDxEffect->BeginPass(pass);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::EndPass()
	{
		mDxEffect->EndPass();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::UpdateParameters()
	{
		// Updates kernels if RT size changer
		ProcessSemantics();

		for(size_t i = 0; i != mParamMap.size(); ++i)
		{
			// Update matrix
			if(mParamMap[i].type > FXP_START_MATRIX_TYPES && mParamMap[i].type < FXP_END_MATRIX_TYPES)
			{
				VML::Matrix4 m;
				g_Renderer->GetMaterialCallback()->SupplyMatrix(mParamMap[i].type, m);
				mDxEffect->SetMatrix(mParamMap[i].handle, (D3DXMATRIX*)&m);
			}

			// Update vector
			else if(mParamMap[i].type > FXP_START_VECTOR_TYPES && mParamMap[i].type < FXP_END_VECTOR_TYPES)
			{
				VML::Vector4 v;
				g_Renderer->GetMaterialCallback()->SupplyVector(mParamMap[i].type, v);
				mDxEffect->SetVector(mParamMap[i].handle, (D3DXVECTOR4*)&v);
			}

			// Update color
			else if(mParamMap[i].type > FXP_START_COLOR_TYPES && mParamMap[i].type < FXP_END_COLOR_TYPES)
			{
				VML::Vector4 v;
				g_Renderer->GetMaterialCallback()->SupplyColor(mParamMap[i].type, v);
				mDxEffect->SetVector(mParamMap[i].handle, (D3DXVECTOR4*)&v);
			}

			// Update texture
			else if(mParamMap[i].type > FXP_START_TEXTURE_TYPES && mParamMap[i].type < FXP_END_TEXTURE_TYPES)
			{
				ITexture* tex;
				g_Renderer->GetMaterialCallback()->SupplyTexture(mParamMap[i].type, &tex);
				mDxEffect->SetTexture(mParamMap[i].handle, ((CTexture*)tex)->GetTexture());
			}

			// Update float
			else if(mParamMap[i].type > FXP_START_FLOAT_TYPES && mParamMap[i].type < FXP_END_FLOAT_TYPES)
			{
				float v;
				g_Renderer->GetMaterialCallback()->SupplyFloat(mParamMap[i].type, v);
				mDxEffect->SetFloat(mParamMap[i].handle, v);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::OnDeviceLost()
	{
		mDxEffect->OnLostDevice();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEffectInstance::OnDeviceReset()
	{
		mDxEffect->OnResetDevice();
		mPrevRTHeight = mPrevRTWidth = 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace