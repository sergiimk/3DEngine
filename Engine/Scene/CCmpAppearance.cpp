/*========================================================
* CCmpAppearance.cpp
* @author Sergey Mikhtonyuk
* @date 15 June 2009
=========================================================*/
#include "CCmpAppearance.h"
#include "../../Engine.Graphics/Interfaces/IMesh.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CCmpAppearance::CCmpAppearance()
		: mEntity(0), mMesh(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CCmpAppearance::~CCmpAppearance()
	{
		if(mMesh) mMesh->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CCmpAppearance::Bind(Engine::IEntity *entity, SComponentDesc* desc)
	{
		mEntity = entity;
		mMesh = ((SAppearanceDesc*)desc)->Mesh;
		if(mMesh) mMesh->AddRef();
		return true;
	}

} // namespace