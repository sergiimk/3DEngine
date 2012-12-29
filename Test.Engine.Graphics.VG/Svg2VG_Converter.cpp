#include "Svg2VG_Converter.h"
#include "../Engine.UI.SVG/SvgPath.h"
#include "../Engine.Graphics.VG/VGLib.h"

#include <sstream>

using namespace Engine::UI::SVG;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Svg2VG_Converter::Visit(Engine::UI::SVG::SvgPath *path)
{
	PathData data;

	for ( std::vector<SvgPathItem*>::const_iterator it  = path->Items().begin(); it != path->Items().end(); it++)
	{
		////////////////////////////////////////////////////////////
		// TODO: Refactor type conversion
		////////////////////////////////////////////////////////////

		switch( (*it)->Type() )
		{
		case SVG_CUBIC_BEZIER:
			data.Commands().push_back( VG::PC_BEZIER_3);
			break;
		case SVG_QUADRATIC_BEZIER:
			data.Commands().push_back( VG::PC_BEZIER_2);
			break;
		case SVG_LINE:
			data.Commands().push_back( VG::PC_LINE);
			break;
		case SVG_MOVETO:
			data.Commands().push_back( VG::PC_MOVE);
			break;
		case SVG_CLOSE:
			data.Commands().push_back( VG::PC_CLOSE);
			break;
		default:
			throw std::exception();
		}

		for (std::vector<SvgPoint>::const_iterator jt = (*it)->Coordinates().begin(); jt != (*it)->Coordinates().end(); jt++)
		{
			// Adjustments are specific to butterfly
			VML::Vector2 a(jt->x /*- 200.0f*/, -jt->y /*+ 150.f*/);
			data.Points().push_back(a);
		}
	}

	SvgStyle & st = path->Style();

	data.FillStyle() = static_cast<VG::FillStyle>(st.FillStyle());
	if(st.FillStyle() != Engine::UI::SVG::FS_NONE)
	{
		data.FillColor() = GetColor(st.FillColor(), /*(int)(st.Opacity() * 255)*/255);
	}

	data.StrokeStyle() = static_cast<VG::StrokeStyle>(st.StrokeStyle());
	if(st.StrokeStyle() != Engine::UI::SVG::SS_NONE)
	{
		data.StrokeColor() = GetColor(st.StrokeColor(), /*(int)(st.Opacity() * 255)*/255);
	}

	m_datas.push_back(data);
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<PathData>& Svg2VG_Converter::Datas() 
{
	return m_datas;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Svg2VG_Converter::GetChanelColorString(int value)
{
	std::stringstream ss;
	ss << std::hex;
	ss << value;
	std::string str;
	ss >> str;
	
	if (ss.fail())
		throw std::exception();

	if (str.length() == 1)
		str = "0" + str;

	return str;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long Svg2VG_Converter::GetColor(const Engine::UI::SVG::Color color, int opacity)
{
	std::string cStr("");

	cStr += GetChanelColorString(opacity);
	cStr += GetChanelColorString(color.Red);
	cStr += GetChanelColorString(color.Green);
	cStr += GetChanelColorString(color.Blue);

	assert(cStr.length() == 8);

	std::stringstream ss(cStr);
	ss << std::hex;

	unsigned long col = 0;

	ss >> col;

	if (ss.fail())
		throw std::exception();

	return col;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
