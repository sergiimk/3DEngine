/*========================================================
* CCmpSpatialNode.h
* @author Sergey Mikhtonyuk
* @date 01 May 2009
=========================================================*/
#ifndef _CCMPSPATIALNODE_H__
#define _CCMPSPATIALNODE_H__

#include "../Interfaces/IEntity.h"
#include "../Interfaces/ICmpSpatialNode.h"
#include "../../Core.Math/VML.h"
#include "../../Core.COM/Implementations.h"
#include <vector>

namespace Engine
{
	/// This class contains all data that define spatial properties of the object
	/** @ingroup Engine */
	class NOVTABLE CCmpSpatialNode : 
		public Core::SCOM::ComRootObject<>,
		public ICmpSpatialNode
	{
	public:
		
		// Using specific allocator to satisfy alignment needs of SSE types
		DECLARE_IMPLEMENTATIONA(CCmpSpatialNode, VML::AlignedAllocator)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ICmpSpatialNode)
			INTERFACE_ENTRY(IComponent)
		END_INTERFACE_MAP()
	
		CCmpSpatialNode();

		const char*			getComponentName()	const	{ return "SpatialNode"; }

		IEntity*			getEntity()			const	{ return mEntity; }

		bool				Bind(IEntity* entity, SComponentDesc* desc);

		//////////////////////////////////////////////////////////////////////////

		const VML::Vector3&	getPosition()		const	{ return mPosition; }

		const VML::Quat&	getRotation()		const	{ return mRotation; }

		const VML::Vector3&	getScale()			const	{ return mScale; }

		const VML::Matrix4&	getTransform()		const	{ return mBatchedTransform; }

		//////////////////////////////////////////////////////////////////////////

		void	setPosition(const VML::Vector3& pos)	{ mPosition = pos; mState = NODE_DIRTY; }

		void	setRotation(const VML::Quat& rot)		{ mRotation = rot; mState = NODE_DIRTY; }

		void	setScale(const VML::Vector3& scale)		{ mScale = scale; mState = NODE_DIRTY; }

		void	setTransform(const VML::Matrix4& tf)	{ mBatchedTransform = tf; }

		void	BatchTransform();

		//////////////////////////////////////////////////////////////////////////

		void			AcceptTraverser(ITransformTraverser* traverser);

		ENodeState		getState()				const	{ return mState; }

		void			setState(ENodeState state)		{ mState = state; }

		ICmpSpatialNode* getParent()			const	{ return mParent; }

		void			AttachTo(ICmpSpatialNode* parent);

		void			Detach();

		void			ReparentTo(ICmpSpatialNode* parent);

		void			ReparentWRT(ICmpSpatialNode* parent);

		//////////////////////////////////////////////////////////////////////////		
		
	private:
		VML::Matrix4		mBatchedTransform;	///< all transformations batched together
		VML::Vector3		mPosition;			///< position
		VML::Quat			mRotation;			///< orientation quaternion
		VML::Vector3		mScale;				///< per-axis scale

		typedef std::vector<CCmpSpatialNode*>	TNodeContainer;
		CCmpSpatialNode*	mParent;		///< parent node
		TNodeContainer		mChildren;		///< children nodes that affected by this node
		ENodeState			mState;			///< state of the node

		IEntity*			mEntity;		///< entity this data belongs to
	};

} // namespace

#endif	// _CCMPSPATIALNODE_H__