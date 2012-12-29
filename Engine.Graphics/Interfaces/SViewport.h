/*========================================================
* SViewport.h
* @author Sergey Mikhtonyuk
* @date 08 May 2009
=========================================================*/
#ifndef _SVIEWPORT_H__
#define _SVIEWPORT_H__

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		struct SRect
		{
			SRect() { }
			SRect(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h)
			{ }

			int		X;		///< coordinate of the left border of rect
			int		Y;		///< coordinate of the top border of rect
			int		Width;	///< width of the rect
			int		Height;	///< height of the rect
		};

		//////////////////////////////////////////////////////////////////////////

		/// Defines region of the surface that will be used for rendering
		/** @ingroup Graphics */
		struct SViewport : public SRect
		{
			SViewport() { }
			SViewport(int x, int y, int w, int h) : SRect(x, y, w, h) { }

			SViewport& operator = (const SRect& rect)
			{ 
				memcpy((SRect*)this, &rect, sizeof(SRect));
				return *this;
			}
		};

		//////////////////////////////////////////////////////////////////////////

		inline bool operator == (const SViewport& vp, const SRect& rect)
		{ return vp.X == rect.X && vp.Y == rect.Y && vp.Width == rect.Width && vp.Height == rect.Height; }

		inline bool operator == (const SRect& rect, const SViewport& vp)
		{ return vp == rect; }

		inline bool operator != (const SViewport& vp, const SRect& rect)
		{ return !(vp == rect); }

		inline bool operator != (const SRect& rect, const SViewport& vp)
		{ return !(vp == rect); }

		//////////////////////////////////////////////////////////////////////////

		inline bool operator == (const SViewport& vp, const SViewport& vp2)
		{ return vp.X == vp2.X && vp.Y == vp2.Y && vp.Width == vp2.Width && vp.Height == vp2.Height; }

		inline bool operator != (const SViewport& vp, const SViewport& vp2)
		{ return !(vp == vp2); }

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _SVIEWPORT_H__