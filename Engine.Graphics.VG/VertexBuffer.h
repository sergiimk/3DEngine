/*========================================================
* VertexBuffer.h
* @author Sergey Mikhtonyuk
* @date 20 July 2009
=========================================================*/
#ifndef _VERTEXBUFFER_H__
#define _VERTEXBUFFER_H__

#include "VGTypes.h"
#include "../Engine.Graphics/Interfaces/IBuffer.h"
#include "../Engine.Graphics/Interfaces/MeshTypes.h"
#include "../Core.Math/VML.h"

namespace VG
{
	using namespace Engine::Graphics;

	//////////////////////////////////////////////////////////////////////////

	/// Vertex structure
	/** @ingroup VG */
	struct VGVertex
	{
		float x, y, z;		///< Position components
		unsigned int color;	///< Color

		/// Default ctor
		VGVertex() 
		{ }

		/// Full ctor
		VGVertex(const VML::Vector2& pos, unsigned int clr)
			: x(pos.getX()), y(pos.getY()), z(0), color(clr)
		{ }

		/// Vertex declaration
		static const SVertexElement* getDeclaration()
		{
			static SVertexElement elems[3];
			elems[0] = SVertexElement(0, ETYPE_FLOAT3, USG_POSITION, 0);
			elems[1] = SVertexElement(sizeof(float) * 3, ETYPE_COLOR, USG_COLOR, 0);
			elems[2] = END_DECLARATION();

			return elems;
		}
	};

	/// Linear interpolation of color
	inline void LerpColor(unsigned int& res, const unsigned int& c1, const unsigned int& c2, float s)
	{
		unsigned char* pr = (unsigned char*)&res;
		const unsigned char* pc1 = (const unsigned char*)&c1;
		const unsigned char* pc2 = (const unsigned char*)&c2;

		pr[0] = pc1[0] + unsigned char(float(pc2[0] - pc1[0]) * s);
		pr[1] = pc1[1] + unsigned char(float(pc2[1] - pc1[1]) * s);
		pr[2] = pc1[2] + unsigned char(float(pc2[2] - pc1[2]) * s);
		pr[3] = pc1[3] + unsigned char(float(pc2[3] - pc1[3]) * s);
	}	 

	//////////////////////////////////////////////////////////////////////////

	/// std::vector-like wrapper for meshes vertex buffer
	/** @ingroup VG */
	class VertexBuffer
	{
	public:

		VertexBuffer(IBuffer* wrapped) : mBuffer(wrapped), mSize(0), mData(0)
		{
		}

		/// Buffer capacity
		size_t capacity() const
		{ return mBuffer->Size() / sizeof(VGVertex); }

		/// Size of the buffer
		size_t size() const
		{ return mSize; }

		/// Clears the buffer
		void clear()
		{ mSize = 0; }

		/// Adds vertex to the end of the buffer
		void push_back(const VGVertex& vertex)
		{
			assert(mData);
			// Check capacity
			if(mSize == capacity())
				reserve(capacity() << 1);
			// insert element
			mData[mSize++] = vertex;
		}

		/// Indexation operator
		const VGVertex& operator[](size_t index) const
		{
			assert(mData && index < mSize);
			return mData[index];
		}

		/// Indexation operator
		VGVertex& operator[](size_t index)
		{
			assert(mData && index < mSize);
			return mData[index];
		}

		/// Last element
		VGVertex& back()
		{
			assert(mData);
			return mData[mSize - 1];
		}


		/// Locks all buffer
		void start_update()
		{
			mBuffer->Lock((void**)&mData, LOCK_NORMAL);
		}

		/// Unlocks buffer
		void end_update()
		{
			mBuffer->Unlock();
			mData = 0;
		}

		/// Reserves the suitable buffer
		void reserve(size_t newCapacity)
		{
			if(capacity() >= newCapacity)
				return;

			mBuffer->Resize(newCapacity * sizeof(VGVertex), true, (void**)&mData);
		}

		/// Access to wrapped buffer
		IBuffer* wrapped() const
		{ return mBuffer; }

	private:

		IBuffer*	mBuffer;
		VGVertex*	mData;
		size_t		mSize;

	};

} // namespace

#endif // _VERTEXBUFFER_H__