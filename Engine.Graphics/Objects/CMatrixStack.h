/*========================================================
* CMatrixStack.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef _CMATRIXSTACK_H__
#define _CMATRIXSTACK_H__

#include "../Interfaces/IMatrixStack.h"
#include "../../Core.COM/Implementations.h"
#include "../../Core.Math/VML.h"
#include <vector>

namespace Engine
{
	namespace Graphics
	{
		/// Class for hierarchical matrix transformations
		/** @ingroup Graphics */
		class NOVTABLE CMatrixStack : 
			public Core::SCOM::ComRootObject<>,
			public IMatrixStack
		{
		public:
			DECLARE_IMPLEMENTATION(CMatrixStack)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IMatrixStack)
			END_INTERFACE_MAP()

			void						Pop();
			void						Push();
			void						Push(const VML::Matrix4& mat);
			void						PreMultiply(const VML::Matrix4& mat);
			void						PostMultiply(const VML::Matrix4& mat);
			const VML::Matrix4&	GetTop() const;
			void						LoadIdentity();
			size_t						Size() const;

		private:
			typedef	std::vector<VML::Matrix4, 
								VML::AlignedAllocator<VML::Matrix4> > TMatrixStack;

			TMatrixStack				mStack;
		};

	} // namespace
} // namespace

#endif