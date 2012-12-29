/*========================================================
* CommonProcMeshCallbacks.cpp
* @author Sergey Mikhtonyuk
* @date 21 May 2009
=========================================================*/
#include "CommonProcMeshCallbacks.h"
#include "../../Core.Math/VML.h"
#include "../Interfaces/IMesh.h"
#include "../Interfaces/IBuffer.h"
#include "../../Core.Math/VML.h"

namespace Engine
{
	namespace Graphics
	{

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		void CBoxCallback::FinalConstruct(const VML::Vector3& a, const VML::Vector3& b)
		{ 
			mA[0] = a.getX(); mA[1] = a.getY(); mA[2] = a.getZ();
			mB[0] = b.getX(); mB[1] = b.getY(); mB[2] = b.getZ();
		}

		//////////////////////////////////////////////////////////////////////////

		void CBoxCallback::FillMeshData(Engine::Graphics::IMesh *pMesh)
		{
			// Declaration
			SVertexElement elems[4];
			elems[0] = SVertexElement(0, ETYPE_FLOAT3, USG_POSITION, 0);
			elems[1] = SVertexElement(sizeof(float) * 3, ETYPE_FLOAT3, USG_NORMAL, 0);
			elems[2] = SVertexElement(sizeof(float) * 6, ETYPE_FLOAT2, USG_TEXCOORD, 0);
			elems[3] = END_DECLARATION();
			pMesh->SetVertexDeclaration(elems);
			pMesh->setPrimitiveType(PT_INDEXED_TRIANGLE_LIST);

			// Data
			const int n_verts = 36;
			struct Vert { float data[8]; };
			Vert v[] =
			{
				{ mA[0],  mB[1], mA[2], 0, 1, 0 ,  0, 1 },
				{ mA[0],  mB[1], mB[2], 0, 1, 0 ,  0, 0 },
				{ mB[0],  mB[1], mB[2], 0, 1, 0 ,  1, 0 },

				{ mB[0],  mB[1], mB[2], 0, 1, 0 ,  1, 0 },
				{ mB[0],  mB[1], mA[2], 0, 1, 0 ,  1, 1 },
				{ mA[0],  mB[1], mA[2], 0, 1, 0 ,  0, 1 },

				{ mA[0],  mA[1], mA[2], 0, 0, -1 ,  0, 1 },
				{ mA[0],  mB[1], mA[2], 0, 0, -1 ,  0, 0 },
				{ mB[0],  mB[1], mA[2], 0, 0, -1 ,  1, 0 },

				{ mB[0],  mB[1], mA[2], 0, 0, -1 ,  1, 0 },
				{ mB[0],  mA[1], mA[2], 0, 0, -1 ,  1, 1 },
				{ mA[0],  mA[1], mA[2], 0, 0, -1 ,  0, 1 },

				{ mA[0],  mA[1], mB[2], -1, 0, 0 ,  0, 1 },
				{ mA[0],  mB[1], mB[2], -1, 0, 0 ,  0, 0 },
				{ mA[0],  mB[1], mA[2], -1, 0, 0 ,  1, 0 },

				{ mA[0],  mB[1], mA[2], -1, 0, 0 ,  1, 0 },
				{ mA[0],  mA[1], mA[2], -1, 0, 0 ,  1, 1 },
				{ mA[0],  mA[1], mB[2], -1, 0, 0 ,  0, 1 },

				{ mA[0],  mB[1], mB[2], 0, 0, 1 ,  1, 0 },
				{ mA[0],  mA[1], mB[2], 0, 0, 1 ,  1, 1 },
				{ mB[0],  mA[1], mB[2], 0, 0, 1 ,  0, 1 },

				{ mB[0],  mA[1], mB[2], 0, 0, 1 ,  0, 1 },
				{ mB[0],  mB[1], mB[2], 0, 0, 1 ,  0, 0 },
				{ mA[0],  mB[1], mB[2], 0, 0, 1 ,  1, 0 },

				{ mB[0],  mA[1], mA[2], 1, 0, 0 ,  0, 1 },
				{ mB[0],  mB[1], mA[2], 1, 0, 0 ,  0, 0 },
				{ mB[0],  mB[1], mB[2], 1, 0, 0 ,  1, 0 },

				{ mB[0],  mB[1], mB[2], 1, 0, 0 ,  1, 0 },
				{ mB[0],  mA[1], mB[2], 1, 0, 0 ,  1, 1 },
				{ mB[0],  mA[1], mA[2], 1, 0, 0 ,  0, 1 },

				{ mA[0],  mA[1], mB[2], 0, -1, 0 ,  0, 1 },
				{ mA[0],  mA[1], mA[2], 0, -1, 0 ,  0, 0 },
				{ mB[0],  mA[1], mA[2], 0, -1, 0 ,  1, 0 },

				{ mB[0],  mA[1], mA[2], 0, -1, 0 ,  1, 0 },
				{ mB[0],  mA[1], mB[2], 0, -1, 0 ,  1, 1 },
				{ mA[0],  mA[1], mB[2], 0, -1, 0 ,  0, 1 },
			};

			int i[] = {	
				0,1,2, 3,4,5, 6,7,8, 9,10,11,
				12,13,14, 15,16,17, 18,19,20, 21,22,23,
				24,25,26, 27,28,29, 30,31,32, 33,34,35, };

			IBuffer *vb = pMesh->GetVertexBuffer();
			vb->Resize(sizeof(Vert) * n_verts);
			void *pData;
			vb->Lock(&pData, LOCK_DISCARD);
			memcpy(pData, v, sizeof(Vert) * n_verts);
			vb->Unlock();

			IBuffer *ib = pMesh->GetIndexBuffer();
			ib->Resize(sizeof(int) * n_verts);
			ib->Lock(&pData, LOCK_DISCARD);
			memcpy(pData, i, sizeof(int) * n_verts);
			ib->Unlock();

			// Subset
			IGeometry::TInterval vi(0, n_verts);
			IGeometry::TInterval ii(0, n_verts);
			pMesh->AddSubset(vi, ii);

			VML::Vector3 vmin(mA[0], mA[1], mA[2]);
			VML::Vector3 vmax(mB[0], mB[1], mB[2]);
			SBoundingVolume bv(vmin, vmax);
			pMesh->SetBoundingVolume(bv);
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		void CSphereCallback::FinalConstruct(int rings, int segments, float r)
		{
			mRings = rings; mSegments = segments; mRadius = r;
		}

		//////////////////////////////////////////////////////////////////////////

		void CSphereCallback::FillMeshData(Engine::Graphics::IMesh *pMesh)
		{
			// Declaration
			SVertexElement elems[4];
			elems[0] = SVertexElement(0, ETYPE_FLOAT3, USG_POSITION, 0);
			elems[1] = SVertexElement(sizeof(float) * 3, ETYPE_FLOAT3, USG_NORMAL, 0);
			elems[2] = SVertexElement(sizeof(float) * 6, ETYPE_FLOAT2, USG_TEXCOORD, 0);
			elems[3] = END_DECLARATION();
			pMesh->SetVertexDeclaration(elems);
			pMesh->setPrimitiveType(PT_INDEXED_TRIANGLE_LIST);

			// Data
			const int n_verts = (mRings + 1) * (mSegments + 1);
			const int n_indcs = 6 * mRings * (mSegments + 1);
			void *vertices, *indices;
			
			IBuffer* vb = pMesh->GetVertexBuffer();
			IBuffer* ib = pMesh->GetIndexBuffer();

			vb->Resize(n_verts * sizeof(float) * 8);
			ib->Resize(n_indcs * sizeof(int));

			vb->Lock(&vertices, LOCK_DISCARD);
			ib->Lock(&indices, LOCK_DISCARD);

			const float PI = 3.1415926f;
			float fDeltaRingAngle = (PI / mRings);
			float fDeltaSegAngle = (2.0f * PI / mSegments);
			unsigned short wVerticeIndex = 0 ;

			float* pVertex = (float*)vertices;
			int* pIndices = (int*)indices;

			// Generate the group of rings for the sphere
			for(int ring = 0; ring <= mRings; ring++)
			{
				float r0 = mRadius * sinf (ring * fDeltaRingAngle);
				float y0 = mRadius * cosf (ring * fDeltaRingAngle);

				// Generate the group of segments for the current ring
				for(int seg = 0; seg <= mSegments; seg++)
				{
					float x0 = r0 * sinf(seg * fDeltaSegAngle);
					float z0 = r0 * cosf(seg * fDeltaSegAngle);

					// Position
					*pVertex++ = x0;
					*pVertex++ = y0;
					*pVertex++ = z0;

					// Normal
					VML::Vector3 vNormal(x0, y0, z0);
					vNormal.normalize();

					*pVertex++ = vNormal.getX();
					*pVertex++ = vNormal.getY();
					*pVertex++ = vNormal.getZ();

					// Texture coordinates
					*pVertex++ = 1.0f - (float) seg / (float) mSegments;
					*pVertex++ = (float) ring / (float) mRings;

					if (ring != mRings) 
					{
						// each vertex (except the last) has six indices pointing to it
						*pIndices++ = wVerticeIndex + mSegments + 1;
						*pIndices++ = wVerticeIndex;               
						*pIndices++ = wVerticeIndex + mSegments;
						*pIndices++ = wVerticeIndex + mSegments + 1;
						*pIndices++ = wVerticeIndex + 1;
						*pIndices++ = wVerticeIndex;
						wVerticeIndex ++;
					}
				} // end for seg
			} // end for ring


			vb->Unlock();
			ib->Unlock();

			// Subset
			IGeometry::TInterval vi(0, n_verts);
			IGeometry::TInterval ii(0, n_indcs);
			pMesh->AddSubset(vi, ii);

			SBoundingVolume bv(VML::Vector3(0), mRadius);
			pMesh->SetBoundingVolume(bv);
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		void CPlaneCallback::FinalConstruct(float x, float y)
		{
			m_x = x;
			m_y = y;
		}

		//////////////////////////////////////////////////////////////////////////

		void CPlaneCallback::FillMeshData(Engine::Graphics::IMesh *pMesh)
		{
			// Declaration
			SVertexElement elems[4];
			elems[0] = SVertexElement(0, ETYPE_FLOAT3, USG_POSITION, 0);
			elems[1] = SVertexElement(sizeof(float) * 3, ETYPE_FLOAT3, USG_NORMAL, 0);
			elems[2] = SVertexElement(sizeof(float) * 6, ETYPE_FLOAT2, USG_TEXCOORD, 0);
			elems[3] = END_DECLARATION();
			pMesh->SetVertexDeclaration(elems);
			pMesh->setPrimitiveType(PT_TRIANGLE_STRIP);

			float x = m_x * 0.5f;
			float y = m_y * 0.5f;

			// Data
			const int n_verts = 4;
			struct Vert { float data[8]; };
			Vert v[] =
			{
				{ -x,  0,  y, 0, 1, 0,  0, 0 },
				{  x,  0,  y, 0, 1, 0,  1, 0 },
				{ -x,  0, -y, 0, 1, 0,  0, 1 },
				{  x,  0, -y, 0, 1, 0,  1, 1 },
			};

			IBuffer *vb = pMesh->GetVertexBuffer();
			vb->Resize(sizeof(Vert) * n_verts);
			void *pData;
			vb->Lock(&pData, LOCK_DISCARD);
			memcpy(pData, v, sizeof(Vert) * n_verts);
			vb->Unlock();

			// Subset
			IGeometry::TInterval vi(0, n_verts);
			IGeometry::TInterval ii(0, 0);
			pMesh->AddSubset(vi, ii);

			SBoundingVolume bv(VML::Vector3(-x, 0, -y), VML::Vector3(x, 0.001f, y));
			pMesh->SetBoundingVolume(bv);
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace