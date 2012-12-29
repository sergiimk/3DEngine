/*========================================================
* MeshTypes.h
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#ifndef _MESHTYPES_H__
#define _MESHTYPES_H__

#include <iosfwd>

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		/// Type of primitives that contained in mesh
		/** @ingroup Graphics */
		enum EPrimitiveType
		{
			PT_TRIANGLE_STRIP,
			PT_TRIANGLE_LIST,
			PT_INDEXED_TRIANGLE_LIST,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Usage of vertex declaration element
		/** @ingroup Graphics */
		enum EElemUsage
		{
			USG_POSITION,		
			USG_BLENDWEIGHT,
			USG_BLENDINDICES,
			USG_NORMAL,
			USG_PSIZE,
			USG_TEXCOORD,
			USG_TANGENT,
			USG_BINORMAL,
			USG_COLOR,

			USG_UNUSED = 0xff,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Type of the element of vertex
		/** @ingroup Graphics  */
		enum EElemType
		{
			ETYPE_FLOAT,
			ETYPE_FLOAT2,
			ETYPE_FLOAT3,
			ETYPE_FLOAT4,
			ETYPE_COLOR,	// unsigned int

			ETYPE_UNUSED = 0xff,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Description of vertex element
		/** @ingroup Graphics */
		struct SVertexElement
		{
			unsigned short	Offset;		///< Offset of element from beginning of the vertex structure
			unsigned char	Type;		///< Type of the element
			unsigned char	Usage;		///< Usage type of the element
			unsigned char	UsageIndex;	///< Index of usage

			SVertexElement() {}

			SVertexElement(unsigned short offset, EElemType type, EElemUsage usage, unsigned char usg_index)
				: Offset(offset), Type(type), Usage(usage), UsageIndex(usg_index)
			{}
		};

		#define MAX_VERTEX_ELEMENTS 16
		#define END_DECLARATION() SVertexElement(0xffff, ETYPE_UNUSED, USG_UNUSED, 0)

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _MESHTYPES_H__