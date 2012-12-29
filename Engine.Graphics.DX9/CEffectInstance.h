/*========================================================
* CEffectInstance.h
* @author Sergey Mikhtonyuk
* @date 27 August 2009
=========================================================*/
#ifndef _CEFFECTINSTANCE_H__
#define _CEFFECTINSTANCE_H__

#include "../Engine.Graphics/Interfaces/IEffectInstance.h"
#include "../Engine.Graphics/Interfaces/EffectTypes.h"
#include "DirectX.h"
#include "../Core.COM/Implementations.h"
#include <vector>

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	/// Used to associate parameters types with ones in the shader
	/** @ingroup DX9 */
	struct ShaderParam
	{
		EEffectParam	type;
		D3DXHANDLE		handle;

		ShaderParam(EEffectParam t, D3DXHANDLE h) : type(t), handle(h) {}
	};
	//////////////////////////////////////////////////////////////////////////



	/// Implementation of effect instance
	/** @ingroup DX9 */
	class NOVTABLE CEffectInstance : 
		public Core::SCOM::ComRootObject<>,
		public IEffectInstance
	{
	public:
		DECLARE_IMPLEMENTATION(CEffectInstance)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IEffectInstance)
		END_INTERFACE_MAP()

		CEffectInstance();
		~CEffectInstance();
		void					FinalConstruct(IEffect* effect, const SEffectCaps& caps);
		IEffect*				GetSrcEffect() const;
		const SEffectCaps*		GetInstanceCaps() const;
		const SEffectParams*	GetInstanceParameters() const;
		void					UpdateParameters();
		unsigned int			BeginSequence();
		void					EndSequence();
		void					BeginPass(unsigned int pass);
		void					EndPass();

		void					FillMacros(D3DXMACRO* macros) const;
		void					FillParameters();
		void					ProcessSemantics();
		D3DXHANDLE				GetParameterBySemantics(const char* annotation, int& start_index);

		void					OnDeviceLost();
		void					OnDeviceReset();

	private:
		SEffectCaps					mCaps;
		SEffectParams				mParams;
		std::vector<ShaderParam>	mParamMap;

		IEffect*					mSrcEffect;
		ID3DXEffect*				mDxEffect;
		D3DXHANDLE					mTechnique;

		// Needed for pixel kernel updates
		int							mPrevRTWidth;
		int							mPrevRTHeight;
	};

} // namespace

#endif // _CEFFECTINSTANCE_H__