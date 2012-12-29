/*========================================================
* Svg2VG_Converter.h
* @author Roman Prikhodcheko
* @date 22 May 2009
=========================================================*/
#ifndef _SVG2VG_CONVERTER_H_
#define _SVG2VG_CONVERTER_H_

#include "../Engine.UI.SVG/SvgVisitor.h"
#include "../Engine.UI.SVG/SvgStyle.h"
#include "CommonTypes.h"
//

struct Color;

/// Svg2VG_Converter class
/** Converts svg path commands to VG path commands */
class Svg2VG_Converter : public Engine::UI::SVG::SvgVisitor
{
public:

	/// Visit svg path
	virtual bool Visit(Engine::UI::SVG::SvgPath* path);

	 std::vector<PathData>& Datas() ;

private:
	
	unsigned long GetColor(const Engine::UI::SVG::Color color, int opacity);
	std::string GetChanelColorString(int value);
	std::vector<PathData> m_datas;
};

#endif	// _SVG2VG_CONVERTER_H_
