/*========================================================
* ITransformTraverser.h
* @author Sergey Mikhtonyuk
* @date 01 May 2009
=========================================================*/
#ifndef _ITRANSFORMTRAVERSER_H__
#define _ITRANSFORMTRAVERSER_H__

#include "../Engine_fwd.h"

namespace Engine
{
	/// Visitor for transformation graph eases operation with tree object structure
	/** @ingroup Engine */
	class ITransformTraverser
	{
	public:
		/// Called before start of traversing (initialization)
		virtual void TraversingStarted(ITransformGraph* tg) = 0;

		/// Called when traversing completed (finalization)
		virtual void TraversingEnd(ITransformGraph* tg) = 0;

		/// Called when entering the node
		/** @param node Node that being visited
		 *  @param entity Entity associated with this node
		 *  @return pass true if you want to continue traversing this branch */
		virtual bool VisitNode(ICmpSpatialNode* node, IEntity* entity) = 0;

		/// Called when all children of the node are visited
		/** Placing operations in this method result in depth-first traversing */
		virtual void LeaveNode(ICmpSpatialNode* node, IEntity* entity) = 0;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif	// _ITRANSFORMTRAVERSER_H__