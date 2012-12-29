/*========================================================
* CVertexBuffer.cpp
* @author Sergey Mikhtonyuk
* @date 18 July 2009
=========================================================*/
#include "CVertexBuffer.h"
#include "TypeUtilities.h"
#include "CD3DRenderer.h"
#include "managers.h"

namespace DXRenderer
{

	//////////////////////////////////////////////////////////////////////////

	CVertexBuffer::CVertexBuffer() : mBuffer(0), mSize(0), mpData(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CVertexBuffer::~CVertexBuffer()
	{
		if(mBuffer) mBuffer->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CVertexBuffer::Size() const
	{
		return mSize;
	}

	//////////////////////////////////////////////////////////////////////////

	void CVertexBuffer::Resize(size_t newSize, bool copyData, void** ppData)
	{
		LPDIRECT3DDEVICE9 device = ((CD3DRenderer*)g_Renderer)->GetDevice();
		
		// Buffer was locked
		bool locked = mpData ? true : false;

		// Allocate new buffer
		LPDIRECT3DVERTEXBUFFER9 newAPIBuffer = 0;
		if(newSize)
			HR(device->CreateVertexBuffer(newSize, 0, 0, D3DPOOL_MANAGED, &newAPIBuffer, 0));

		if(mBuffer && copyData && newSize && mSize)
		{ // Copy values from old buffer

			if(!locked) 
				Lock(&mpData, LOCK_READONLY);

			// Lock new buffer
			void* newBuffer;
			newAPIBuffer->Lock(0, 0, &newBuffer, 0);

			// Copy old data
			memcpy(newBuffer, mpData, mSize);

			// Unlock and release old buffer
			Unlock();
			ReleaseBuffer();
			mBuffer = newAPIBuffer;

			if(locked)	// Set locked pointer	
				mpData = newBuffer;
			else		// Unlock new buffer
				Unlock();
		}
		else
		{ // Just discard old buffer
			if(locked)
				Unlock();

			ReleaseBuffer();
			mBuffer = newAPIBuffer;

			// Lock new buffer if old one was locked
			if(locked)
				Lock(&mpData, LOCK_DISCARD);
		}

		mSize = newSize;
		if(ppData)
			*ppData = mpData;
	}

	//////////////////////////////////////////////////////////////////////////

	void CVertexBuffer::Lock(void **ppData, ELockType type)
	{		
		*ppData = 0;
		if(mBuffer) mBuffer->Lock(0, 0, ppData, type == LOCK_READONLY ? ToDXFormat(type) : 0);
		mpData = *ppData;
	}

	//////////////////////////////////////////////////////////////////////////

	void CVertexBuffer::Unlock()
	{
		if(mBuffer) mBuffer->Unlock();
		mpData = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CVertexBuffer::setBuffer(IDirect3DVertexBuffer9 *buf)
	{
		assert(!mpData);
		if(mBuffer) mBuffer->Release();
		mBuffer = buf;
		mBuffer->AddRef();

		D3DVERTEXBUFFER_DESC desc;
		mBuffer->GetDesc(&desc);
		mSize = desc.Size;
	}

	//////////////////////////////////////////////////////////////////////////

	void CVertexBuffer::ReleaseBuffer()
	{
		assert(!mpData);
		if(mBuffer) mBuffer->Release();
		mBuffer = 0;
		mSize = 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace