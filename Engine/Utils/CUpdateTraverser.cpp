/*========================================================
* CUpdateTraverser.cpp
* @author Sergey Mikhtonyuk
* @date 26 May 2009
=========================================================*/
#include "CUpdateTraverser.h"
#include "../Interfaces/IEntity.h"
#include "../Interfaces/ICmpSpatialNode.h"
#include "../../Core.Math/VML.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	void CUpdateTraverser::TraversingStarted(ITransformGraph* tg)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CUpdateTraverser::TraversingEnd(ITransformGraph* tg)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	bool CUpdateTraverser::VisitNode(ICmpSpatialNode *node, IEntity *entity)
	{
		bool shouldUpdate = node->getState() == NODE_DIRTY;
		ICmpSpatialNode* parent = node->getParent();
		shouldUpdate = shouldUpdate || (parent && parent->getState() == NODE_UPDATING);

		if(shouldUpdate)
		{
			node->BatchTransform();

			if(parent)
			{
				// Change child matrix according to parent's
				node->setTransform( parent->getTransform() *  node->getTransform() );
			}
			node->setState(NODE_UPDATING);
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	void CUpdateTraverser::LeaveNode(ICmpSpatialNode* node, IEntity* entity)
	{
		// Compute bounding volume
		node->setState(NODE_UP_TO_DATE);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace