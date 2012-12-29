#include "main.h"

using namespace VG;

void BuildScene()
{
	PathCommand* commands = new PathCommand[4];
	commands[0] = PC_MOVE;
	commands[1] = PC_LINE;
	commands[2] = PC_LINE;
	commands[3] = PC_CLOSE;
	
	PathPoint* points = new PathPoint[3];
	points[0].x = -10;	points[0].y = 0;
	points[1].x = 0;	points[1].y = 10;
	points[2].x = 10;	points[2].y = 0;

	// Last dummy-parameter indicates that Path should wrap provided pointers instead of copying them
	g_layers[0].Components().push_back(new Path(pD3DDevice, commands, 4, points, 3, 0));
	g_layers[0].Components().back()->SetProperty(PP_FILL_STYLE, FS_SOLID);
	g_layers[0].Components().back()->SetProperty(PP_STROKE_STYLE, SS_NONE);
	g_layers[0].Components().back()->FillColor1() = 0xffff0000;
}