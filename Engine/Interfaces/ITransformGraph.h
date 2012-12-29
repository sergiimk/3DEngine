/*========================================================
* ITransformGraph.h
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#ifndef _ITRANSFORMGRAPH_H__
#define _ITRANSFORMGRAPH_H__

#include "../Engine_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	/// This data structure defines hierarchical transformation relationships of objects
	/** @ingroup Engine */
	SCOM_INTERFACE(ITransformGraph, "27c41a55-6e73-473f-8198-8835fac0806b", Core::SCOM::IUnknown)
	{
	public:

		/// Passes traverser through hierarchy starting with root node
		virtual void AcceptTraverser(ITransformTraverser* traverser) = 0;

		/// After all spatial adjustments in are frame call this to update the transformations
		/** This function passes the update traverser down the graph and updates only
		 *  nodes that was changed during the frame and their children */
		virtual void Update() = 0;

		/// Returns root transformation node
		virtual ICmpSpatialNode* getRoot() = 0;

		/// Sets root transformation node
		virtual void setRoot(ICmpSpatialNode* node) = 0;
	};

} // namespace

#endif	// _ITRANSFORMGRAPH_H__