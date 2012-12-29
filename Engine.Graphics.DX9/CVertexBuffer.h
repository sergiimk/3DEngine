/*========================================================
* CVertexBuffer.h
* @author Sergey Mikhtonyuk
* @date 18 July 2009
=========================================================*/
#ifndef _CVERTEXBUFFER_H__
#define _CVERTEXBUFFER_H__

#include "DirectX.h"
#include "../Engine.Graphics/Interfaces/IBuffer.h"

namespace DXRenderer
{
	using namespace Engine::Graphics;

	/// Implementation of IBuffer for vertex data
	/** @ingroup DX9 */
	class CVertexBuffer : IBuffer
	{
	public:

		CVertexBuffer();

		~CVertexBuffer();

		size_t Size() const;

		void Resize(size_t newSize, bool copyData, void** ppData);

		void Lock(void** ppData, ELockType type);

		void Unlock();


		IDirect3DVertexBuffer9* getDXBuffer() const { return mBuffer; }

		void setBuffer(IDirect3DVertexBuffer9* buf);

		void ReleaseBuffer();

	private:

		IDirect3DVertexBuffer9* mBuffer;
		size_t mSize;
		void* mpData;
	};

} // namespace

#endif // _CVERTEXBUFFER_H__