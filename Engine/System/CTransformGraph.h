/*========================================================
* CTransformGraph.h
* @author Sergey Mikhtonyuk
* @date 01 May 2009
=========================================================*/
#ifndef _CTRANSFORMGRAPH_H__
#define _CTRANSFORMGRAPH_H__

#include "../Interfaces/ITransformGraph.h"
#include "../Scene/CCmpSpatialNode.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{
	/// Implementation of ITransformGraph interface
	/** @ingroup Engine */
	class NOVTABLE CTransformGraph : 
		public Core::SCOM::ComRootObject<>,
		public ITransformGraph
	{
	public:

		DECLARE_IMPLEMENTATION(CTransformGraph)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ITransformGraph)
		END_INTERFACE_MAP()

		CTransformGraph();

		void				AcceptTraverser(ITransformTraverser* traverser);

		void				Update();

		ICmpSpatialNode*	getRoot()						{ return mRootNode; }

		void				setRoot(ICmpSpatialNode* node)	{ mRootNode = static_cast<CCmpSpatialNode*>(node); }

	private:
		CCmpSpatialNode*	mRootNode;	///< root transformation node
	};

} // namespace

#endif	// _CTRANSFORMGRAPH_H__