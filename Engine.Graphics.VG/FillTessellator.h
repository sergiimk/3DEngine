/*========================================================
* FillTessellator.h
* @author Sergey Mikhtonyuk
* @date 25 January 2009
=========================================================*/
#ifndef _FILLTESSELLATOR_H__
#define _FILLTESSELLATOR_H__

#include "VertexBuffer.h"
#include "ApproximationUnit.h"
#include "../Core.Math/VML.h"

namespace VG
{

	/// Performs fill tessellation of approximated path
	/** @ingroup VG */
	class FillTessellator
	{
	public:
		/// Wrap approximation buffer and vb reference
		FillTessellator(ApproximationBuffer* l, VertexBuffer& fb, const PathProperties& properties)
			:	lines(l), fill(fb), props(properties), currentCommand(0)
		{ }

		/// Begin path tessellation
		void Tessellate();

	protected:

		/// Tessellates the fill of path
		void TessellateFill();

		/// Interpolate fill color
		void InterpolateFillColor();

		/// Adds point with bounding box check
		void AddPoint(const VGVertex& p)
		{
			fill.push_back(p);
		}

	protected:
		ApproximationBuffer*	lines;			///< Pointer to approximation buffer
		VertexBuffer&			fill;			///< Fill vertex buffer

		PathProperties			props;			///< Path properties
		size_t					currentCommand;	///< Current processed command
	};


} // namespace


#endif // _FILLTESSELLATOR_H__