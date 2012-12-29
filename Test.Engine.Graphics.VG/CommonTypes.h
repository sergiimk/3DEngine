/*========================================================
* CommonTypes.h
* @author Roman Prikhodcheko
* @date 22 May 2009
=========================================================*/

#ifndef _COMMONTYPES_H_
#define _COMMONTYPES_H_

#include "../Engine.Graphics.VG/VGLib.h"
#include "../Core.Math/VML.h"

using namespace VG;

#include <algorithm>
#include <vector>

/// PathData class.
/** Contains definition of path commands and their coordinates */
class PathData
{
	typedef std::vector<VML::Vector2 > TPointsCont;
	typedef std::vector<PathCommand> TCommandsCont;

public:

	TPointsCont& Points()
	{
		return m_points;
	}

	TCommandsCont& Commands()
	{
		return m_commands;
	}

	VG::FillStyle & FillStyle()
	{
		return m_fillStyle;
	}

	VG::StrokeStyle & StrokeStyle()
	{
		return m_strokeStyle;
	}

	unsigned long & StrokeColor()
	{
		return m_strokeColor;
	}
	
	unsigned long & FillColor()
	{
		return m_fillColor;
	}

private:

	VG::FillStyle m_fillStyle;

	VG::StrokeStyle m_strokeStyle;

	unsigned long m_strokeColor;

	unsigned long m_fillColor;
	
	TPointsCont m_points;
	
	TCommandsCont m_commands;
};

#endif	// _COMMONTYPES_H_
