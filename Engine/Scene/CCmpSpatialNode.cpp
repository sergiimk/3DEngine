/*========================================================
* CCmpSpatialNode.cpp
* @author Sergey Mikhtonyuk
* @date 03 May 2009
=========================================================*/
#include "CCmpSpatialNode.h"
#include "../Interfaces/ITransformTraverser.h"
#include "../../Core.Utils/EnvironmentDefs.h"
#include <algorithm>
#include <functional>

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CCmpSpatialNode::CCmpSpatialNode()
		:	mEntity(0),
			mParent(0),
			mState(NODE_DIRTY)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CCmpSpatialNode::BatchTransform()
	{
		mBatchedTransform = VML::Matrix4::scale(mScale);
		mBatchedTransform = VML::Matrix4::rotation(mRotation) * mBatchedTransform;
		mBatchedTransform = VML::Matrix4::translation(mPosition) * mBatchedTransform;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CCmpSpatialNode::Bind(IEntity* entity, SComponentDesc* desc)
	{
		mEntity = entity;
		SSpatialNodeDesc* snd = (SSpatialNodeDesc*)desc;

		mPosition = snd->Position;
		mRotation = snd->Rotation;
		mScale = snd->Scale;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCmpSpatialNode::AcceptTraverser( ITransformTraverser* traverser )
	{
		bool cont = traverser->VisitNode(this, mEntity);
		if(cont)
		{
			std::for_each(	mChildren.begin(), 
							mChildren.end(), 
							std::bind2nd(
								std::mem_fun1(&ICmpSpatialNode::AcceptTraverser),
								traverser));
		}
		traverser->LeaveNode(this, mEntity);
	}

	//////////////////////////////////////////////////////////////////////////

	void CCmpSpatialNode::AttachTo(ICmpSpatialNode* parent)
	{
		assert(parent);
		assert(!mParent);	// use reparent instead

		CCmpSpatialNode* cparent = static_cast<CCmpSpatialNode*>(parent);
		cparent->mChildren.push_back(this);
		mParent = cparent;

		mState = NODE_DIRTY;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCmpSpatialNode::Detach()
	{
		assert(mParent);

		TNodeContainer::iterator it = std::find(mParent->mChildren.begin(), mParent->mChildren.end(), this);
		assert(it != mParent->mChildren.end()); // structure corrupted
		mParent->mChildren.erase(it);
		mParent = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCmpSpatialNode::ReparentTo(ICmpSpatialNode* parent)
	{
		Detach();
		AttachTo(parent);

		mState = NODE_DIRTY;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCmpSpatialNode::ReparentWRT(ICmpSpatialNode* parent)
	{
		NOT_IMPLEMENTED();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace