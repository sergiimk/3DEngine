/*========================================================
* TypeUtilities.h
* @author Sergey Mikhtonyuk
* @date 07 May 2009
=========================================================*/
#ifndef _TYPEUTILITIES_H__
#define _TYPEUTILITIES_H__

#include "../Engine.Graphics/Interfaces/MeshTypes.h"
#include "../Engine.Graphics/Interfaces/SSurfaceDesc.h"
#include "../Engine.Graphics/Interfaces/IBuffer.h"
#include "DirectX.h"
#include <cassert>

namespace DXRenderer
{
	using namespace Engine::Graphics;

	//////////////////////////////////////////////////////////////////////////

	inline EElemType FromDXFormat(_D3DDECLTYPE type)
	{
		switch(type)
		{
		case D3DDECLTYPE_FLOAT1: return ETYPE_FLOAT;
		case D3DDECLTYPE_FLOAT2: return ETYPE_FLOAT2;
		case D3DDECLTYPE_FLOAT3: return ETYPE_FLOAT3;
		case D3DDECLTYPE_FLOAT4: return ETYPE_FLOAT4;
		case D3DDECLTYPE_D3DCOLOR: return ETYPE_COLOR;
		default: ASSERT_STRICT(false); return ETYPE_UNUSED;
		};
	}

	inline _D3DDECLTYPE ToDXFormat(EElemType type)
	{
		switch(type)
		{
		case ETYPE_FLOAT:  return D3DDECLTYPE_FLOAT1;
		case ETYPE_FLOAT2: return D3DDECLTYPE_FLOAT2;
		case ETYPE_FLOAT3: return D3DDECLTYPE_FLOAT3;
		case ETYPE_FLOAT4: return D3DDECLTYPE_FLOAT4;
		case ETYPE_COLOR:  return D3DDECLTYPE_D3DCOLOR;
		case ETYPE_UNUSED: return D3DDECLTYPE_UNUSED;
		default: ASSERT_STRICT(false); return D3DDECLTYPE_UNUSED;
		};
	}

	//////////////////////////////////////////////////////////////////////////

	inline EElemUsage FromDXFormat(_D3DDECLUSAGE usage)
	{
		switch(usage)
		{
		case D3DDECLUSAGE_POSITION:		return USG_POSITION;
		case D3DDECLUSAGE_BLENDWEIGHT:	return USG_BLENDWEIGHT;
		case D3DDECLUSAGE_BLENDINDICES:	return USG_BLENDINDICES;
		case D3DDECLUSAGE_NORMAL:		return USG_NORMAL;
		case D3DDECLUSAGE_PSIZE:		return USG_PSIZE;
		case D3DDECLUSAGE_TEXCOORD:		return USG_TEXCOORD;
		case D3DDECLUSAGE_TANGENT:		return USG_TANGENT;
		case D3DDECLUSAGE_BINORMAL:		return USG_BINORMAL;
		case D3DDECLUSAGE_COLOR:		return USG_COLOR;
		default: ASSERT_STRICT(false);  return USG_UNUSED;
		};
	}

	inline _D3DDECLUSAGE ToDXFormat(EElemUsage usage)
	{
		switch(usage)
		{
		case USG_POSITION:				return D3DDECLUSAGE_POSITION;
		case USG_BLENDWEIGHT:			return D3DDECLUSAGE_BLENDWEIGHT;
		case USG_BLENDINDICES:			return D3DDECLUSAGE_BLENDINDICES;
		case USG_NORMAL:				return D3DDECLUSAGE_NORMAL;
		case USG_PSIZE:					return D3DDECLUSAGE_PSIZE;
		case USG_TEXCOORD:				return D3DDECLUSAGE_TEXCOORD;
		case USG_TANGENT:				return D3DDECLUSAGE_TANGENT;
		case USG_BINORMAL:				return D3DDECLUSAGE_BINORMAL;
		case USG_COLOR:					return D3DDECLUSAGE_COLOR;
		default: ASSERT_STRICT(false);  return D3DDECLUSAGE_COLOR;
		};
	}

	//////////////////////////////////////////////////////////////////////////

	inline SVertexElement FromDXFormat(const D3DVERTEXELEMENT9& elem)
	{
		SVertexElement ve(
			elem.Stream == 0xFF ? 0xffff : elem.Offset,
			elem.Stream == 0xFF ? ETYPE_UNUSED : FromDXFormat((_D3DDECLTYPE)elem.Type), 
			elem.Stream == 0xFF ? USG_UNUSED : FromDXFormat((_D3DDECLUSAGE)elem.Usage), 
			elem.Stream == 0xFF ? 0 : elem.UsageIndex 
		);
		return ve;
	}

	inline D3DVERTEXELEMENT9 ToDXFormat(const SVertexElement& elem)
	{
		D3DVERTEXELEMENT9 ve = {
			elem.Offset == 0xffff ? 0xFF : 0,
			elem.Offset == 0xffff ? 0 : elem.Offset,
			elem.Offset == 0xffff ? D3DDECLTYPE_UNUSED : ToDXFormat((EElemType)elem.Type),
			elem.Offset == 0xffff ? 0 : D3DDECLMETHOD_DEFAULT,
			elem.Offset == 0xffff ? 0 : ToDXFormat((EElemUsage)elem.Usage),
			elem.Offset == 0xffff ? 0 : elem.UsageIndex
		};
		return ve;
	}

	inline size_t VertexSizeFromDecl(const SVertexElement* elems)
	{
		int last = -1;
		unsigned short off = 0;
		
		for(int i = 0; i != MAX_VERTEX_ELEMENTS; ++i)
		{
			if(elems[i].Offset == 0xffff) break;
			if(elems[i].Offset > off)
			{
				off = elems[i].Offset;
				last = i;
			}
		}
		
		switch(elems[last].Type)
		{
		case ETYPE_FLOAT:		return off + sizeof(float);
		case ETYPE_FLOAT2:		return off + sizeof(float) * 2;
		case ETYPE_FLOAT3:		return off + sizeof(float) * 3;
		case ETYPE_FLOAT4:		return off + sizeof(float) * 4;
		case ETYPE_COLOR:		return off + sizeof(int);
		case ETYPE_UNUSED: 		return off;
		}
		ASSERT_STRICT(false);
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	/// Converts from DX format to EBufferFormat
	inline EBufferFormat FromDXFormat(D3DFORMAT dxf)
	{
		switch(dxf)
		{
		case D3DFMT_R8G8B8:			return FMT_R8G8B8;
		case D3DFMT_A8R8G8B8:		return FMT_A8R8G8B8;
		case D3DFMT_X8R8G8B8:		return FMT_X8R8G8B8;
		case D3DFMT_X1R5G5B5:		return FMT_X1R5G5B5;
		case D3DFMT_A1R5G5B5:		return FMT_A1R5G5B5;
		case D3DFMT_A2R10G10B10:	return FMT_A2R10G10B10;

		case D3DFMT_L8:				return FMT_L8;

		case D3DFMT_R16F:			return FMT_R16F;
		case D3DFMT_G16R16F:		return FMT_G16R16F;
		case D3DFMT_A16B16G16R16F:	return FMT_A16B16G16R16F;
		case D3DFMT_R32F:			return FMT_R32F;
		case D3DFMT_G32R32F:		return FMT_G32R32F;
		case D3DFMT_A32B32G32R32F:	return FMT_A32B32G32R32F;

		case D3DFMT_DXT1:			return FMT_DXT1;
		case D3DFMT_DXT2:			return FMT_DXT2;
		case D3DFMT_DXT3:			return FMT_DXT3;
		case D3DFMT_DXT4:			return FMT_DXT4;
		case D3DFMT_DXT5:			return FMT_DXT5;
		default:					ASSERT_STRICT(false); return FMT_UNKNOWN;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	/// Converts from DX format to EBufferFormat
	inline D3DFORMAT ToDXFormat(EBufferFormat fmt)
	{
		switch(fmt)
		{
		case FMT_R8G8B8:			return D3DFMT_R8G8B8;
		case FMT_A8R8G8B8:			return D3DFMT_A8R8G8B8;
		case FMT_X8R8G8B8:			return D3DFMT_X8R8G8B8;
		case FMT_X1R5G5B5:			return D3DFMT_X1R5G5B5;
		case FMT_A1R5G5B5:			return D3DFMT_A1R5G5B5;
		case FMT_A2R10G10B10:		return D3DFMT_A2R10G10B10;

		case FMT_L8:				return D3DFMT_L8;

		case FMT_R16F:				return D3DFMT_R16F;
		case FMT_G16R16F:			return D3DFMT_G16R16F;
		case FMT_A16B16G16R16F:		return D3DFMT_A16B16G16R16F;
		case FMT_R32F:				return D3DFMT_R32F;
		case FMT_G32R32F:			return D3DFMT_G32R32F;
		case FMT_A32B32G32R32F:		return D3DFMT_A32B32G32R32F;

		case FMT_DXT1:				return D3DFMT_DXT1;
		case FMT_DXT2:				return D3DFMT_DXT2;
		case FMT_DXT3:				return D3DFMT_DXT3;
		case FMT_DXT4:				return D3DFMT_DXT4;
		case FMT_DXT5:				return D3DFMT_DXT5;
		default:					ASSERT_STRICT(false); return D3DFMT_UNKNOWN;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	inline DWORD ToDXFormat(ELockType type)
	{
		switch(type)
		{
		case LOCK_NORMAL:			return 0;
		case LOCK_DISCARD:			return D3DLOCK_DISCARD;
		case LOCK_READONLY:			return D3DLOCK_READONLY;
		default:					ASSERT_STRICT(false); return 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif	// _TYPEUTILITIES_H__