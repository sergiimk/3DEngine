/*========================================================
* CTextureManager.cpp
* @author Sergey Mikhtonyuk
* @date 04 January 2009
=========================================================*/
#include "../Core/SekaiCore.h"
#include "../Core/CommonPlugin.h"
#include "../Core.FileSystem/IFileSystem.h"
#include "CSurfaceManager.h"
#include "CTexture.h"
#include "CCubeTexture.h"

namespace DXRenderer
{
	//////////////////////////////////////////////////////////////////////////

	CSurfaceManager::CSurfaceManager()
	{
		LogTrace("Creating texture manager");
	}

	//////////////////////////////////////////////////////////////////////////

	CSurfaceManager::~CSurfaceManager()
	{
		LogTrace("Destroying texture manager");

		ASSERT_SOFT(!mTextures.size());

		if(!mTextures.size())
			for(TextureMapIter it = mTextures.begin(); it != mTextures.end(); ++it)
				LogErrorAlways("[Memory leak] Texture %s was not released before shutdown", it->second->GetURL()->Name.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	void CSurfaceManager::FindOrLoadTexture(const Utils::URL &url, ITexture** outTex)
	{
		*outTex = 0;

		// Make full path
		Utils::URL nurl(
			Core::gEnv->FileSystem->PathCombine(
				"../Resources/Meshes/Textures", 
				url.Name.c_str()
				));

		TextureMapIter it = mTextures.find(nurl.Name);
		if(it != mTextures.end())
		{
			*outTex = it->second;
			(*outTex)->AddRef();
			return;
		}

		CTexture* pt;
		scom_new<CTexture>(&pt);
		pt->FinalConstruct(nurl);
		mTextures.insert(std::make_pair(nurl.Name, pt));
		*outTex = pt;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSurfaceManager::FindOrLoadCubeTexture(const Utils::URL &url, ITexture **outTex)
	{
		*outTex = 0;

		// Make full path
		Utils::URL nurl(
			Core::gEnv->FileSystem->PathCombine(
			"../Resources/Meshes/Textures", 
			url.Name.c_str()
			));

		TextureMapIter it = mTextures.find(nurl.Name);
		if(it != mTextures.end())
		{
			*outTex = it->second;
			(*outTex)->AddRef();
			return;
		}

		CCubeTexture* pt;
		scom_new<CCubeTexture>(&pt);
		pt->FinalConstruct(nurl);
		mTextures.insert(std::make_pair(nurl.Name, pt));
		*outTex = pt;
	}

	//////////////////////////////////////////////////////////////////////////

	void CSurfaceManager::CreateNewTexture(const SSurfaceDesc& sdesc, ITexture** outTex)
	{
		*outTex = 0;
		CTexture* pt;
		scom_new<CTexture>(&pt);
		pt->FinalConstruct(sdesc);
		*outTex = pt;

		mDynamicTextures.push_back(pt);
	}

	void CSurfaceManager::SaveTextureToFile(ITexture *ptex, const char *file)
	{
		HR(D3DXSaveTextureToFileA(file, D3DXIFF_BMP, ((CTexture*)ptex)->GetTexture(), 0));
	}

	//////////////////////////////////////////////////////////////////////////

	void CSurfaceManager::CloseResourceHandle(ITexture* tex)
	{
		TextureMapIter it = mTextures.find(tex->GetURL()->Name);
		if(it != mTextures.end())
		{
			// Static
			mTextures.erase(it);
		}
		else
		{
			// Dynamic
			TDTexContainer::iterator dti = std::find(mDynamicTextures.begin(), mDynamicTextures.end(), tex);
			ASSERT_STRICT(dti != mDynamicTextures.end());
			mDynamicTextures.erase(dti);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CSurfaceManager::OnDeviceLost()
	{
		for(TextureMapIter it = mTextures.begin(); it != mTextures.end(); ++it)
			it->second->OnDeviceLost();

		for(TDTexContainer::iterator it = mDynamicTextures.begin(); it != mDynamicTextures.end(); ++it)
			(*it)->OnDeviceLost();
	}

	//////////////////////////////////////////////////////////////////////////

	void CSurfaceManager::OnDeviceReset()
	{
		for(TextureMapIter it = mTextures.begin(); it != mTextures.end(); ++it)
			it->second->OnDeviceReset();

		for(TDTexContainer::iterator it = mDynamicTextures.begin(); it != mDynamicTextures.end(); ++it)
			(*it)->OnDeviceReset();
	}	

	//////////////////////////////////////////////////////////////////////////

} // namespace
