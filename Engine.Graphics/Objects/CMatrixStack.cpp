/*========================================================
* CMatrixStack.cpp
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/

#include "CMatrixStack.h"

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		using namespace VML;
		
		//////////////////////////////////////////////////////////////////////////

		void CMatrixStack::Push()
		{
			if(mStack.size())
				mStack.push_back(mStack.back());
			else
				mStack.push_back(Matrix4::identity());
		}

		//////////////////////////////////////////////////////////////////////////

		void CMatrixStack::Push(const VML::Matrix4& mat)
		{
			mStack.push_back(mat);
		}

		//////////////////////////////////////////////////////////////////////////

		void CMatrixStack::Pop()
		{
			assert(mStack.size());
			mStack.pop_back();
		}

		//////////////////////////////////////////////////////////////////////////

		void CMatrixStack::PreMultiply(const VML::Matrix4 &mat)
		{
			assert(mStack.size());
			mStack.back() = mStack.back() * mat;
		}

		//////////////////////////////////////////////////////////////////////////

		void CMatrixStack::PostMultiply(const VML::Matrix4& mat)
		{
			assert(mStack.size());
			mStack.back() = mat * mStack.back();
		}

		//////////////////////////////////////////////////////////////////////////

		const VML::Matrix4& CMatrixStack::GetTop() const
		{
			assert(mStack.size());
			return mStack.back(); 
		}

		//////////////////////////////////////////////////////////////////////////

		void CMatrixStack::LoadIdentity()
		{
			assert(mStack.size());
			mStack.back() = Matrix4::identity();
		}

		//////////////////////////////////////////////////////////////////////////

		size_t CMatrixStack::Size() const
		{
			return mStack.size();
		}

	} // namespace
} // namespace