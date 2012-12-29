/*========================================================
* CTestGame.cpp
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#include "CTestGame.h"
#include "SpatialCallback.h"
#include "EarthLogic.h"
#include "../Engine/Interfaces/EginePlugin.h"

//////////////////////////////////////////////////////////////////////////

void CTestGame::Initialize(Engine::IMainLoop *pMainLoop)
{
	// Base
	CApplication::Initialize(pMainLoop);

	// Register earth logic component
	gEnv->ComponentRegistry->RegisterComponent(EnginePlugin::Instance->PluginShadow(), CLSID_CEarthLogic);

	// Cache the back buffer pointer
	back_buffer = gEnv->Renderer->GetRenderTarget(0);

	// Create render textures for G-Buffer
	SSurfaceDesc sdesc = *back_buffer->GetSurfaceParams();;
	sdesc.Type = SFC_RENDERTARGET;

	sdesc.Format = FMT_R32F;
	gEnv->SurfaceManager->CreateNewTexture(sdesc, gbuf_depth.wrapped());
	gbuf_depth->AddUser();

	sdesc.Format = FMT_A2R10G10B10;
	gEnv->SurfaceManager->CreateNewTexture(sdesc, gbuf_normal.wrapped());
	gbuf_normal->AddUser();

	// Create light accumulation buffer
	sdesc.Format = FMT_A16B16G16R16F;
	gEnv->SurfaceManager->CreateNewTexture(sdesc, acc_lighting.wrapped());
	acc_lighting->AddUser();

	// Create material for light accumulation
	IEffect* pEffect; SMaterialBindings* bindings;
	gEnv->EffectManager->FindOrLoadEffect(Utils::URL("acc_uberlight.fxd"), &pEffect);
	gEnv->MaterialManager->CreateMaterial(mat_accumulation.wrapped());
	bindings = mat_accumulation->GetBindings();
	bindings->addTextureBinding(FXP_TEXTURE_DEPTH, gbuf_depth);
	bindings->addTextureBinding(FXP_TEXTURE_NORMAL, gbuf_normal);
	mat_accumulation->SetEffect(0, pEffect);
	pEffect->Release();
	pEffect = 0;

	mat_accumulation->AddUser();

	SetupScene();
}

//////////////////////////////////////////////////////////////////////////

CTestGame::~CTestGame()
{
	mat_accumulation->RemoveUser();

	gbuf_depth->RemoveUser();
	gbuf_normal->RemoveUser();
	acc_lighting->RemoveUser();

	earth_model->RemoveUser();
	sky_model->RemoveUser();
}

//////////////////////////////////////////////////////////////////////////
static RenderingTraverser		mRenderTraverser;

void CTestGame::SetupScene()
{
	//////////////////////////////////////////////////////////////////////////
	// Earth
	gEnv->GeometryManager->CreateSphere(100, 100, 20.0f, earth_model.wrapped());
	earth_model->AddUser();

	IMaterial* pMaterial;
	gEnv->MaterialManager->FindOrLoadMaterial(Utils::URL("earth.mt"), &pMaterial);
	earth_model->GetSubset(0)->SetMaterial(pMaterial);
	pMaterial->Release();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Skybox
	gEnv->GeometryManager->CreateBox(VML::Vector3(-1, -1, -1), VML::Vector3(1, 1, 1), sky_model.wrapped());
	sky_model->AddUser();

	gEnv->MaterialManager->FindOrLoadMaterial(Utils::URL("skybox_space.mt"), &pMaterial);
	sky_model->GetSubset(0)->SetMaterial(pMaterial);
	pMaterial->Release();
	//////////////////////////////////////////////////////////////////////////

	// Spawning entities
	SEntitySpawnParams params;
	SAppearanceDesc appdesc;
	SSpatialNodeDesc spatialdesc;

	params.Name = "sky";
	appdesc.Mesh = sky_model;
	params.ComponentDescs.push_back(&appdesc);
	params.ComponentDescs.push_back(&spatialdesc);

	IEntity* sky;
	gEnv->SceneManager->CreateEntity(params, &sky);

	//////////////////////////////////////////////////////////////////////////
	params.ResetDefaults(); appdesc.ResetDefaults(); spatialdesc.ResetDefaults();

	SLogicDescBase logicdesc(&CLSID_CEarthLogic, THINK_EACH_FRAME);

	params.Name = "earth";
	appdesc.Mesh = earth_model;
	params.ComponentDescs.push_back(&appdesc);
	params.ComponentDescs.push_back(&spatialdesc);
	params.ComponentDescs.push_back(&logicdesc);

	IEntity* earth;
	gEnv->SceneManager->CreateEntity(params, &earth);

	//////////////////////////////////////////////////////////////////////////
	params.ResetDefaults(); appdesc.ResetDefaults(); spatialdesc.ResetDefaults();

	params.Name = "camera";
	appdesc.Mesh = 0;
	spatialdesc.Position = VML::Vector3(0, 0, -75);
	params.ComponentDescs.push_back(&appdesc);
	params.ComponentDescs.push_back(&spatialdesc);

	gEnv->SceneManager->CreateEntity(params, &mCamera);

	// Form transform graph
	ICmpSpatialNode* sn1 = (ICmpSpatialNode*)earth->getComponent(UUIDOF(ICmpSpatialNode));
	ICmpSpatialNode* sn2 = (ICmpSpatialNode*)sky->getComponent(UUIDOF(ICmpSpatialNode));
	sn1->AttachTo(sn2);

	gEnv->TransformGraph->setRoot(sn2);

	// Add callback to handle spatial queries
	SpatialCallback* sc;
	scom_new<SpatialCallback>(&sc);
	sc->mGame = this;
	gEnv->Renderer->GetMaterialCallback()->setNextCallback(sc);
	sc->Release();

	mRenderTraverser.camera = mCamera;
}

//////////////////////////////////////////////////////////////////////////

void CTestGame::Render(double frameDelta)
{
	// Setup G-Buffer
	gEnv->Renderer->SetRenderTarget(0, gbuf_depth->GetRenderTarget());
	gEnv->Renderer->SetRenderTarget(1, gbuf_normal->GetRenderTarget());

	// Clearing the surfaces
	gEnv->Renderer->Clear(SRFC_CLEAR_COLOR| SRFC_CLEAR_DEPTH | SRFC_CLEAR_STENCIL);

	if(gEnv->Renderer->BeginFrame())
	{
		// Setup view & projection matrices
		mRenderTraverser.Setup();

		// Render scene to G-Buffer
		mRenderTraverser.stage = 0;
		gEnv->TransformGraph->AcceptTraverser(&mRenderTraverser);

		// Setup accumulation buffer
		gEnv->Renderer->SetRenderTarget(1, 0);
		gEnv->Renderer->SetRenderTarget(0, acc_lighting->GetRenderTarget());
		gEnv->Renderer->Clear(SRFC_CLEAR_COLOR);

		// Render fs quad to accumulation buffer (ambient + directional)
		gEnv->Renderer->SetMaterial(mat_accumulation);
		DrawFSQuad();

		// Render scene and apply lighting
		gEnv->Renderer->SetRenderTarget(0, back_buffer);

		mRenderTraverser.stage = 1;
		gEnv->TransformGraph->AcceptTraverser(&mRenderTraverser);


		// Pop view & projection matrices
		mRenderTraverser.TearDown();
		gEnv->Renderer->EndFrame();
	}
}

//////////////////////////////////////////////////////////////////////////

void CTestGame::DrawFSQuad(int pass)
{
	IEffectInstance* effect = gEnv->Renderer->GetEffectInstance();
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

	if(gEnv->InputController->IsKeyPressed(Input::KC_F))
	{
		gEnv->Renderer->GetRendererParams()->FullScreen = !gEnv->Renderer->GetRendererParams()->FullScreen;
		gEnv->Renderer->Reset();
	}
}

//////////////////////////////////////////////////////////////////////////