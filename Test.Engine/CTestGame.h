/*========================================================
* CTestGame.h
* @author Sergey Mikhtonyuk
* @date 15 May 2009
=========================================================*/
#ifndef _CTESTGAME_H__
#define _CTESTGAME_H__

#include "../Engine.Common/CApplication.h"
#include "../Engine.Graphics/Graphics.h"
#include "../Core.COM/Intellectual.h"

using namespace Core::SCOM;
using namespace Engine;
using namespace Graphics;

#include "../Engine.Common/RenderTraverser.h"

#define NUM_TONEMAP_TEXTURES 4

class NOVTABLE CTestGame : 
	public Common::CApplication
{
public:
	DECLARE_IMPLEMENTATION(CTestGame)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(IUnknown)
		INTERFACE_ENTRY_CHAIN(CApplication)
	END_INTERFACE_MAP()

	~CTestGame();

	void	Initialize(IMainLoop *pMainLoop);
	void	SetupScene();
	void	ProcessInput(double frameDelta);
	void	Render(double frameDelta);
	void	DrawFSQuad(int pass = -1 /*-1 == all*/);
	void	CreateShapeFromMesh(IMesh* mesh, NxActorDesc* actor);

private:

	IEntity*				mCamera;
	
	ComPtr<ITexture>		hdrScene;
	ComPtr<ITexture>		hdrSceneDS4;
	ComPtr<ITexture>		hdrBrightPass;
	ComPtr<ITexture>		hdrLuminanceAdaptedLast;
	ComPtr<ITexture>		hdrLuminanceAdaptedNew;
	ComPtr<ITexture>		hdrToneMaps[NUM_TONEMAP_TEXTURES];
	ComPtr<ITexture>		hdrBloom[2];

	ComPtr<IMaterial>		matSceneDS4;
	ComPtr<IMaterial>		matLuminance;
	ComPtr<IMaterial>		matFinal;

	ComPtr<IRenderTarget>	back_buf;
	ComPtr<IMesh>			sky_model;
	ComPtr<IMesh>			terrain_model;
	ComPtr<IMesh>			box_model;
};

#endif	// _CTESTGAME_H__