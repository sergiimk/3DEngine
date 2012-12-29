/*========================================================
* RenderTraverser.h
* @author Sergey Mikhtonyuk
* @date 16 May 2009
=========================================================*/
#ifndef _RENDERTRAVERSER_H__
#define _RENDERTRAVERSER_H__

#include "../Engine/Engine.h"
#include "../Core.Math/VML.h"
#include "../Engine.Graphics/Interfaces/IEffectInstance.h"
using namespace VML;

class RenderingTraverser : public Engine::ITransformTraverser
{
public:
	IEntity* camera;
	Vector3	camRotation;
	Vector3 up;
	Vector3 to;
	bool drawBB;
	size_t stage;
	float zNear, zFar, fov, aspect;

	RenderingTraverser() : camRotation(0), drawBB(false), stage(0), 
		zNear(1.0f), zFar(500.0f), fov(3.1415f / 3.2f), aspect(4.0f / 3.0f)
	{
	}

	void Setup()
	{
		Transform3 rot = Transform3::rotationZYX(camRotation);
		ICmpSpatialNode* csn = (ICmpSpatialNode*)camera->getComponent(UUIDOF(ICmpSpatialNode));
		csn->setRotation(	Quat::rotationZ(camRotation.getZ()) * 
			Quat::rotationY(camRotation.getY()) * 
			Quat::rotationX(camRotation.getX()));

		up = rot * Vector3::yAxis();
		to = rot * Vector3::zAxis();

		Point3 pto = Point3(csn->getPosition() + to);

		Matrix4 view = Matrix4::lookAtLH( Point3(csn->getPosition()), pto, up);
		Matrix4 proj = Matrix4::perspectiveLH(fov, aspect, zNear, zFar);

		gEnv->Renderer->GetMatrixStack(Engine::Graphics::TRANSFORM_VIEW)->Push(view);
		gEnv->Renderer->GetMatrixStack(Engine::Graphics::TRANSFORM_PROJECTION)->Push(proj);
	}

	void TearDown()
	{
		gEnv->Renderer->GetMatrixStack(Engine::Graphics::TRANSFORM_PROJECTION)->Pop();
		gEnv->Renderer->GetMatrixStack(Engine::Graphics::TRANSFORM_VIEW)->Pop();
	}

	void TraversingStarted(ITransformGraph* tg) 
	{		
	}

	void TraversingEnd(ITransformGraph* tg)
	{		
	}

	bool VisitNode(ICmpSpatialNode* node, IEntity* entity)
	{
		ICmpAppearance* app = (ICmpAppearance*)entity->getComponent(UUIDOF(ICmpAppearance));
		ICmpSpatialNode* sn = (ICmpSpatialNode*)entity->getComponent(UUIDOF(ICmpSpatialNode));

		if(!app) return true;
		assert(sn->getState() == NODE_UP_TO_DATE);

		IMesh* mesh = app->getMesh();
		if(!mesh) return true;

		IMatrixStack* MSWorld = gEnv->Renderer->GetMatrixStack(Engine::Graphics::TRANSFORM_WORLD);
		MSWorld->Push(sn->getTransform());

		gEnv->Renderer->SetGeometryBuffer(mesh);

		for(int i = 0; i != mesh->GetSubsetCount(); ++i)
		{
			IMaterial* mat = mesh->GetSubset(i)->GetMaterial();

			gEnv->Renderer->SetMaterial(mat, stage);
			IEffectInstance* effect = gEnv->Renderer->GetEffectInstance();
			
			if(!effect) 
				continue;

			unsigned int npass = effect->BeginSequence();
			for(unsigned int p = 0; p != npass; ++p)
			{
				effect->BeginPass(p);
				gEnv->Renderer->DrawGeometry(mesh->GetSubset(i));
				effect->EndPass();
			}
			effect->EndSequence();
		}

		if(drawBB) gEnv->Renderer->DbgDrawBBox(mesh->GetBoundingVolume(), VML::Vector4(0, 1, 0, 1));

		MSWorld->Pop();
		return true;
	}

	void LeaveNode(ICmpSpatialNode* node, IEntity* entity)	{ }
};


#endif	// _RENDERTRAVERSER_H__