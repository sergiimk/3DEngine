/*========================================================
* CLayer.cpp
* @author Sergey Mikhtonyuk
* @date 20 July 2009
=========================================================*/
#include "CLayer.h"
#include "CPath.h"
#include <algorithm>
#include "../Engine.Graphics/Interfaces/IRenderer.h"
#include "../Engine.Graphics/Interfaces/IMaterialManager.h"
#include "../Engine.Graphics/Interfaces/IMaterial.h"
#include "../Engine.Graphics/Interfaces/IEffect.h"
#include "../Engine.Graphics/Interfaces/IEffectInstance.h"
#include "../Core.Utils/URL.h"

namespace VG
{
	//////////////////////////////////////////////////////////////////////////

	CLayer::CLayer() : mUsageRefs(0), mRenderer(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CLayer::~CLayer()
	{
		for(size_t i = 0; i != mComponents.size(); ++i)
			mComponents[i]->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::FinalConstruct(Engine::Graphics::IRenderer* renderer)
	{
		mRenderer = renderer;
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CLayer::getComponentsNum() const
	{
		return mComponents.size();
	}

	//////////////////////////////////////////////////////////////////////////

	IPath* CLayer::getComponent(size_t index) const
	{
		return mComponents[index];
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::AddComponent(IPath* path)
	{
		assert(!mUsageRefs);
		path->AddRef();
		mComponents.push_back(path);
	}

	//////////////////////////////////////////////////////////////////////////

	IPath* CLayer::AddNewComponent()
	{
		assert(!mUsageRefs);
		CPath* p;
		scom_new<CPath>(&p);
		p->FinalConstruct(mRenderer);
		mComponents.push_back(p);
		return p;
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::RemoveComponent(VG::IPath *path)
	{
		assert(!mUsageRefs);
		std::vector<IPath*>::iterator it = std::find(mComponents.begin(), mComponents.end(), path);
		if(it != mComponents.end())
			mComponents.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::RecalculateAll()
	{
		assert(mUsageRefs);
		for(size_t i = 0; i != mComponents.size(); ++i)
			mComponents[i]->RecalculatePath();
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::setToleranceToAll(float tolerance)
	{
		for(size_t i = 0; i != mComponents.size(); ++i)
			mComponents[i]->setTolerance(tolerance);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::Render()
	{
		assert(mUsageRefs);

		for(int p = (int)mComponents.size() - 1; p >= 0; --p)
		{
			IPath* path = mComponents[p];

			// Render stroke
			mRenderer->SetMaterial(mMatStroke, 1);
			IEffectInstance* effect = mRenderer->GetEffectInstance();
			int npass = effect->BeginSequence();

			for(int i = 0; i != npass; ++i)
			{
				effect->BeginPass(i);
				IMesh* mesh = path->getStrokeMesh();
				mRenderer->SetGeometryBuffer(mesh);

				for(size_t s = 0; s != mesh->GetSubsetCount(); ++s)
					mRenderer->DrawGeometry(mesh->GetSubset(s));

				effect->EndPass();
			}
			effect->EndSequence();
			

			// Render fill
			mRenderer->SetMaterial(mMatFill, 1);
			effect = mRenderer->GetEffectInstance();
			npass = effect->BeginSequence();
			for(int i = 0; i != npass; ++i)
			{
				effect->BeginPass(i);
				IMesh* mesh = path->getFillMesh();
				mRenderer->SetGeometryBuffer(mesh);

				for(size_t s = 0; s != mesh->GetSubsetCount(); ++s)
					mRenderer->DrawGeometry(mesh->GetSubset(s));

				effect->EndPass();
			}
			effect->EndSequence();
		}

		mRenderer->Clear(SRFC_CLEAR_STENCIL);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::AddUser()
	{
		assert(mUsageRefs >= 0);
		
		if(!mUsageRefs++)
		{
			for(size_t i = 0; i != mComponents.size(); ++i)
				mComponents[i]->AddUser();

			mRenderer->GetMaterialManager()->FindOrLoadMaterial(
				Utils::URL("vg_fill_concave.mt"), 
				mMatFill.wrapped());

			mRenderer->GetMaterialManager()->FindOrLoadMaterial(
				Utils::URL("vg_stroke.mt"), 
				mMatStroke.wrapped());

			mMatStroke->AddUser();
			mMatFill->AddUser();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CLayer::RemoveUser()
	{
		assert(mUsageRefs > 0);
		
		if(!(--mUsageRefs))
		{
			for(size_t i = 0; i != mComponents.size(); ++i)
				mComponents[i]->RemoveUser();

			mMatStroke->RemoveUser();
			mMatFill->RemoveUser();

			mMatStroke.Release();
			mMatFill.Release();
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace