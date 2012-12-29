#ifndef _TEXT_CALLBACK_H__
#define _TEXT_CALLBACK_H__

class NOVTABLE CTextCallback: 
	public Core::SCOM::ComRootObject<>,
	public IProceduralMeshCallback
{

	DECLARE_IMPLEMENTATION(CTextCallback)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(IProceduralMeshCallback)
	END_INTERFACE_MAP()

	void FillMeshData(IMesh* pMesh)
	{
		// Declaration
		SVertexElement elems[4];
		elems[0] = SVertexElement(0, ETYPE_FLOAT3, USG_POSITION, 0);
		elems[1] = SVertexElement(sizeof(float) * 3, ETYPE_FLOAT3, USG_NORMAL, 0);
		elems[2] = SVertexElement(sizeof(float) * 6, ETYPE_FLOAT2, USG_TEXCOORD, 0);
		elems[3] = END_DECLARATION();
		pMesh->SetVertexDeclaration(elems);
		pMesh->setPrimitiveType(PT_TRIANGLE_LIST);

		float x = 1.0f;
		float y = 2.0f;

		// Data
		const int n_verts = 6;
		struct Vert { float data[8]; };
		Vert v[] =
		{
			{ -x,  y,  0, 0, 1, 0,  0.21f, 0 },
			{  x,  y,  0, 0, 1, 0,  0.22f, 0 },
			{ -x, -y,  0, 0, 1, 0,  0.21f, 1 },

			{  x,  y,  0, 0, 1, 0,  0.22f, 0 },
			{  x, -y,  0, 0, 1, 0,  0.22f, 1 },
			{ -x, -y,  0, 0, 1, 0,  0.21f, 1 },
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

		SBoundingVolume bv(VML::Vector3(-x, -y, 0), VML::Vector3(x, y, 0.001f));
		pMesh->SetBoundingVolume(bv);
	}
};

#endif