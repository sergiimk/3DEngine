/*========================================================
* CProceduralMesh.cpp
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#include "CProceduralMesh.h"
#include "CGeometry.h"
#include "CD3DRenderer.h"
#include "TypeUtilities.h"
#include "../Engine.Graphics/Interfaces/IMaterialManager.h"
#include "../Engine.Graphics/RendererExceptions.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CProceduralMesh::CProceduralMesh() : mPrimType(PT_INDEXED_TRIANGLE_LIST)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CProceduralMesh::FinalConstruct(IProceduralMeshCallback* callback)
	{
		mProcCallback = callback;
	}

	//////////////////////////////////////////////////////////////////////////

	CProceduralMesh::~CProceduralMesh()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CProceduralMesh::Load()
	{
		mProcCallback->FillMeshData(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CProceduralMesh::Unload()
	{
		for(size_t i = 0; i != mGeometry.size(); ++i)
			mGeometry[i]->Release();

		mGeometry.clear();

		mVertexBuffer.ReleaseBuffer();
		mIndexBuffer.ReleaseBuffer();
		if(mDeclaration) mDeclaration->Release();
		mDeclaration = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CProceduralMesh::OnDeviceLost() 
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CProceduralMesh::OnDeviceReset() 
	{
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace