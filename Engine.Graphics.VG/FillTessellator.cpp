/*========================================================
* FillTessellator.cpp
* @author Sergey Mikhtonyuk
* @date 17 April 2009
=========================================================*/
#include "FillTessellator.h"
#include <cassert>
#include <limits>

namespace VG
{	
	//////////////////////////////////////////////////////////////////////////

	void FillTessellator::Tessellate()
	{
		if(props.properties[PP_FILL_STYLE] == FS_NONE || !lines->points.size())
			return;

		const size_t nVerts = (lines->points.size() - 2) * 3;
		if(fill.size() < nVerts)
			fill.reserve(nVerts << 1);

		fill.start_update();
		TessellateFill();
		InterpolateFillColor();
		fill.end_update();
	}

	//////////////////////////////////////////////////////////////////////////

	void FillTessellator::TessellateFill()
	{
		/// \todo optimize to triangle strip?
		const size_t nPoints = lines->points.size();
		const size_t nVerts = (nPoints - 2) * 3;
		const size_t ssSize = lines->styleStops.size();

		currentCommand = 0;

		VGVertex refPoint = VGVertex(lines->points[0], props.properties[PP_FILL_COLOR1]);
		while(currentCommand < ssSize && lines->styleStops[currentCommand].first < 2) ++currentCommand;

		for(int i = 0; i != nPoints - 2; ++i)
		{
			while(currentCommand < ssSize && lines->styleStops[currentCommand].first == i + 2)
			{
				if(lines->styleStops[currentCommand].second == PC_MOVE)
				{
					i += 2;
					refPoint = VGVertex(lines->points[i], props.properties[PP_FILL_COLOR1]);
				}

				++currentCommand;
			}

			AddPoint(refPoint);
			AddPoint(VGVertex(lines->points[i + 1], props.properties[PP_FILL_COLOR1]));
			AddPoint(VGVertex(lines->points[i + 2], props.properties[PP_FILL_COLOR1]));
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void FillTessellator::InterpolateFillColor()
	{
		if(props.properties[PP_FILL_STYLE] == FS_GRAD_X)
		{
			float min = (std::numeric_limits<float>::max)();
			float max = (std::numeric_limits<float>::min)();

			size_t fs = fill.size();
			for(size_t i = 0; i != fs; ++i)
			{
				if(fill[i].x < min) min = fill[i].x;
				if(fill[i].x > max) max = fill[i].x;
			}

			float dx = max - min;

			for(size_t i = 0; i != fs; ++i)
			{
				float progress = (fill[i].x - min) / dx;
				LerpColor(fill[i].color, props.properties[PP_FILL_COLOR1], props.properties[PP_FILL_COLOR2], progress);
			}
		}
		else if(props.properties[PP_FILL_STYLE] == FS_GRAD_Y)
		{
			float min = (std::numeric_limits<float>::max)();
			float max = (std::numeric_limits<float>::min)();

			size_t fs = fill.size();
			for(size_t i = 0; i != fs; ++i)
			{
				if(fill[i].y < min) min = fill[i].y;
				if(fill[i].y > max) max = fill[i].y;
			}

			float dy = max - min;

			for(size_t i = 0; i != fs; ++i)
			{
				float progress = (fill[i].y - min) / dy;
				LerpColor(fill[i].color, props.properties[PP_FILL_COLOR1], props.properties[PP_FILL_COLOR2], progress);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace