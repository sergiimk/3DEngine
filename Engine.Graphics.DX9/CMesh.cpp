/*========================================================
* CMesh.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "CMesh.h"
#include "CGeometry.h"
#include "CD3DRenderer.h"
#include "CGeometryManager.h"
#include "../Core/CommonPlugin.h"
#include "../Core.Logging/ILogger.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "../Engine.Graphics/Interfaces/ITexture.h"
#include "../Engine.Graphics/Interfaces/IMaterial.h"
#include "../Engine.Graphics/Interfaces/IMaterialManager.h"
#include "../Engine.Graphics/Interfaces/ISurfaceManager.h"
#include "../Engine.Graphics/RendererExceptions.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CMesh::CMesh()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::FinalConstruct(const Utils::URL &url)
	{
		mUrl = url;
		LogTrace("Mesh resource created: %s", mUrl.Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	CMesh::~CMesh()
	{
		if(g_GeometryManager)
			((CGeometryManager*)g_GeometryManager)->CloseResourceHandle(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::Load()
	{
		MeshParser parser;
		if(!parser.Parse(mUrl.Name.c_str(), this))
		{
			LogErrorAlways("Failed to load mesh: %s", mUrl.Name.c_str());
			throw ResourceException("Failed to load mesh");
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::Unload()
	{
		for(size_t i = 0; i != mGeometry.size(); ++i)
			mGeometry[i]->Release();

		mGeometry.clear();

		if(mDeclaration)
		{
			mDeclaration->Release();
			mDeclaration = 0;
		}

		mVertexBuffer.ReleaseBuffer();
		mIndexBuffer.ReleaseBuffer();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::OnDeviceLost()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::OnDeviceReset()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	// Parsing
	//////////////////////////////////////////////////////////////////////////

	void CMesh::OnError(const char* msg)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::OnGeometryFile(const char* file)
	{
		LPDIRECT3DDEVICE9 device = ((CD3DRenderer*)g_Renderer)->GetDevice();

		// Create geometry file name
		std::string geom_path = Core::gEnv->FileSystem->PathGetParentFolder(mUrl.Name.c_str());
		geom_path = Core::gEnv->FileSystem->PathCombine(geom_path.c_str(), "Geometry");
		geom_path = Core::gEnv->FileSystem->PathCombine(geom_path.c_str(), file);

		// Load mesh from file
		ID3DXMesh* mesh;
		HR(D3DXLoadMeshFromXA( geom_path.c_str(), D3DXMESH_MANAGED, device, 0, 0, 0, 0, &mesh ));

		// Optimize by material, so we can split buffer to subsets
		HR(mesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT, 0, 0, 0, 0 ));

		// Read attributes (subsets)
		DWORD nAttributes = 0;
		HR(mesh->GetAttributeTable(0, &nAttributes));
		ASSERT_STRICT(nAttributes > 0);
		D3DXATTRIBUTERANGE* table = new D3DXATTRIBUTERANGE[nAttributes];
		HR(mesh->GetAttributeTable(table, &nAttributes));


		// Create a geometry entries
		for(int i = 0; i != nAttributes; ++i)
		{
			CGeometry* pGeom;
			scom_new<CGeometry>(&pGeom);
			pGeom->mMesh = this;
			mGeometry.push_back(pGeom);
		}

		// Assign intervals to subsets
		for(size_t i = 0; i != nAttributes; ++i)
		{
			std::pair<int, int> ii(table[i].FaceStart * 3, table[i].FaceCount * 3);
			std::pair<int, int> vi(table[i].VertexStart, table[i].VertexCount);

			mGeometry[i]->mIndexInterval = ii;
			mGeometry[i]->mVertexInterval =  vi;
		}

		delete[] table;

		// Get buffers
		IDirect3DVertexBuffer9* vb;
		IDirect3DIndexBuffer9* ib;
		HR(mesh->GetVertexBuffer(&vb));
		HR(mesh->GetIndexBuffer(&ib));

		// Wrap data by internal buffers
		mVertexBuffer.setBuffer(vb);
		mIndexBuffer.setBuffer(ib);
		vb->Release();
		ib->Release();

		// Load vertex declaration
		D3DVERTEXELEMENT9 declelems[MAX_FVF_DECL_SIZE];
		HR(mesh->GetDeclaration(declelems));
		HR(device->CreateVertexDeclaration(declelems, &mDeclaration));

		// Load stats
		mIndexSize = sizeof(int);
		mVertexSize = mesh->GetNumBytesPerVertex();

		// Release mesh
		mesh->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::OnSubsetMaterial(int sid, const char* material)
	{
		ASSERT_STRICT(sid < (int)mGeometry.size());

		IMaterial* pMaterial;
		g_MaterialManager->FindOrLoadMaterial(Utils::URL(material), &pMaterial);
		mGeometry[sid]->SetMaterial(pMaterial);
		pMaterial->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMesh::OnFinished(int nsubsets)
	{
		// Validate
		if(mGeometry.size() != nsubsets)
		{
			ASSERT_STRICT(false);
			LogErrorAlways("Number of subsets in description and geometry file doesn't match");
		}

		// Finalize subsets
		for(size_t i = 0; i != mGeometry.size(); ++i)
			mGeometry[i]->FinishInit();

		// Compute bounding box
		UpdateBoundingVolume();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
