/*========================================================
* SpatialCallback.h
* @author Sergey Mikhtonyuk
* @date 17 May 2009
=========================================================*/
#ifndef _SPATIALCALLBACK_H__
#define _SPATIALCALLBACK_H__

#include "../Engine.Graphics/Interfaces/IMaterialCallback.h"
#include "../Engine/Engine.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"

using namespace Engine;
using namespace Graphics;

class NOVTABLE SpatialCallback : 
	public Core::SCOM::ComRootObject<>,
	public IMaterialCallback
{
	friend class CTestGame;
public:
	DECLARE_IMPLEMENTATION(SpatialCallback)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(IMaterialCallback)
	END_INTERFACE_MAP()

	void SupplyMatrix(EEffectParam param_type, VML::Matrix4& m_out);
	void SupplyVector(EEffectParam param_type, VML::Vector4& v_out);
	void SupplyColor(EEffectParam param_type, VML::Vector4& clr_out);
	void SupplyTexture(EEffectParam param_type, ITexture** ppTexture);
	void SupplyFloat(EEffectParam param_type, float& f_out);
	void FillInstanceCaps(SEffectCaps& caps, IMaterial* pMaterial, IEffect* pEffect);

	IMaterialCallback* getNextCallback() const;
	void setNextCallback(IMaterialCallback* next);

private:
	IEntity*								mCamera;
	Core::SCOM::ComPtr<IMaterialCallback>	mNextCallback;
};

#endif	// _SPATIALCALLBACK_H__