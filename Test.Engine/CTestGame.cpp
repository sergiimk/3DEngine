/*========================================================
* CTestGame.cpp
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#include "CTestGame.h"
#include "SpatialCallback.h"

#include <NxPhysics.h>
#include <NxCooking.h>
#include "../Engine/Utils/PhysXFileStream.h"

//////////////////////////////////////////////////////////////////////////

void CTestGame::Initialize(Engine::IMainLoop *pMainLoop)
{
	// Base
	CApplication::Initialize(pMainLoop);

	// Cache back buffer
	back_buf = gEnv->Renderer->GetRenderTarget(0);

	// Create offscreen surfaces for HDR rendering
	
	// Base FP texture
	SSurfaceDesc sdesc = *back_buf->GetSurfaceParams();
	sdesc.Type = SFC_RENDERTARGET;
	sdesc.Format = FMT_A16B16G16R16F;
	gEnv->SurfaceManager->CreateNewTexture(sdesc, hdrScene.wrapped());

	// 4x Downscaled scene
	sdesc.Height /= 4;
	sdesc.Width /= 4;
	gEnv->SurfaceManager->CreateNewTexture(sdesc, hdrSceneDS4.wrapped());
	hdrSceneDS4->AddUser();

	// Bright pass texture
	gEnv->SurfaceManager->CreateNewTexture(sdesc, hdrBrightPass.wrapped());
	hdrBrightPass->AddUser();

	// Textures that holds a previous and current adapted luminance
	sdesc.Format = FMT_R16F;
	sdesc.Height = sdesc.Width = 1;
	gEnv->SurfaceManager->CreateNewTexture(sdesc, hdrLuminanceAdaptedLast.wrapped());
	gEnv->SurfaceManager->CreateNewTexture(sdesc, hdrLuminanceAdaptedNew.wrapped());
	hdrLuminanceAdaptedLast->AddUser();
	hdrLuminanceAdaptedNew->AddUser();

	// For each scale stage, create a texture to hold the intermediate results
	// of the luminance calculation
	for(int i = 0; i < NUM_TONEMAP_TEXTURES; i++ )
	{
		sdesc.Height = sdesc.Width = 1 << ( 2 * i );

		gEnv->SurfaceManager->CreateNewTexture(sdesc, hdrToneMaps[i].wrapped());
		hdrToneMaps[i]->AddUser();
	}


	// Create materials and effect
	IEffect* ppEffect;
	SMaterialBindings* bindings;
	gEnv->EffectManager->FindOrLoadEffect(Utils::URL("HDR/hdr_downscale4.fxd"), &ppEffect);
	gEnv->MaterialManager->CreateMaterial(matSceneDS4.wrapped());
	bindings = matSceneDS4->GetBindings();
	bindings->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrScene);
	matSceneDS4->SetEffect(0, ppEffect);
	ppEffect->Release();
	ppEffect = 0;

	gEnv->EffectManager->FindOrLoadEffect(Utils::URL("HDR/hdr_luminance.fxd"), &ppEffect);
	gEnv->MaterialManager->CreateMaterial(matLuminance.wrapped());
	bindings = matLuminance->GetBindings();
	bindings->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrSceneDS4);
	matLuminance->SetEffect(0, ppEffect);
	ppEffect->Release();
	ppEffect = 0;

	gEnv->EffectManager->FindOrLoadEffect(Utils::URL("HDR/hdr_final.fxd"), &ppEffect);
	gEnv->MaterialManager->CreateMaterial(matFinal.wrapped());
	bindings = matFinal->GetBindings();
	bindings->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrScene);
	matFinal->SetEffect(0, ppEffect);
	ppEffect->Release();
	ppEffect = 0;

	matSceneDS4->AddUser();
	matLuminance->AddUser();
	matFinal->AddUser();

	SetupScene();
}

//////////////////////////////////////////////////////////////////////////

CTestGame::~CTestGame()
{
	box_model->RemoveUser();
	sky_model->RemoveUser();
	terrain_model->RemoveUser();

	matSceneDS4->RemoveUser();
	hdrBrightPass->RemoveUser();
	matLuminance->RemoveUser();
	matFinal->RemoveUser();
	
	hdrSceneDS4->RemoveUser();
	for(int i = 0; i < NUM_TONEMAP_TEXTURES; i++ )
		hdrToneMaps[i]->RemoveUser();

	hdrLuminanceAdaptedLast->RemoveUser();
	hdrLuminanceAdaptedNew->RemoveUser();
}

//////////////////////////////////////////////////////////////////////////
static RenderingTraverser		mRenderTraverser;

void CTestGame::SetupScene()
{
	//////////////////////////////////////////////////////////////////////////
	// Skybox
	gEnv->GeometryManager->CreateBox(VML::Vector3(-1, -1, -1), VML::Vector3(1, 1, 1), sky_model.wrapped());
	sky_model->AddUser();

	IMaterial* pMaterial;
	gEnv->MaterialManager->FindOrLoadMaterial(Utils::URL("skybox_stormy.mt"), &pMaterial);
	sky_model->GetSubset(0)->SetMaterial(pMaterial);
	pMaterial->Release();

	//////////////////////////////////////////////////////////////////////////
	// Terrain model
	gEnv->GeometryManager->FindOrLoadMesh(Utils::URL("columns.md"),  terrain_model.wrapped());
	terrain_model->AddUser();

	//////////////////////////////////////////////////////////////////////////
	// Boxes
	gEnv->GeometryManager->CreateBox(VML::Vector3(-2, -2, -2), VML::Vector3(2, 2, 2), box_model.wrapped());
	box_model->AddUser();

	gEnv->MaterialManager->FindOrLoadMaterial(Utils::URL("crate.mt"), &pMaterial);
	box_model->GetSubset(0)->SetMaterial(pMaterial);
	pMaterial->Release();

	//////////////////////////////////////////////////////////////////////////
	// Spawning entities
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	SEntitySpawnParams params;
	SAppearanceDesc appdesc;
	SSpatialNodeDesc spatialdesc;
	SPhysicalBodyDesc physdesc;

	//////////////////////////////////////////////////////////////////////////
	params.Name = "sky";
	appdesc.Mesh = sky_model;
	params.ComponentDescs.push_back(&appdesc);
	params.ComponentDescs.push_back(&spatialdesc);

	IEntity* sky;
	gEnv->SceneManager->CreateEntity(params, &sky);
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	params.ResetDefaults(); appdesc.ResetDefaults(); spatialdesc.ResetDefaults();
	params.Name = "terrain";
	appdesc.Mesh = terrain_model;

	NxActorDesc scene_actor;
	scene_actor.name = "scene";

	NxTriangleMeshShapeDesc shape;
	shape.meshData = gEnv->PhysX->createTriangleMesh(PhysXFileStream("../Resources/Meshes/Geometry/columns.phx", true));
	scene_actor.shapes.push_back(&shape);

	/*NxTriangleMeshDesc meshdesc;
	meshdesc.numVertices = terrain_model->GetVertexCount();
	meshdesc.numTriangles = terrain_model->GetFacesCount();

	terrain_model->LockVertexBuffer((void**)&meshdesc.points);
	meshdesc.pointStrideBytes = terrain_model->GetVertexSize();

	terrain_model->LockIndexBuffer((void**)&meshdesc.triangles);
	meshdesc.triangleStrideBytes = sizeof(NxU16) * 3;

	meshdesc.flags = NX_CF_16_BIT_INDICES;
	ASSERT_STRICT(meshdesc.isValid());

	bool s = gEnv->PhysXCooking->NxCookTriangleMesh(meshdesc, PhysXFileStream("c:/cooked.bin", false));

	terrain_model->UnlockVertexBuffer();
	terrain_model->UnlockIndexBuffer();*/

	//CreateShapeFromMesh(terrain_model, &scene_actor);
	physdesc.ActorDescs = &scene_actor;
	params.ComponentDescs.push_back(&appdesc);
	params.ComponentDescs.push_back(&spatialdesc);
	params.ComponentDescs.push_back(&physdesc);


	IEntity* terrain;
	gEnv->SceneManager->CreateEntity(params, &terrain);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	params.ResetDefaults(); spatialdesc.ResetDefaults(); physdesc.ResetDefaults();

	NxActorDesc cameraActor;
	NxBodyDesc cameraBody;
	cameraBody.mass = 10;
	cameraActor.body = &cameraBody;
	NxSphereShapeDesc cameraShape;
	cameraShape.radius = 5.0f;
	cameraActor.shapes.push_back(&cameraShape);
	params.Name = "camera";
	spatialdesc.Position = VML::Vector3(0, 5, 0);
	physdesc.ActorDescs = &cameraActor;
	ASSERT_STRICT(cameraActor.isValid());

	params.ComponentDescs.push_back(&spatialdesc);
	params.ComponentDescs.push_back(&physdesc);

	gEnv->SceneManager->CreateEntity(params, &mCamera);
	((ICmpPhysicalBody*)mCamera->getComponent(UUIDOF(ICmpPhysicalBody)))->getActor()->raiseBodyFlag(NX_BF_KINEMATIC);
	//////////////////////////////////////////////////////////////////////////

	// Form transform graph
	ICmpSpatialNode* sn1 = (ICmpSpatialNode*)terrain->getComponent(UUIDOF(ICmpSpatialNode));
	ICmpSpatialNode* sn2 = (ICmpSpatialNode*)sky->getComponent(UUIDOF(ICmpSpatialNode));
	sn1->AttachTo(sn2);

	sn1 = (ICmpSpatialNode*)mCamera->getComponent(UUIDOF(ICmpSpatialNode));
	sn1->AttachTo(sn2);
	gEnv->TransformGraph->setRoot(sn2);

	mRenderTraverser.camera = mCamera;


	// Create ground plane
	/*NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	gEnv->PhysXScene->createActor(actorDesc);*/

	// Add callback to handle spatial queries
	SpatialCallback* sc;
	scom_new<SpatialCallback>(&sc);
	sc->mCamera = mCamera;
	gEnv->Renderer->GetMaterialCallback()->setNextCallback(sc);
	sc->Release();
}

//////////////////////////////////////////////////////////////////////////

void CTestGame::Render(double frameDelta)
{
	if(gEnv->Renderer->BeginFrame())
	{
		gEnv->Renderer->Clear(SRFC_CLEAR_DEPTH | SRFC_CLEAR_STENCIL, 0xff000000);
		gEnv->Renderer->SetRenderTarget(0, hdrScene->GetRenderTarget());

		gEnv->TransformGraph->AcceptTraverser(&mRenderTraverser);

		// Downscale scene
		gEnv->Renderer->SetRenderTarget(0, hdrSceneDS4->GetRenderTarget());
		gEnv->Renderer->SetMaterial(matSceneDS4);
		DrawFSQuad();

		// Swap current and last luminance textures
		ComPtr<ITexture> swp = hdrLuminanceAdaptedLast;
		hdrLuminanceAdaptedLast = hdrLuminanceAdaptedNew;
		hdrLuminanceAdaptedNew = swp;

		// Compute initial luminance texture
		int curTone = NUM_TONEMAP_TEXTURES - 1;
		matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrSceneDS4);
		matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_SPECULAR, hdrLuminanceAdaptedLast);
		gEnv->Renderer->SetRenderTarget(0, hdrToneMaps[curTone]->GetRenderTarget());
		gEnv->Renderer->SetMaterial(matLuminance);
		DrawFSQuad(0);
		--curTone;

		// Perform iterative luminance downscaling to 4x4 texture
		while(curTone > 0)
		{
			// Set prev texture as source
			matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrToneMaps[curTone + 1]);
			gEnv->Renderer->SetRenderTarget(0, hdrToneMaps[curTone]->GetRenderTarget());
			gEnv->Renderer->SetMaterial(matLuminance);
			DrawFSQuad(1);

			--curTone;
		}

		// Final luminance pass
		matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrToneMaps[1]);
		gEnv->Renderer->SetRenderTarget(0, hdrToneMaps[0]->GetRenderTarget());
		gEnv->Renderer->SetMaterial(matLuminance);
		DrawFSQuad(2);


		// Luminance adaptation
		matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrToneMaps[0]);
		matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_SPECULAR, hdrLuminanceAdaptedLast);
		gEnv->Renderer->SetRenderTarget(0, hdrLuminanceAdaptedNew->GetRenderTarget());
		gEnv->Renderer->SetMaterial(matLuminance);
		DrawFSQuad(3);

		// Bright pass
		/*matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_DIFFUSE, hdrSceneDS4);
		matLuminance->GetBindings()->addTextureBinding(FXP_TEXTURE_SPECULAR, hdrLuminanceAdaptedNew);
		gEnv->Renderer->SetRenderTarget(0, hdrBrightPass->GetRenderTarget());
		gEnv->Renderer->SetMaterial(matLuminance);
		DrawFSQuad(4);*/

		// Final render with tone mapping
		matFinal->GetBindings()->addTextureBinding(FXP_TEXTURE_SPECULAR, hdrLuminanceAdaptedNew);
		gEnv->Renderer->SetRenderTarget(0, back_buf);
		gEnv->Renderer->SetMaterial(matFinal);
		DrawFSQuad();

		gEnv->Renderer->EndFrame();
	}
}

//////////////////////////////////////////////////////////////////////////

void CTestGame::DrawFSQuad(int pass)
{
	IEffectInstance* effect = gEnv->Renderer->GetMaterial()->GetEffectInstance(0);
	unsigned int passes = effect->BeginSequence();

	if(pass == -1)
	{
		for(unsigned int i = 0; i != passes; ++i)
		{
			effect->BeginPass(i);
			gEnv->Renderer->DrawFSQuad();
			effect->EndPass();
		}
	}
	else
	{
		effect->BeginPass(pass);
		gEnv->Renderer->DrawFSQuad();
		effect->EndPass();
	}
	effect->EndSequence();
}

//////////////////////////////////////////////////////////////////////////

float clamp(float f, float min, float max)
{
	return f > max ? max : ( f < min ? min : f );
}

void CTestGame::ProcessInput(double frameDelta)
{
	const float speed = 20.0f;
	// Update camera position
	float dx = gEnv->InputController->GetMouseDX() / 100.0f;
	float dy = gEnv->InputController->GetMouseDY() / 100.0f;
	mRenderTraverser.camRotation.setY(mRenderTraverser.camRotation.getY() + dx);
	mRenderTraverser.camRotation.setX(clamp(mRenderTraverser.camRotation.getX() + dy, -3.1415f / 2.0f, 3.1415f / 2.0f));

	ICmpSpatialNode* csn = (ICmpSpatialNode*)mCamera->getComponent(UUIDOF(ICmpSpatialNode));
	if(gEnv->InputController->IsKeyPressed(Input::KC_W))
		csn->setPosition(csn->getPosition() + mRenderTraverser.to * (float)frameDelta * speed);
	if(gEnv->InputController->IsKeyPressed(Input::KC_S))
		csn->setPosition(csn->getPosition() - mRenderTraverser.to * (float)frameDelta * speed);
	if(gEnv->InputController->IsKeyPressed(Input::KC_A))
		csn->setPosition(csn->getPosition() + cross(mRenderTraverser.to, mRenderTraverser.up) * (float)frameDelta * speed);
	if(gEnv->InputController->IsKeyPressed(Input::KC_D))
		csn->setPosition(csn->getPosition() - cross(mRenderTraverser.to, mRenderTraverser.up) * (float)frameDelta * speed);
	if(gEnv->InputController->IsKeyPressed(Input::KC_SPACE))
		csn->setPosition(csn->getPosition() + mRenderTraverser.up * (float)frameDelta * speed);
	if(gEnv->InputController->IsKeyPressed(Input::KC_LCONTROL))
		csn->setPosition(csn->getPosition() - mRenderTraverser.up * (float)frameDelta * speed);

	if(gEnv->InputController->IsKeyDownEvent(Input::KC_B))
		mRenderTraverser.drawBB = !mRenderTraverser.drawBB;

	if(gEnv->InputController->IsKeyPressed(Input::KC_F))
	{
		gEnv->Renderer->GetRendererParams()->FullScreen = !gEnv->Renderer->GetRendererParams()->FullScreen;
		gEnv->Renderer->Reset();
	}

	static double chill = 0;
	chill += frameDelta;

	if(gEnv->InputController->IsMouseButtonPressed(0))
	{
		if(chill > 0.2f) chill = 0;
		else return;

		// Positioning
		Vector3 position_ = csn->getPosition();
		Quat rotation_ = csn->getRotation();
		Vector3 direction_ = normalize( rotate(rotation_, Vector3::zAxis()) );
		position_ += direction_ * 10;
		Transform3 rotation_mat_ = Transform3::rotation(rotation_);

		NxVec3 position((float* const)&position_.get128());
		NxVec3 velocity((float* const)&direction_.get128());
		velocity *= 20.0f;
		NxMat34 pose;
		pose.setColumnMajor44((float* const)&rotation_mat_);
		pose.t = position;

		
		// Create body
		NxBodyDesc bodyDesc;
		bodyDesc.angularDamping	= 0.5f;
		bodyDesc.linearVelocity = velocity;

		NxBoxShapeDesc boxDesc;
		float size = 2.0f;
		boxDesc.dimensions = NxVec3(size, size, size);

		NxActorDesc actorDesc;
		actorDesc.shapes.pushBack(&boxDesc);
		actorDesc.body			= &bodyDesc;
		actorDesc.density		= 100.0f;
		actorDesc.globalPose	= pose;
		ASSERT_STRICT(actorDesc.isValid());

		//////////////////////////////////////////////////////////////////////////
		SEntitySpawnParams params;
		SAppearanceDesc appdesc;
		SSpatialNodeDesc spatialdesc;
		SPhysicalBodyDesc physdesc;
		params.Name = "box";
		physdesc.ActorDescs = &actorDesc;
		appdesc.Mesh = box_model;
		spatialdesc.Position = position_;
		spatialdesc.Rotation = rotation_;

		params.ComponentDescs.push_back(&appdesc);
		params.ComponentDescs.push_back(&physdesc);
		params.ComponentDescs.push_back(&spatialdesc);


		IEntity* nb;
		gEnv->SceneManager->CreateEntity(params, &nb);
		((ICmpSpatialNode*)nb->getComponent(UUIDOF(ICmpSpatialNode)))->AttachTo(gEnv->TransformGraph->getRoot());
	}
}

//////////////////////////////////////////////////////////////////////////
