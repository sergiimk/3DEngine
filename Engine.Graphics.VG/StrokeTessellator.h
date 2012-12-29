/*========================================================
* StrokeTessellator.h
* @author Sergey Mikhtonyuk
* @date 08 February 2009
=========================================================*/
#ifndef _STROKETESSELLATOR_H__
#define _STROKETESSELLATOR_H__

#include "VertexBuffer.h"
#include "ApproximationUnit.h"
#include "../Core.Math/VML.h"

namespace VG
{
	using namespace Engine::Graphics;

	/// Performs stroke tessellation of approximated path
	/** @ingroup VG */
	class StrokeTessellator
	{
	public:
		/// Wrap approximation buffer and vb reference
		StrokeTessellator(ApproximationBuffer* l, VertexBuffer& sb, const PathProperties& properties)
			:	lines(l), stroke(sb), props(properties), currentCommand(0), length_acc(0)
		{ }

		/// Begin path tessellation
		void Tessellate();


	protected:
		//------------------- Top-level ----------------------

		/// Tessellates the stroke path
		void TessellateStrokePath();

		/// Interpolate stroke color
		void InterpolateStrokeColor();

		//------------------- Linear stroke ----------------------

		/// Plots line beginning
		void PlotLineBeginning();

		/// Plots line ending
		void PlotLineEnding();

		/// Plots line joint according to params
		void PlotLineJoint();

		/// If path is closed circle the joints
		void PlotClosedPath();

		//------------------- Line joints ----------------------

		/// Plot line simple joint
		void PlotJointToFirst();

		/// Plot line bevel joint
		void PlotJointBevel();

		/// Plot line miter joint
		void PlotJointMiter();

		/// Plot line round joint
		void PlotJointRound();

		/// Plot line separate joint
		void PlotJointSeparate();


		//------------------- Service ----------------------

		/// Creates new vertex, in gradient stroke mode 'z' coordinate will contain distance from the start point
		void AddVertex(const VML::Vector2& pos, bool top)
		{
			//if(props.properties[PP_STROKE_STYLE] == SS_LINE_GRAD_WIDTH)
			//	return VGVertex(x, y, 0, props.stroke_color[top ? 0 : 1]);
			//if(props.properties[PP_STROKE_STYLE] == SS_LINE_GRAD_LENGTH)
			//	return VGVertex(x, y, length_acc, 0);
			//return VGVertex(x, y, 0, props.stroke_color[0]);

			stroke.push_back(VGVertex(pos, props.properties[PP_STROKE_COLOR1]));
		}


		/// Loads all settings for point
		void UpdateState(size_t point);


		/// Fills v, n arrays if p[] are set
		void CalculateLines()
		{
			v[0] = p[1] - p[0];
			v[1] = p[2] - p[1];

			l[0] = v[0].length();
			l[1] = v[1].length();

			n[0].setX(-v[0].getY() / l[0]);
			n[0].setY(v[0].getX() / l[0]);

			n[1].setX(-v[1].getY() / l[1]);
			n[1].setY(v[1].getX() / l[1]);
		}

		/// Fills p, v, n arrays
		void CalculateLines(size_t startPoint)
		{
			if(lines->points.size() > 2)
			{
				p[0] = lines->points[startPoint];
				p[1] = lines->points[startPoint+1];
				p[2] = lines->points[startPoint+2];
				CalculateLines();
			}
			else
			{
				p[0] = lines->points[startPoint];
				p[1] = lines->points[startPoint+1];
				p[2] = lines->points[startPoint+1];
				CalculateLines();

				v[1] = p[2] - p[0];
				l[1] = v[1].length();
				n[1].setX(-v[1].getY() / l[1]);
				n[1].setY(v[1].getX() / l[1]);
			}
		}

		/// Shifts data calculated with CalculateLines()
		void CalculateNextLine(size_t startPoint)
		{
			p[0] = p[1];
			p[1] = p[2];
			p[2] = lines->points[startPoint+2];

			v[0] = v[1];
			v[1] = p[2] - p[1];

			l[0] = l[1];
			l[1] = v[1].length();

			n[0] = n[1];

			n[1].setX(-v[1].getY() / l[1]);
			n[1].setY(v[1].getX() / l[1]);
		}

		/// Inserts degenerated connection
		void degen_connect(const VML::Vector2& to)
		{
			stroke.push_back(stroke.back());
			AddVertex(to, false);
		}

		/// Determinant of 2x2 matrix
		inline float determinant2(float a11, float a12, float a21, float a22)
		{
			return a11 * a22 - a12 * a21;
		}

		/// Fast version that takes direction vectors
		inline bool line_intersection(
			const VML::Vector2& p0, const VML::Vector2& p1, 
			const VML::Vector2& p2, const VML::Vector2& p3, 
			const VML::Vector2& v0, const VML::Vector2& v1, VML::Vector2& p_int)
		{
			float det = determinant2(v1.getX(), -v0.getX(), v1.getY(), -v0.getY());

			float s = determinant2(p0.getX() - p2.getX(), -v0.getX(), p0.getY() - p2.getY(), -v0.getY()) / det;
			float t = determinant2(v1.getX(), p0.getX() - p2.getX(), v1.getY(), p0.getY() - p2.getY()) / det;

			p_int.setX(p0.getX() + v0.getX() * t);
			p_int.setY(p0.getY() + v0.getY() * t);

			return (s > 0) && (s < 1) && (t > 0) && (t < 1);
		}

		//////////////////////////////////////////////////////////////////////////




	protected:
		ApproximationBuffer*	lines;			///< Approximation buffer
		VertexBuffer&			stroke;			///< Stroke vertex buffer

		PathProperties			props;			///< Path properties
		PathCommand				special;		///< Special-case command
		size_t					currentCommand;	///< Current processed command

		VML::Vector2			p[3];			///< Points p1-p2-p3
		VML::Vector2			v[2];			///< Direction vectors of l1(p1-p2) and l2(p2-p3)
		VML::Vector2			n[2];			///< Normal vectors of l1 and l2
		float					l[2];			///< Lengths of l1 and l2

		size_t					closedBegin;	///< Index of first point in the closed path
		size_t					closedBeginV;	///< Index of first vertex plotted in the closed path
		float					length_acc;		///< Accumulator for length to apply gradient
	};

} // namespace

#endif // _STROKETESSELLATOR_H__