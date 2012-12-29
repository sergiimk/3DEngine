/*========================================================
* ICmpSpatialNode.h
* @author Sergey Mikhtonyuk
* @date 04 May 2009
=========================================================*/
#ifndef _ICMPSPATIALNODE_H__
#define _ICMPSPATIALNODE_H__

#include "../Engine_fwd.h"
#include "IComponent.h"
#include "../../Core.Math/VML.h"
#include "../Engine_classid.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////
	/// Node state to optimize graph update
	/** @ingroup Engine */
	enum ENodeState
	{
		NODE_UP_TO_DATE,	///< Indicates that node transforms are actual
		NODE_DIRTY,			///< Indicates that node transforms should be updated
		NODE_UPDATING,		///< Service flag used during update
	};


	//////////////////////////////////////////////////////////////////////////


	/// Built-in entity component. Represents entity position in space and transform hierarchy
	/** @ingroup Engine */
	SCOM_INTERFACE(ICmpSpatialNode, "72ab539a-4f25-42d3-8a68-d90157d0c3cb", IComponent)
	{
	public:

		/// Returns current position vector
		virtual const VML::Vector3&	getPosition()		const	= 0;

		/// Returns current rotation quaternion
		virtual const VML::Quat&	getRotation()		const	= 0;

		/// Returns current per-axis scale vector
		virtual const VML::Vector3&	getScale()			const	= 0;

		/// Returns the batched transformation matrix
		virtual const VML::Matrix4&	getTransform()		const	= 0;

		//////////////////////////////////////////////////////////////////////////

		/// Sets current position vector
		virtual void				setPosition(const VML::Vector3& pos)	= 0;

		/// Sets current rotation quaternion
		virtual void				setRotation(const VML::Quat& rot)		= 0;

		/// Sets current per-axis scale vector
		virtual void				setScale(const VML::Vector3& scale)		= 0;

		/// This method is used for overriding computed batched transform
		/** Typical situation is when after batching of transform
		 *  this matrix is multiplied on transform of parent node */
		/// \todo look for a better way to do this
		virtual void				setTransform(const VML::Matrix4& tf)	= 0;

		/// Computes the batched transformation matrix
		virtual void				BatchTransform() = 0;

		//////////////////////////////////////////////////////////////////////////

		/// Drives traverser through the hierarchy
		virtual void				AcceptTraverser(ITransformTraverser* traverser) = 0;

		/// Returns node's state
		virtual ENodeState			getState() const = 0;

		/// Sets node state
		virtual void				setState(ENodeState state) = 0;

		/// Returns parent node
		virtual ICmpSpatialNode*	getParent() const = 0;

		/// Links the node to specified one
		virtual void				AttachTo(ICmpSpatialNode* parent) = 0;

		/// Detaches node from its parent
		virtual void				Detach() = 0;

		/// Detaches node from previous parent first and then links to new parent
		virtual void				ReparentTo(ICmpSpatialNode* parent) = 0;

		/// Reparent with respect to
		/** Reparents node, but modifies initial transform 
		 *  so that object maintain its current position in the world */
		virtual void				ReparentWRT(ICmpSpatialNode* parent) = 0;
	};


	//////////////////////////////////////////////////////////////////////////


	/// SpatialNode component description, used for component instantiation
	/** @ingroup Engine */
	struct SSpatialNodeDesc : public SComponentDesc
	{
		VML::Vector3		Position;			///< Position of entity
		VML::Quat			Rotation;			///< Rotation quaternion
		VML::Vector3		Scale;				///< Per-axis scale of entity

		SSpatialNodeDesc()
			:	SComponentDesc(&CLSID_CCmpSpatialNode),
				Position(0),
				Rotation(VML::Quat::identity()),
				Scale(1.0f)
		{}

		SSpatialNodeDesc(	const VML::Vector3& pos, 
							const VML::Quat& rot = VML::Quat::identity(),
							const VML::Vector3& scale = VML::Vector3(1.0f))
			:	SComponentDesc(&CLSID_CCmpSpatialNode),
				Position(pos),
				Rotation(rot),
				Scale(scale)
		{}

		void ResetDefaults() 
		{ 
			Position = VML::Vector3(0);
			Rotation = VML::Quat::identity();
			Scale = VML::Vector3(1.0f);
		}
	};


	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif	// _ICMPSPATIALNODE_H__