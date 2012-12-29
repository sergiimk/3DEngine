/*========================================================
* CGeometry.cpp
* @author Sergey Mikhtonyuk
* @date 09 May 2009
=========================================================*/
#include "CGeometry.h"
#include "CBaseMesh.h"
#include "../Engine.Graphics/Interfaces/IMaterial.h"
#include "../Engine.Graphics/Interfaces/IMaterialManager.h"
#include "managers.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CGeometry::CGeometry() : mIsInitialized(false)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometry::FinishInit()
	{
		if(!mMaterial) g_MaterialManager->GetDefaultMaterial(mMaterial.wrapped());
		if(mMaterial) mMaterial->AddUser();
		mIsInitialized = true;
	}

	//////////////////////////////////////////////////////////////////////////

	CGeometry::~CGeometry()
	{
		if(mMaterial && mIsInitialized) mMaterial->RemoveUser();
	}

	//////////////////////////////////////////////////////////////////////////

	IMesh* CGeometry::GetMesh() const
	{
		return mMesh;
	}

	//////////////////////////////////////////////////////////////////////////

	IMaterial* CGeometry::GetMaterial() const
	{
		return mMaterial;
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometry::SetMaterial(IMaterial* mat)
	{
		if(mMaterial && mIsInitialized) mMaterial->RemoveUser();
		mMaterial = mat;
		if(mMaterial && mIsInitialized) mMaterial->AddUser();
	}

	//////////////////////////////////////////////////////////////////////////

	const IGeometry::TInterval& CGeometry::GetIndexInterval() const
	{
		return mIndexInterval;
	}

	//////////////////////////////////////////////////////////////////////////

	const IGeometry::TInterval& CGeometry::GetVertexInterval() const
	{
		return mVertexInterval;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace