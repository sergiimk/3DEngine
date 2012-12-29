/*========================================================
* CMaterialManager.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "CMaterialManager.h"
#include "../Core.Logging/ILogger.h"
#include "../Core.FileSystem/IFile.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "../Engine.Graphics/RendererExceptions.h"
#include "../Core.COM/Intellectual.h"
#include "CMaterial.h"
#include <algorithm>
#include <functional>

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Core;
	using namespace SCOM;
	using namespace FileSystem;
	//////////////////////////////////////////////////////////////////////////

	CMaterialManager::CMaterialManager()
	{
		LogTrace("Creating material manager");
	}

	//////////////////////////////////////////////////////////////////////////

	CMaterialManager::~CMaterialManager()
	{
		LogTrace("Destroying material manager");

		mDefaultMaterial.Release();

		ASSERT_SOFT(!mMaterials.size());

		if(!mMaterials.size())
			for(MaterialMapCIter it = mMaterials.begin(); it != mMaterials.end(); ++it)
				LogErrorAlways("[Memory leak] Material %s was not released before shutdown", it->second->GetURL()->Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterialManager::FindOrLoadMaterial(const Utils::URL &url, IMaterial** outMaterial)
	{
		*outMaterial = 0;

		// Make full path
		Utils::URL nurl(
			gEnv->FileSystem->PathCombine(
			"../Resources/Meshes/Materials", 
			url.Name.c_str()
			));

		// Try find loaded
		MaterialMapIter it = mMaterials.find(nurl.Name);
		if(it != mMaterials.end())
		{
			*outMaterial = it->second;
			(*outMaterial)->AddRef();
			return;
		}

		// Create material
		CMaterial* pm;
		scom_new<CMaterial>(&pm);
		pm->FinalConstruct(nurl);
		mMaterials.insert(std::make_pair(nurl.Name, pm));
		*outMaterial = pm;
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterialManager::CreateMaterial(IMaterial** outMaterial)
	{
		*outMaterial = 0;

		CMaterial* pm;
		scom_new<CMaterial>(&pm);
		pm->FinalConstruct(Utils::URL(""));
		*outMaterial = pm;
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterialManager::GetDefaultMaterial(IMaterial** outMaterial)
	{
		*outMaterial = 0;

		/// \todo Load default material name from settings
		if(!mDefaultMaterial)
			FindOrLoadMaterial(Utils::URL("default.mt"), mDefaultMaterial.wrapped());

		*outMaterial = mDefaultMaterial;
		(*outMaterial)->AddRef();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterialManager::CloseResourceHandle(IMaterial* mat)
	{
		MaterialMapIter it = mMaterials.find(mat->GetURL()->Name);
		ASSERT_STRICT(it != mMaterials.end());
		mMaterials.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterialManager::OnDeviceLost()
	{
		for(MaterialMapCIter it = mMaterials.begin(); it != mMaterials.end(); ++it)
			it->second->OnDeviceLost();
	}

	//////////////////////////////////////////////////////////////////////////

	void CMaterialManager::OnDeviceReset()
	{
		for(MaterialMapCIter it = mMaterials.begin(); it != mMaterials.end(); ++it)
			it->second->OnDeviceReset();
	}	

	//////////////////////////////////////////////////////////////////////////

} // namespace
