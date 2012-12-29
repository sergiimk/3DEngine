/*========================================================
* CApproximationUnit.cpp
* @author Sergey Mikhtonyuk
* @date 25 January 2009
=========================================================*/

#include "ApproximationUnit.h"
#include "IPathBuffer.h"
#include "VGExceptions.h"
#include <cassert>

namespace VG
{
	//////////////////////////////////////////////////////////////////////////

	ApproximationUnit::ApproximationUnit(IPathBuffer* p, ApproximationBuffer& appbuf, float dist_tolerance)
		:	path(p), 
			tolerance(dist_tolerance), 
			buf(appbuf),
			currentPoint(0),
			path_start(-1)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void ApproximationUnit::Approximate()
	{
		size_t commands_num = path->getCommandsNumber();
		PathCommand* commands = path->getCommands();
		size_t points_num = path->getPointsNumber();

		// Iterate all commands and build linear path
		for(size_t cmd = 0; cmd != commands_num; ++cmd)
		{
			PathCommand toProcess = commands[cmd];

			// If this is a style command, write it io buffer to pass to tessellation unit
			if(toProcess > _PATH_COMMANDS_TOP || toProcess == PC_CLOSE)
			{
				// Remove one point if last one matches first
				if(VML::equivalent(buf.points[path_start], buf.points.back()))
					buf.points.pop_back();

				buf.styleStops.push_back(std::make_pair(buf.points.size() - 1, toProcess));
				continue;
			}

			ProcessCommand(toProcess);
		}

		assert(currentPoint == points_num);
		if(currentPoint != points_num) 
			throw VGFormatException("Commands-points number mismatch");
	}

	//////////////////////////////////////////////////////////////////////////

	void ApproximationUnit::ProcessCommand(PathCommand cmd)
	{
		size_t commands_num = path->getCommandsNumber();
		PathCommand* commands = path->getCommands();
		size_t points_num = path->getPointsNumber();
		VML::Vector2* points = path->getPoints();

		switch(cmd)
		{

		case PC_MOVE:
			if(buf.styleStops.size() != 0 && buf.styleStops.back().second == PC_MOVE)
			{
				throw VGFormatException("Invalid MOVE command position");
			}
			else
			{
				AppendPoint(points[currentPoint++]);
				path_start = buf.points.size() - 1;
				buf.styleStops.push_back(std::make_pair(path_start, PC_MOVE));
			}
			break;


		case PC_LINE:			
			if(VML::equivalent(points[currentPoint], buf.points.back(), 0.001f))
			{
				++currentPoint;
				break;
			}

			AppendPoint(points[currentPoint]);
			++currentPoint;
			break;


		case PC_BEZIER_2:
			AppendBezier2Recursive(
				points[currentPoint - 1],
				points[currentPoint],
				points[currentPoint + 1], 0);

			AppendPoint(points[currentPoint + 1]);
			currentPoint += 2;
			break;


		case PC_BEZIER_3:
			AppendBezier3Recursive(
				points[currentPoint - 1],
				points[currentPoint],
				points[currentPoint + 1],
				points[currentPoint + 2], 0);

			AppendPoint(points[currentPoint + 2]);
			currentPoint += 3;
			break;

		default:
			throw VGFormatException("Path command not implemented");
		}
	}

	//////////////////////////////////////////////////////////////////////////


	/*=======================================================================
	 =  Approximations
	 =======================================================================*/

	void ApproximationUnit::AppendBezier2Recursive(
		const VML::Vector2& p1, const VML::Vector2& p2, 
		const VML::Vector2& p3, int level)
	{
		static const int curve_recursion_limit = 10;

		if(level > curve_recursion_limit) return;

		VML::Vector2 p12 = (p1 + p2) * 0.5f;
		VML::Vector2 p23 = (p2 + p3) * 0.5f;
		VML::Vector2 p123 = (p12 + p23) * 0.5f;

		VML::Vector2 d1 = p3 - p1;
		VML::Vector2 d2 = p2 - p3;
		
		/// \todo use de Casteljau's method
		float d = fabs(d2.getX() * d1.getY() - d2.getY() * d1.getX());

		if(d*d < tolerance * d1.lengthSqr())
		{
			AppendPoint(p123);
			return;
		}

		AppendBezier2Recursive(p1, p12, p123, ++level); 
		AppendBezier2Recursive(p123, p23, p3, level);
	}

	//////////////////////////////////////////////////////////////////////////

	void ApproximationUnit::AppendBezier3Recursive(
		const VML::Vector2& p1, const VML::Vector2& p2, 
		const VML::Vector2& p3, const VML::Vector2& p4, int level)
	{
		static const int curve_recursion_limit = 10;

		if(level > curve_recursion_limit) return;

		VML::Vector2 p12 = (p1 + p2) * 0.5f;
		VML::Vector2 p23 = (p2 + p3) * 0.5f;
		VML::Vector2 p34 = (p3 + p4) * 0.5f;
		VML::Vector2 p123 = (p12 + p23) * 0.5f;
		VML::Vector2 p234 = (p23 + p34) * 0.5f;
		VML::Vector2 p1234 = (p123 + p234) * 0.5f;

		VML::Vector2 d1 = p4 - p1;
		VML::Vector2 d2 = p2 - p4;
		VML::Vector2 d3 = p3 - p4;

		float df2 = fabs(d2.getX() * d1.getY() - d2.getY() * d1.getX());
		float df3 = fabs(d3.getX() * d1.getY() - d3.getY() * d1.getX());

		if((df2 + df3)*(df2 + df3) < tolerance * d1.lengthSqr())
		{
			AppendPoint(p1234);
			return;
		}

		AppendBezier3Recursive(p1, p12, p123, p1234, ++level); 
		AppendBezier3Recursive(p1234, p234, p34, p4, level);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace