/*========================================================
* CTransformGraph.cpp
* @author Sergey Mikhtonyuk
* @date 01 May 2009
=========================================================*/
#include "CTransformGraph.h"
#include "../Utils/CUpdateTraverser.h"
#include <cassert>

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	CTransformGraph::CTransformGraph() : mRootNode(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CTransformGraph::AcceptTraverser(Engine::ITransformTraverser *traverser)
	{
		assert(traverser);
		traverser->TraversingStarted(this);
		if(mRootNode) mRootNode->AcceptTraverser(traverser);
		traverser->TraversingEnd(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CTransformGraph::Update()
	{
		CUpdateTraverser ut;
		AcceptTraverser(&ut);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace