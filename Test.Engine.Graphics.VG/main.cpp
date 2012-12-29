#include "main.h"

VML::Vector3 g_cameraPos(0, 0, -600);

float GetTolerance(float dist)
{
	struct pair
	{
		float first, second;
	};

	static pair stops[10] = 
	{
		{ 0.0f,		0.01f },
		{ 100.0f,	0.05f },
		{ 300.0f,	1.0f },
		{ 500.0f,	3.0f },
		{ 800.0f,	8.0f },
		{ 1000.0f,	14.0f },
		{ 1500.0f,	25.0f },
		{ 2000.0f,	100.0f },
		{ 3000.0f,	200.0f },
		{ 4000.0f,	400.0f },
	};

	if(dist <= stops[0].first) return stops[0].second;
	if(dist >= stops[9].first) return stops[9].second;

	for(int i = 1; i != 10; ++i)
	{
		if(dist < stops[i].first)
			return stops[i-1].second + ((dist - stops[i-1].first) / 
			(stops[i].first - stops[i-1].first)) * (stops[i].second - stops[i-1].second);
	}

	throw 1;
}

VOID Render()
{
	pRenderer->Clear(SRFC_CLEAR_COLOR | SRFC_CLEAR_DEPTH | SRFC_CLEAR_STENCIL, 0xfff5f5ff);

	IMatrixStack* world = pRenderer->GetMatrixStack(TRANSFORM_WORLD);
	IMatrixStack* view = pRenderer->GetMatrixStack(TRANSFORM_VIEW);
	IMatrixStack* proj = pRenderer->GetMatrixStack(TRANSFORM_PROJECTION);

	world->Push(VML::Matrix4::identity());
	view->Push(VML::Matrix4::lookAtLH(VML::Point3(g_cameraPos), VML::Point3(0), VML::Vector3::yAxis()));
	proj->Push(VML::Matrix4::perspectiveLH(3.1415f / 4.0f, (float)iWidth / (float)iHeight, 1.0f, 10000.0f));

	g_layer->setToleranceToAll(GetTolerance(g_cameraPos.length()));
	g_layer->RecalculateAll();

	if(pRenderer->BeginFrame())
	{
		g_layer->Render();

		pRenderer->EndFrame();
	}

	world->Pop();
	view->Pop();
	proj->Pop();
}

