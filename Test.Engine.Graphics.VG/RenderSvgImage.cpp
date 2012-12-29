#include "RenderSvgImage.h"
#include "Svg2VG_Converter.h"
#include "PathCounter.h"

#include "main.h"

#include "../Engine.UI.SVG/SvgDocument.h"

#include <vector>

void RenderSvgImage()
{
	const char *  image = "../Resources/SVG/tiger.svg";

	Engine::UI::SVG::SvgDocument doc(image);

	Svg2VG_Converter conv;	
	doc.Accept(&conv);

	for(std::vector<PathData>::iterator it = conv.Datas().begin(); it != conv.Datas().end(); it++)
	{
		IPath* path = g_layer->AddNewComponent();
		IPathBuffer* buf = path->getPathBuffer();

		buf->setCommands(&it->Commands()[0], it->Commands().size());
		buf->setPoints(&it->Points()[0], it->Points().size());

		path->setProperty(PP_STROKE_STYLE, it->StrokeStyle());
		if(it->StrokeStyle() != VG::SS_NONE)
			path->setProperty(PP_STROKE_COLOR1, it->StrokeColor());
		
		path->setProperty(PP_FILL_STYLE, it->FillStyle());
		if(it->FillStyle() != VG::FS_NONE)
			path->setProperty(PP_FILL_COLOR1, it->FillColor());
	}
}
