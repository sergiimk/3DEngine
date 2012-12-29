/*========================================================
* CBaseMesh.cpp
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#include "CBaseMesh.h"
#include "CGeometry.h"
#include "TypeUtilities.h"
#include "../Core/CommonPlugin.h"
#include "../Core.Logging/ILogger.h"
#include "CD3DRenderer.h"
#include "managers.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CBaseMesh::CBaseMesh()
		:	mDeclaration(0), mVertexSize(0), mIndexSize(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CBaseMesh::~CBaseMesh()
	{
		ASSERT_SOFT(!IsLoaded());
		if(mRefs)
			LogErrorAlways("[Memory leak] Mesh %s still was loaded on release, missing RemoveUser call", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBaseMesh::GetVertexCount() const
	{
		ASSERT_STRICT(IsLoaded());
		size_t num = 0;
		for(size_t i = 0; i != mGeometry.size(); ++i)
			num += mGeometry[i]->GetVertexInterval().second;
		return num;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBaseMesh::GetIndexCount() const
	{
		ASSERT_STRICT(IsLoaded());
		size_t num = 0;
		for(size_t i = 0; i != mGeometry.size(); ++i)
			num += mGeometry[i]->GetIndexInterval().second;
		return num;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBaseMesh::GetPrimitiveCount() const
	{
		ASSERT_STRICT(IsLoaded());
		return GetIndexCount() / 3;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBaseMesh::GetSubsetCount() const
	{
		ASSERT_STRICT(IsLoaded());
		return mGeometry.size();
	}

	//////////////////////////////////////////////////////////////////////////

	IGeometry* CBaseMesh::GetSubset(int index) const
	{
		ASSERT_STRICT(IsLoaded());
		return mGeometry[index];
	}

	//////////////////////////////////////////////////////////////////////////

	void CBaseMesh::ClearSubsets()
	{
		ASSERT_STRICT(IsLoaded());
		for(size_t i = 0; i != mGeometry.size(); ++i)
			mGeometry[i]->Release();

		mGeometry.clear();
	}

	//////////////////////////////////////////////////////////////////////////

	IGeometry* CBaseMesh::AddSubset(const IGeometry::TInterval &vert, const IGeometry::TInterval &indx)
	{
		ASSERT_STRICT(IsLoaded());
		CGeometry *geom;
		scom_new<CGeometry>(&geom);
		geom->mMesh = this;
		geom->mVertexInterval = vert;
		geom->mIndexInterval = indx;
		geom->FinishInit();
		mGeometry.push_back(geom);
		return geom;
	}

	//////////////////////////////////////////////////////////////////////////

	const Engine::SBoundingVolume& CBaseMesh::GetBoundingVolume() const
	{
		ASSERT_STRICT(IsLoaded());
		return mBoundingVol;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBaseMesh::GetVertexSize() const
	{
		ASSERT_STRICT(IsLoaded());
		return mVertexSize;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CBaseMesh::GetIndexSize() const
	{
		ASSERT_STRICT(IsLoaded());
		return mIndexSize;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBaseMesh::GetVertexDeclaration(SVertexElement* elems) const
	{
		ASSERT_STRICT(IsLoaded());
		D3DVERTEXELEMENT9 declelems[MAX_VERTEX_ELEMENTS];
		unsigned int nElems;
		mDeclaration->GetDeclaration(declelems, &nElems);
		ASSERT_STRICT(nElems <= MAX_VERTEX_ELEMENTS);

		for(int i = 0; i != MAX_VERTEX_ELEMENTS; ++i)
		{
			elems[i] = FromDXFormat(declelems[i]);
			if(declelems[i].Stream == 0xFF) break;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CBaseMesh::SetVertexDeclaration(const SVertexElement* elems)
	{
		ASSERT_STRICT(IsLoaded());
		D3DVERTEXELEMENT9 declelems[MAX_VERTEX_ELEMENTS];
		for(int i = 0; i != MAX_VERTEX_ELEMENTS; ++i)
		{
			declelems[i] = ToDXFormat(elems[i]);
			if(elems[i].Offset == 0xffff) break; 
		}

		if(mDeclaration) mDeclaration->Release();
		LPDIRECT3DDEVICE9 device = ((CD3DRenderer*)g_Renderer)->GetDevice();
		HR(device->CreateVertexDeclaration(declelems, &mDeclaration));

		mVertexSize = VertexSizeFromDecl(elems);
	}

	//////////////////////////////////////////////////////////////////////////

	IDirect3DVertexDeclaration9* CBaseMesh::GetDeclaration() const
	{
		ASSERT_STRICT(IsLoaded() && mDeclaration);
		return mDeclaration;
	}

	//////////////////////////////////////////////////////////////////////////

	IBuffer* CBaseMesh::GetVertexBuffer() const
	{
		ASSERT_STRICT(IsLoaded());
		return (IBuffer*)&mVertexBuffer;
	}

	//////////////////////////////////////////////////////////////////////////

	IBuffer* CBaseMesh::GetIndexBuffer() const
	{
		ASSERT_STRICT(IsLoaded());
		return (IBuffer*)&mIndexBuffer;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBaseMesh::SetBoundingVolume(const Engine::SBoundingVolume& bv)
	{
		mBoundingVol = bv;
	}

	//////////////////////////////////////////////////////////////////////////

	void CBaseMesh::UpdateBoundingVolume()
	{
		ASSERT_STRICT(IsLoaded());

		mBoundingVol.Reset();

		D3DVERTEXELEMENT9 declelems[MAX_VERTEX_ELEMENTS];
		unsigned int nElems;
		mDeclaration->GetDeclaration(declelems, &nElems);

		int i = 0;
		while(declelems[i].Usage != D3DDECLUSAGE_POSITION)
		{
			if(declelems[i].Stream = 0xff) break;
			++i;
		}
		if(declelems[i].Usage != D3DDECLUSAGE_POSITION) return;

		void *pData;
		mVertexBuffer.Lock(&pData, LOCK_READONLY);

		BuildBoundingBox(pData, declelems[i].Offset);

		mVertexBuffer.Unlock();
	}

	//////////////////////////////////////////////////////////////////////////

	void CBaseMesh::BuildBoundingBox(void* locked, size_t posOffset)
	{
		mBoundingVol.Reset();

		// Lock buffer
		char* pData = (char*)locked;
		
		mBoundingVol.BeginUpdate();

		// Move to initial offset
		pData += posOffset;

		// Iterate through vertices and compute bbox
		size_t c = GetVertexCount();
		while(c)
		{
			D3DXVECTOR3* v = (D3DXVECTOR3*)pData;
			mBoundingVol.Include(VML::Vector3(v->x, v->y, v->z));

			--c;
			pData += mVertexSize;
		}

		// Update bbox and unlock buffer
		mBoundingVol.EndUpdate();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace