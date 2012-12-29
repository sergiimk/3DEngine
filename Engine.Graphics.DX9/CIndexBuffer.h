/*========================================================
* CIndexBuffer.h
* @author Sergey Mikhtonyuk
* @date 18 July 2009
=========================================================*/
#ifndef _CINDEXBUFFER_H__
#define _CINDEXBUFFER_H__

#include "DirectX.h"
#include "../Engine.Graphics/Interfaces/IBuffer.h"

namespace DXRenderer
{
	using namespace Engine::Graphics;

	/// Implementation of IBuffer for index data
	/** @ingroup DX9 */
	class CIndexBuffer : IBuffer
	{
	public:

		CIndexBuffer();

		~CIndexBuffer();

		size_t Size() const;

		void Resize(size_t newSize, bool copyData = false, void** ppData = 0);

		void Lock(void** ppData, ELockType type);

		void Unlock();


		IDirect3DIndexBuffer9* getDXBuffer() const { return mBuffer; }

		void setBuffer(IDirect3DIndexBuffer9* buf);

		void ReleaseBuffer();

	private:

		IDirect3DIndexBuffer9* mBuffer;
		size_t mSize;
		void* mpData;
	};

} // namespace

#endif // _CINDEXBUFFER_H__