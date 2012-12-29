/*========================================================
* SSurfaceDesc.h
* @author Sergey Mikhtonyuk
* @date 07 May 2009
=========================================================*/
#ifndef _SSURFACEDESC_H__
#define _SSURFACEDESC_H__

#include <iosfwd>

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		/// Buffer format
		/** @ingroup Graphics */
		enum EBufferFormat
		{
			FMT_UNKNOWN,

			FMT_R8G8B8,
			FMT_A8R8G8B8,
			FMT_X8R8G8B8,
			FMT_X1R5G5B5,
			FMT_A1R5G5B5,
			FMT_A2R10G10B10,

			FMT_L8,

			FMT_R16F,
			FMT_G16R16F,
			FMT_A16B16G16R16F,

			FMT_R32F,
			FMT_G32R32F,
			FMT_A32B32G32R32F,

			FMT_DXT1,
			FMT_DXT2,
			FMT_DXT3,
			FMT_DXT4,
			FMT_DXT5,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Surface usage type
		/** @ingroup Graphics */
		enum ESurfaceType
		{
			SFC_TEXTURE,
			SFC_CUBETEXTURE,
			SFC_RENDERTARGET,
			SFC_BACKBUFFER,
		};

		//////////////////////////////////////////////////////////////////////////

		/// Surface params structure
		/** @ingroup  */
		struct SSurfaceDesc
		{
			int				Width;		///< Width of the surface
			int				Height;		///< Height of the surface
			EBufferFormat	Format;		///< Format of the surface
			ESurfaceType	Type;		///< Type of the surface
		};

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _SSURFACEDESC_H__