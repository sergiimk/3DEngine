/*========================================================
* SpatialCallback.cpp
* @author Sergey Mikhtonyuk
* @date 17 May 2009
=========================================================*/
#include "SpatialCallback.h"

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::SupplyMatrix(EEffectParam param_type, VML::Matrix4& m_out)
{
	assert(param_type > FXP_START_MATRIX_TYPES && param_type < FXP_END_MATRIX_TYPES);

	//switch(param_type)
	//{
	//default:
	if(mNextCallback)
		mNextCallback->SupplyMatrix(param_type, m_out);
	else
		assert(false);
	//};
}

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::SupplyVector(EEffectParam param_type, VML::Vector4& v_out)
{
	assert(param_type > FXP_START_VECTOR_TYPES && param_type < FXP_END_VECTOR_TYPES);

	switch(param_type)
	{
	case FXP_VECTOR_CAMERA_POSITION:
		v_out.setXYZ(((ICmpSpatialNode*)mGame->mCamera->getComponent(UUIDOF(ICmpSpatialNode)))->getPosition());
		v_out.setW(0);
		break;
	case FXP_VECTOR_CAMERA_DIRECTION:
		v_out = VML::Vector4(mGame->mRenderTraverser.to, 0);
		break;
	case FXP_VECTOR_CAMERA_UP:
		v_out = VML::Vector4(mGame->mRenderTraverser.up, 0);
		break;
	case FXP_VECTOR_DIRACTIONAL_LIGHT_SOURCE:
		v_out = VML::Vector4(1, 1.0f, -1.0f, 0);
		v_out.normalize();
		break;
	default:
		if(mNextCallback)
			mNextCallback->SupplyVector(param_type, v_out);
		else
			assert(false);
	};
}

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::SupplyColor(EEffectParam param_type, VML::Vector4& clr_out)
{
	assert(param_type > FXP_START_COLOR_TYPES && param_type < FXP_END_COLOR_TYPES);

	switch(param_type)
	{
	case FXP_COLOR_AMBIENT_LIGHT:
		clr_out = VML::Vector4(0.05f, 0.05f, 0.01f, 1.0f);
		break;
	case FXP_COLOR_DIRECTIONAL_LIGHT:
		clr_out = VML::Vector4(1.0f, 0.9f, 0.85f, 1.0f);
		break;
	default:
		if(mNextCallback)
			mNextCallback->SupplyColor(param_type, clr_out);
		else
			assert(false);
	};
}

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::SupplyTexture(EEffectParam param_type, ITexture** ppTexture)
{
	assert(param_type > FXP_START_TEXTURE_TYPES && param_type < FXP_END_TEXTURE_TYPES);

	switch(param_type)
	{
	case FXP_TEXTURE_LIGHT_ACC:
		*ppTexture = mGame->acc_lighting;
		break;
	default:
		if(mNextCallback)
			mNextCallback->SupplyTexture(param_type, ppTexture);
		else
			assert(false);
	};
}

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::SupplyFloat(EEffectParam param_type, float& f_out)
{
	assert(param_type > FXP_START_FLOAT_TYPES && param_type < FXP_END_FLOAT_TYPES);

	switch(param_type)
	{
	case FXP_FLOAT_Z_NEAR:
		f_out = mGame->mRenderTraverser.zNear;
		break;
	case FXP_FLOAT_Z_FAR:
		f_out = mGame->mRenderTraverser.zFar;
		break;
	case FXP_FLOAT_FOV:
		f_out = mGame->mRenderTraverser.fov;
		break;
	case FXP_FLOAT_ASPECT_RATIO:
		f_out = mGame->mRenderTraverser.aspect;
		break;
	default:
		if(mNextCallback)
			mNextCallback->SupplyFloat(param_type, f_out);
		else
			assert(false);
	};
}

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::FillInstanceCaps(SEffectCaps& caps, IMaterial* pMaterial, IEffect* pEffect)
{
	caps.setSupportState(FXC_AMBIENT_LIGHT, true);
	caps.setSupportState(FXC_DIRECTIONAL_LIGHT, true);

	// Call next
	if(mNextCallback)
		mNextCallback->FillInstanceCaps(caps, pMaterial, pEffect);
}

//////////////////////////////////////////////////////////////////////////

IMaterialCallback* SpatialCallback::getNextCallback() const
{
	return mNextCallback;
}

//////////////////////////////////////////////////////////////////////////

void SpatialCallback::setNextCallback(IMaterialCallback* next)
{
	mNextCallback = next;
}

//////////////////////////////////////////////////////////////////////////