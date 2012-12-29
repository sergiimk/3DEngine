#include "../Engine.UI.SVG/SvgDocument.h"
#include "../Engine.UI.SVG/SvgGroup.h"
#include "../Engine.UI.SVG/SvgPath.h"
#include "../Engine.UI.SVG/SvgException.h"


#define BOOST_TEST_MODULE Test module name
#include <boost/test/unit_test.hpp>

using Engine::UI::SVG::SvgObject;
using Engine::UI::SVG::SvgDocument;
using Engine::UI::SVG::SvgGroup;
using Engine::UI::SVG::SvgPath;
using Engine::UI::SVG::SvgStyle;
using Engine::UI::SVG::SvgPathItem;
using Engine::UI::SVG::SvgPoint;
using Engine::UI::SVG::SVG_FILL_STYLE;
using Engine::UI::SVG::SVG_STROKE_STYLE;
using Engine::UI::SVG::SvgException;


BOOST_AUTO_TEST_SUITE( ParserTest );

BOOST_AUTO_TEST_CASE( TreeTest )
{
	// Unit test logic
	SvgDocument doc("../Resources/Svg/tig.svg");

	//SvgDocument * d1 = new SvgDocument("../Resources/Svg/tig.svg");
	//delete d1;

	BOOST_CHECK( doc.Children().size() == 2 );
	
	SvgObject* ch1 = doc.Children()[0];
	BOOST_CHECK( dynamic_cast<SvgGroup*>(ch1) );

	BOOST_CHECK( ((SvgGroup*)ch1)->Children().size() == 1 );

	SvgObject* ch2 = static_cast<SvgGroup*>(ch1)->Children()[0];
	BOOST_CHECK( dynamic_cast<SvgPath*>(ch2) );

	SvgPath* p1 = static_cast<SvgPath*>(ch2);
	BOOST_CHECK ( p1->Items().size() == 5 );
}

BOOST_AUTO_TEST_CASE( CoordinatesTest )
{
	// Unit test logic
	SvgDocument doc("../Resources/Svg/tig.svg");

	SvgGroup* gr1 = static_cast<SvgGroup*>(doc.Children()[0]);
	SvgPath* p1  = static_cast<SvgPath*>(gr1->Children()[0]);

	std::vector<SvgPathItem*> items = p1->Items();

	SvgPathItem item1 = *items[0];

	BOOST_CHECK( item1.Type() == Engine::UI::SVG::SVG_MOVETO);

	const std::vector<SvgPoint> points = item1.Coordinates();

	SvgPoint point1 = points[0];

	BOOST_CHECK ( point1.x == -118.774 && point1.y == 81.262 );
}

BOOST_AUTO_TEST_CASE( StyleTest )
{
	// Unit test logic
	SvgDocument doc("../Resources/Svg/tig.svg");

	// Testing simple properties
	SvgGroup* gr1 = static_cast<SvgGroup*>(doc.Children()[0]);
	SvgStyle st1 = gr1->Style();

	BOOST_CHECK( st1.Opacity() == 1 );

	// Testing parsing color-strings in "rgb(r, g, b)" format
	Engine::UI::SVG::Color col1 = st1.FillColor();
	BOOST_CHECK ( col1.Red == 23 && col1.Green == 24 && col1.Blue == 25 );

	Engine::UI::SVG::Color col2 = st1.StrokeColor();
	BOOST_CHECK ( col2.Red == 242 && col2.Green == 167 && col2.Blue == 78 );

	// Testing overrided styles
	SvgPath* p1= static_cast<SvgPath*>(gr1->Children()[0]);
	SvgStyle st2 = p1->Style();

	BOOST_CHECK( st2.Opacity() == 0.5 );

	Engine::UI::SVG::Color col3 = st2.FillColor();
	BOOST_CHECK( col3.Red == 23 && col3.Green == 24 && col3.Blue == 25  );

	// Testing "none" color values parsing
	SvgGroup* gr2 = dynamic_cast<SvgGroup*>(doc.Children()[1]);
	SvgStyle st3 = gr2->Style();
	
	// Testing "none" color values parsing for fill
	BOOST_CHECK( st3.FillStyle() == Engine::UI::SVG::FS_NONE );
	
	// Testing "none" color values parsing for stroke
	BOOST_CHECK( st3.StrokeStyle() == Engine::UI::SVG::SS_NONE );

	// Testing throwing of exceptiuons when none values occure
	// Fill color
	try
	{
		Engine::UI::SVG::Color col4 = st3.FillColor();
		throw;
	}
	catch(SvgException ex)
	{
	}

	// Stroke color
	try
	{
		Engine::UI::SVG::Color col4 = st3.StrokeColor();
		throw;
	}
	catch(SvgException ex)
	{
	}

}


BOOST_AUTO_TEST_SUITE_END();
