/*========================================================
* CUpdateTraverser.h
* @author Sergey Mikhtonyuk
* @date 26 May 2009
=========================================================*/
#ifndef _CUPDATETRAVERSER_H__
#define _CUPDATETRAVERSER_H__

#include "../Interfaces/ITransformTraverser.h"

namespace Engine
{
	/// Common traversed used to update transformations and bounding volumes
	/** @ingroup Engine */
	class CUpdateTraverser : public ITransformTraverser
	{
	public:
		void TraversingStarted(ITransformGraph* tg);

		void TraversingEnd(ITransformGraph* tg);

		bool VisitNode(ICmpSpatialNode* node, IEntity* entity);

		void LeaveNode(ICmpSpatialNode* node, IEntity* entity);
	};

} // namespace

#endif	// _CUPDATETRAVERSER_H__