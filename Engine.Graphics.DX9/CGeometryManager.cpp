/*========================================================
* CGeometryManager.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "../Core.Logging/ILogger.h"
#include "CGeometryManager.h"
#include "CMesh.h"
#include "CProceduralMesh.h"
#include "../Core.COM/Intellectual.h"
#include "../Core/CommonPlugin.h"
#include "../Core.FileSystem/IFile.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "../Engine.Graphics/RendererExceptions.h"
#include "../Engine.Graphics/Objects/CommonProcMeshCallbacks.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Core;
	using namespace SCOM;
	using namespace FileSystem;
	//////////////////////////////////////////////////////////////////////////

	CGeometryManager::CGeometryManager()
	{
		LogTrace("Creating mesh manager");
	}

	//////////////////////////////////////////////////////////////////////////

	CGeometryManager::~CGeometryManager()
	{
		LogTrace("Destroying mesh manager");

		ASSERT_SOFT(!mMeshes.size());

		if(!mMeshes.size())
		for(MeshMapCIter it = mMeshes.begin(); it != mMeshes.end(); ++it)
			LogErrorAlways("[Memory leak] Mesh %s was not released before shutdown", it->second->GetURL()->Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::FindOrLoadMesh(const Utils::URL &url, IMesh** outMesh)
	{
		*outMesh = 0;
		// Make full path
		Utils::URL nurl(
			gEnv->FileSystem->PathCombine(
				"../Resources/Meshes", 
				url.Name.c_str()
		));

		// Try find loaded
		MeshMapCIter it = mMeshes.find(nurl.Name);
		if(it != mMeshes.end())
		{
			*outMesh = it->second;
			(*outMesh)->AddRef();
			return;
		}

		// Create mesh from desc file
		CMesh* pm;
		scom_new<CMesh>(&pm);
		pm->FinalConstruct(nurl);
		mMeshes.insert(std::make_pair(nurl.Name, pm));
		*outMesh = pm;
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::CreatePlane(float x, float y, IMesh **outPlane)
	{
		CPlaneCallback* cbc;
		scom_new<CPlaneCallback>(&cbc);
		cbc->FinalConstruct(x, y);

		CProceduralMesh* pm;
		scom_new<CProceduralMesh>(&pm);
		pm->FinalConstruct(cbc);
		*outPlane = pm;
		cbc->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::CreateBox(const VML::Vector3 &a, const VML::Vector3 &b, IMesh **outBox)
	{
		/// \todo cache callbacks
		CBoxCallback* cbc;
		scom_new<CBoxCallback>(&cbc);
		cbc->FinalConstruct(a, b);

		CProceduralMesh* pm;
		scom_new<CProceduralMesh>(&pm);
		pm->FinalConstruct(cbc);
		*outBox = pm;
		cbc->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::CreateSphere(int nSegments, int nRings, float radius, IMesh** outSphere)
	{
		CSphereCallback* csc;
		scom_new<CSphereCallback>(&csc);
		csc->FinalConstruct(nRings, nSegments, radius);

		CProceduralMesh* pm;
		scom_new<CProceduralMesh>(&pm);
		pm->FinalConstruct(csc);
		*outSphere = pm;
		csc->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::CreateProceduralMesh(IProceduralMeshCallback* callback, IMesh** outProcMesh)
	{
		CProceduralMesh* pm;
		scom_new<CProceduralMesh>(&pm);
		pm->FinalConstruct(callback);
		*outProcMesh = pm;
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::CloseResourceHandle(IMesh* mesh)
	{
		MeshMapIter it = mMeshes.find(mesh->GetURL()->Name);
		ASSERT_STRICT(it != mMeshes.end());
		mMeshes.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::OnDeviceLost()
	{
		for(MeshMapCIter it = mMeshes.begin(); it != mMeshes.end(); ++it)
			it->second->OnDeviceLost();
	}

	//////////////////////////////////////////////////////////////////////////

	void CGeometryManager::OnDeviceReset()
	{
		for(MeshMapCIter it = mMeshes.begin(); it != mMeshes.end(); ++it)
			it->second->OnDeviceReset();
	}	

	//////////////////////////////////////////////////////////////////////////

} // namespace
