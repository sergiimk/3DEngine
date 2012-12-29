/*========================================================
* ApproximationUnit.h
* @author Sergey Mikhtonyuk
* @date 25 January 2009
=========================================================*/
#ifndef _APPROXIMATIONUNIT_H__
#define _APPROXIMATIONUNIT_H__

#include "VGLib_fwd.h"
#include "../Core.Math/VML.h"
#include <vector>

namespace VG
{
	//////////////////////////////////////////////////////////////////////////

	/// Holds temporary data of lines and style commands needed in triangulation step
	/** @ingroup VG */
	struct ApproximationBuffer
	{
		typedef std::vector<VML::Vector2 > TPointCont;

		typedef std::vector<std::pair<size_t, PathCommand> > TStyleStopCont;

		/// Points of interpolated path
		TPointCont		points;

		/// Positions where we need to change style of triangulation
		TStyleStopCont	styleStops;
	};

	//////////////////////////////////////////////////////////////////////////

	/// Used for path approximation with lines
	/** @ingroup VG */
	struct ApproximationUnit
	{
		/// Wraps path and allocates app buffer
		ApproximationUnit(IPathBuffer* p, ApproximationBuffer& appbuf, float dist_tolerance);

		/// Starts path approximation
		void Approximate();

	protected:
		/// Process command
		void ProcessCommand(PathCommand cmd);

		/// Approximates quadratic bezier curve
		void AppendBezier2Recursive(const VML::Vector2& p1, const VML::Vector2& p2, const VML::Vector2& p3, int level);

		/// Approximates cubic bezier curve
		void AppendBezier3Recursive(const VML::Vector2& p1, const VML::Vector2& p2, const VML::Vector2& p3, const VML::Vector2& p4, int level);

		/// Adds point & checks for bounding box
		void AppendPoint(const VML::Vector2& p)
		{
			buf.points.push_back(p);
		}

	protected:
		float					tolerance;		///< Tolerance for curve approximation
		IPathBuffer*			path;			///< Path data
		ApproximationBuffer&	buf;			///< Reference to approximation buffer
		size_t					path_start;		///< indicates the point that started a path (needed to process closed paths)
		size_t					currentPoint;	///< Current processed point
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace


#endif // _CAPPROXIMATIONUNIT_H__