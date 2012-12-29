/*========================================================
* IMatrixStack.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef _IMATRIXSTACK_H__
#define _IMATRIXSTACK_H__

#include "../../Core.Math/VML_fwd.h"
#include "../../Core.COM/Interfaces.h"

namespace Engine
{
	namespace Graphics
	{
		/// Interface to class for hierarchical matrix transformations
		/** @ingroup Graphics */
		SCOM_INTERFACE(IMatrixStack, "7e398591-0398-4aa0-868a-4c615a308c76", Core::SCOM::IUnknown)
		{
		public:
			/// Removes matrix from the top of the stack
			virtual void						Pop() = 0;

			/// Adds matrix on top of the stack equal to the previous (identity if first)
			virtual void						Push() = 0;

			/// Adds specified matrix on top of the stack
			virtual void						Push(const VML::Matrix4& mat) = 0;

			/// Premultiplies top matrix on the given (given transform goes first)
			virtual void						PreMultiply(const VML::Matrix4& mat) = 0;

			/// Postmultiplies top matrix on the given (given transform goes second)
			virtual void						PostMultiply(const VML::Matrix4& mat) = 0;

			/// Returns matrix on top of the stack
			virtual const VML::Matrix4&			GetTop() const = 0;

			/// Set top matrix to identity
			virtual void						LoadIdentity() = 0;

			/// Size of the stack
			virtual size_t						Size() const = 0;
		};



	} // namespace
} // namespace

#endif