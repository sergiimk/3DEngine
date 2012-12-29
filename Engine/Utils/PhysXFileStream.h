/*========================================================
* PhysXFileStream.h
* @author Sergey Mikhtonyuk
* @date 16 June 2009
=========================================================*/
#ifndef _PHYSXFILESTREAM_H__
#define _PHYSXFILESTREAM_H__

#include <NxPhysics.h>
#include <NxStream.h>
#include <stdio.h>

namespace Engine
{

	class PhysXFileStream : public NxStream
	{
	public:
		PhysXFileStream(const char* filename, bool load)
		{
			fopen_s(&fp, filename, load ? "rb" : "wb");
		}

		~PhysXFileStream()
		{
			if(fp)	fclose(fp);
		}

		NxU8 readByte() const
		{
			NxU8 b;
			size_t r = fread(&b, sizeof(NxU8), 1, fp);
			NX_ASSERT(r);
			return b;
		}

		NxU16 readWord() const
		{
			NxU16 w;
			size_t r = fread(&w, sizeof(NxU16), 1, fp);
			NX_ASSERT(r);
			return w;
		}

		NxU32 readDword() const
		{
			NxU32 d;
			size_t r = fread(&d, sizeof(NxU32), 1, fp);
			NX_ASSERT(r);
			return d;
		}

		float readFloat() const
		{
			NxReal f;
			size_t r = fread(&f, sizeof(NxReal), 1, fp);
			NX_ASSERT(r);
			return f;
		}

		double readDouble() const
		{
			NxF64 f;
			size_t r = fread(&f, sizeof(NxF64), 1, fp);
			NX_ASSERT(r);
			return f;
		}

		void readBuffer(void* buffer, NxU32 size) const
		{
			size_t w = fread(buffer, size, 1, fp);
			NX_ASSERT(w);
		}

		NxStream& storeByte(NxU8 b)
		{
			size_t w = fwrite(&b, sizeof(NxU8), 1, fp);
			NX_ASSERT(w);
			return *this;
		}

		NxStream& storeWord(NxU16 w)
		{
			size_t ww = fwrite(&w, sizeof(NxU16), 1, fp);
			NX_ASSERT(ww);
			return *this;
		}

		NxStream& storeDword(NxU32 d)
		{
			size_t w = fwrite(&d, sizeof(NxU32), 1, fp);
			NX_ASSERT(w);
			return *this;
		}

		NxStream& storeFloat(NxReal f)
		{
			size_t w = fwrite(&f, sizeof(NxReal), 1, fp);
			NX_ASSERT(w);
			return *this;
		}

		NxStream& storeDouble(NxF64 f)
		{
			size_t w = fwrite(&f, sizeof(NxF64), 1, fp);
			NX_ASSERT(w);
			return *this;
		}

		NxStream& storeBuffer(const void* buffer, NxU32 size)
		{
			size_t w = fwrite(buffer, size, 1, fp);
			NX_ASSERT(w);
			return *this;
		}

		FILE*			fp;
	};

} // namespace

#endif // _PHYSXFILESTREAM_H__