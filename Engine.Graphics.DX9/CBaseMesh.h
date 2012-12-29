/*========================================================
* CBaseMesh.h
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#ifndef _CBASEMESH_H__
#define _CBASEMESH_H__

#include "CBaseResource.h"
#include "../Engine.Graphics/Interfaces/IMesh.h"
#include "../Core.COM/Implementations.h"
#include "DirectX.h"
#include "managers.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include <string>
#include <vector>

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Engine::Graphics;
	class CGeometry;
	//////////////////////////////////////////////////////////////////////////

	class NOVTABLE CBaseMesh : public CBaseResource<IMesh>
	{
		friend class CGeometry;

	public:

		//////////////////////////////////////////////////////////////////////////

		CBaseMesh();
		~CBaseMesh();

		//////////////////////////////////////////////////////////////////////////

		size_t							GetSubsetCount() const;
		IGeometry*						GetSubset(int index) const;
		void							ClearSubsets();
		IGeometry*						AddSubset(	const IGeometry::TInterval& vert,
													const IGeometry::TInterval& indx);

		size_t							GetVertexCount() const;
		size_t							GetIndexCount() const;
		size_t							GetPrimitiveCount() const;
		size_t							GetVertexSize() const;
		size_t							GetIndexSize() const;
		void							GetVertexDeclaration(SVertexElement* elems) const;
		void							SetVertexDeclaration(const SVertexElement* elems);

		IBuffer*						GetVertexBuffer() const;
		IBuffer*						GetIndexBuffer() const;

		const Engine::SBoundingVolume&	GetBoundingVolume() const;
		void							SetBoundingVolume(const Engine::SBoundingVolume& bv);
		void							UpdateBoundingVolume();
		IGeometryManager*				GetManager() { return g_GeometryManager; }

		//////////////////////////////////////////////////////////////////////////

		IDirect3DVertexDeclaration9*	GetDeclaration() const;
		void							BuildBoundingBox(void* locked, size_t posOffset);

		//////////////////////////////////////////////////////////////////////////

	protected:
		Engine::SBoundingVolume			mBoundingVol;	// should be aligned!
		std::vector<CGeometry*>			mGeometry;

		size_t							mVertexSize;
		size_t							mIndexSize;

		IDirect3DVertexDeclaration9*	mDeclaration;
		CVertexBuffer					mVertexBuffer;
		CIndexBuffer					mIndexBuffer;	
	};

} // namespace

#endif	// _CBASEMESH_H__
