/*========================================================
* StrokeTessellator.cpp
* @author Sergey Mikhtonyuk
* @date 17 April 2009
=========================================================*/
#include "StrokeTessellator.h"
#include <cassert>
#include <limits>
#include "VGExceptions.h"

namespace VG
{
	//////////////////////////////////////////////////////////////////////////
	// Top level
	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::Tessellate()
	{
		if(props.properties[PP_STROKE_STYLE] == SS_NONE || !lines->points.size())
			return;

		// Hope no resizing will happen
		if(stroke.size() < lines->points.size() << 2)
			stroke.reserve(lines->points.size() << 3);

		stroke.start_update();
		TessellateStrokePath();
		InterpolateStrokeColor();
		stroke.end_update();
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::TessellateStrokePath()
	{
		// At least 2 points
		if(lines->points.size() < 2) return;		

		UpdateState(0);

		size_t npoints = lines->points.size();
		for(size_t pn = 0; pn != npoints; ++pn)
		{
			if(special == PC_MOVE)
			{
				CalculateLines(pn);
				if(pn != 0) degen_connect(p[0]);
				closedBegin = pn; closedBeginV = stroke.size(); // the start of a path
				PlotLineBeginning();
				if(pn != 0) stroke[closedBeginV - 1] = stroke[closedBeginV]; // Adjust degenerated connection
			}
			else if(special == PC_CLOSE)
			{
				PlotClosedPath();
				UpdateState(pn + 1);
				continue;
			}
			else if(pn < lines->points.size() - 2)
			{
				CalculateNextLine(pn);
			}

			UpdateState(pn + 1);

			if(special == PC_CLOSE)
			{
				p[0] = lines->points[pn];
				p[1] = lines->points[pn+1];
				p[2] = lines->points[closedBegin];
				CalculateLines();
			}
			else if(pn == lines->points.size() - 2)
			{
				PlotLineEnding();
				return;
			}

			PlotLineJoint();
		}
	}

	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	// Plotting
	//////////////////////////////////////////////////////////////////////////


	void StrokeTessellator::PlotLineBeginning()
	{
		float width = props.strokeWidth * 0.5f;

		/// \todo check for closed path not to add a cap
		AddVertex(p[0] - n[0] * width, false);
		AddVertex(p[0] + n[0] * width, true);
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotLineEnding()
	{
		float width = props.strokeWidth * 0.5f;

		AddVertex(p[2] - n[1] * width, false);
		AddVertex(p[2] + n[1] * width, true);
	}

	//////////////////////////////////////////////////////////////////////////
	
	void StrokeTessellator::PlotLineJoint()
	{
		PathCommand joint = (PathCommand)props.properties[PP_DEFAULT_JOINT];

		if(joint != LJOINT_TOFIRST)
		{
			//Collinearity check
			float angcos = VML::dot(v[0], v[1]) / (l[0] * l[1]);
			if(fabs(angcos) > (1 - FLOAT_CMP_EPSILON))
			{
				PlotJointToFirst();
				return;
			}
		}

		switch(joint)
		{
		case LJOINT_TOFIRST:
			PlotJointToFirst();
			break;
		case LJOINT_SEPARATE:
			PlotJointSeparate();
			break;
		case LJOINT_BEVEL:
			PlotJointBevel();
			break;
		case LJOINT_MITER:
			PlotJointMiter();
			break;
		case LJOINT_ROUND:
			PlotJointRound();
			break;
		default:
			throw VGFormatException("Line joint not implemented");
		};
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotClosedPath()
	{
		p[0] = p[1];
		p[1] = p[2];
		p[2] = lines->points[closedBegin + 1];

		CalculateLines();
		PlotLineJoint();

		bool had_degen = closedBeginV != 0;

		if(had_degen)
		{
			VML::Vector2 v1(stroke[closedBeginV].x, stroke[closedBeginV].y);
			VML::Vector2 v2(stroke[closedBeginV - 1].x, stroke[closedBeginV - 1].y);
			had_degen = VML::equivalent(v1, v2, FLOAT_CMP_EPSILON);
		}

		size_t strokesize = stroke.size();
		stroke[closedBeginV] = stroke[strokesize - 2];
		stroke[closedBeginV + 1] = stroke[strokesize - 1];

		if(had_degen) 
			stroke[closedBeginV - 1] = stroke[closedBeginV];
	}

	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// Joints
	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotJointToFirst()
	{
		float width = props.strokeWidth * 0.5f;

		length_acc += l[0];
		AddVertex(p[1] - n[0] * width, false);
		AddVertex(p[1] + n[0] * width, true);
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotJointBevel()
	{
		float width = props.strokeWidth * 0.5f;

		VML::Vector2 l11 = p[0] - n[0] * width;
		VML::Vector2 l12 = p[1] - n[0] * width;
		VML::Vector2 l21 = p[0] + n[0] * width;
		VML::Vector2 l22 = p[1] + n[0] * width;

		VML::Vector2 l31 = p[1] - n[1] * width;
		VML::Vector2 l32 = p[2] - n[1] * width;
		VML::Vector2 l41 = p[1] + n[1] * width;
		VML::Vector2 l42 = p[2] + n[1] * width;

		VML::Vector2 i1, i2;
		bool f = line_intersection(l11, l12, l31, l32, v[0], v[1], i1);
		line_intersection(l21, l22, l41, l42, v[0], v[1], i2);

		length_acc += l[0];

		if(f)
		{
			AddVertex(i1, false);
			AddVertex(l22, true);
			AddVertex(i1, false);
			AddVertex(l41, true);
		}
		else
		{
			AddVertex(l12, false);
			AddVertex(i2, true);
			AddVertex(l31, false);
			AddVertex(i2, true);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotJointMiter()
	{
		float width = props.strokeWidth * 0.5f;

		VML::Vector2 l11 = p[0] - n[0] * width;
		VML::Vector2 l12 = p[1] - n[0] * width;
		VML::Vector2 l21 = p[0] + n[0] * width;
		VML::Vector2 l22 = p[1] + n[0] * width;

		VML::Vector2 l31 = p[1] - n[1] * width;
		VML::Vector2 l32 = p[2] - n[1] * width;
		VML::Vector2 l41 = p[1] + n[1] * width;
		VML::Vector2 l42 = p[2] + n[1] * width;

		VML::Vector2 i1, i2;
		line_intersection(l11, l12, l31, l32, v[0], v[1], i1);
		line_intersection(l21, l22, l41, l42, v[0], v[1], i2);

		length_acc += l[0];
		AddVertex(i1, false);
		AddVertex(i2, true);
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotJointRound()
	{
		float width = props.strokeWidth * 0.5f;

		VML::Vector2 l11 = p[0] - n[0] * width;
		VML::Vector2 l12 = p[1] - n[0] * width;
		VML::Vector2 l21 = p[0] + n[0] * width;
		VML::Vector2 l22 = p[1] + n[0] * width;

		VML::Vector2 l31 = p[1] - n[1] * width;
		VML::Vector2 l32 = p[2] - n[1] * width;
		VML::Vector2 l41 = p[1] + n[1] * width;
		VML::Vector2 l42 = p[2] + n[1] * width;

		VML::Vector2 i1, i2;
		bool f = line_intersection(l11, l12, l31, l32, v[0], v[1], i1);
		line_intersection(l21, l22, l41, l42, v[0], v[1], i2);

		length_acc += l[0];

		if(f)
		{
			VML::Vector2 rn = n[0] + n[1];
			rn.normalize();

			AddVertex(i1, false);
			AddVertex(l22, true);
			AddVertex(i1, false);
			AddVertex(p[1] + rn * width, true);
			AddVertex(i1, false);
			AddVertex(l41, true);
		}
		else
		{
			VML::Vector2 rn = -n[0] - n[1];
			rn.normalize();

			AddVertex(l12, false);
			AddVertex(i2, true);
			AddVertex(p[1] + rn * width, false);
			AddVertex(i2, true);
			AddVertex(l31, false);
			AddVertex(i2, true);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::PlotJointSeparate()
	{
		float width = props.strokeWidth * 0.5f;

		length_acc += l[0];

		AddVertex(p[1] - n[0] * width, false);
		AddVertex(p[1] + n[0] * width, true);
		// degenerated triangle
		AddVertex(p[1] + n[0] * width, true);
		AddVertex(p[1] - n[1] * width, false);
		AddVertex(p[1] - n[1] * width, false);
		AddVertex(p[1] + n[1] * width, true);
	}
	
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// Color interpolation
	//////////////////////////////////////////////////////////////////////////

	void StrokeTessellator::InterpolateStrokeColor()
	{
		
		/*const size_t strokesize = stroke.size();
		if(props.properties[PP_STROKE_STYLE] == SS_LINE_GRAD_LENGTH)
		{
			// length_acc should have a line length now
			for(size_t i = 0; i != strokesize; ++i)
			{
				float progress = 1.0f - (length_acc - stroke[i].z) / length_acc;
				LerpColor(&stroke[i].color, &props.stroke_color[0], &props.stroke_color[1], progress);
				stroke[i].z = 0;
			}
		}
		else if(props.properties[PP_STROKE_STYLE] == SS_LINE_GRAD_X)
		{
			float min = (std::numeric_limits<float>::max)();
			float max = (std::numeric_limits<float>::min)();
			for(size_t i = 0; i != strokesize; ++i)
			{
				if(stroke[i].x < min) min = stroke[i].x;
				if(stroke[i].x > max) max = stroke[i].x;
			}

			float dx = max - min;

			for(size_t i = 0; i != strokesize; ++i)
			{
				float progress = (stroke[i].x - min) / dx;
				LerpColor(&stroke[i].color, &props.stroke_color[0], &props.stroke_color[1], progress);
			}
		}
		else if(props.properties[PP_STROKE_STYLE] == SS_LINE_GRAD_Y)
		{
			float min = (std::numeric_limits<float>::max)();
			float max = (std::numeric_limits<float>::min)();
			for(size_t i = 0; i != strokesize; ++i)
			{
				if(stroke[i].y < min) min = stroke[i].y;
				if(stroke[i].y > max) max = stroke[i].y;
			}

			float dy = max - min;

			for(size_t i = 0; i != strokesize; ++i)
			{
				float progress = (stroke[i].y - min) / dy;
				LerpColor(&stroke[i].color, &props.stroke_color[0], &props.stroke_color[1], progress);
			}
		}*/
	}

	//////////////////////////////////////////////////////////////////////////


	void StrokeTessellator::UpdateState(size_t point)
	{
		special = (PathCommand)-1;
		while(currentCommand < lines->styleStops.size() && lines->styleStops[currentCommand].first == point)
		{
			PathCommand cmd = lines->styleStops[currentCommand].second;

			if(cmd > _JOIT_STYLE_TOP)	
				props.properties[PP_DEFAULT_ENDING] = cmd;
			else if(cmd == PC_CLOSE || cmd == PC_MOVE)
				special = cmd;
			else
				props.properties[PP_DEFAULT_JOINT] = cmd;

			++currentCommand;
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace