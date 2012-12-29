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
#include "../Core.Time/IInterpolator.h"

using namespace Core::SCOM;
using namespace Time;
using namespace Engine;
using namespace Graphics;

#include "../Engine.Common/RenderTraverser.h"

class NOVTABLE CTestGame : 
	public Common::CApplication
{
	friend class SpatialCallback;
public:
	DECLARE_IMPLEMENTATIONA(CTestGame, VML::AlignedAllocator)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(IUnknown)
		INTERFACE_ENTRY_CHAIN(CApplication)
	END_INTERFACE_MAP()

	~CTestGame();

	void	Initialize(IMainLoop *pMainLoop);
	void	SetupScene();
	void	ProcessInput(double frameDelta);
	void	Render(double frameDelta);
	void	DrawFSQuad(int pass = -1);

private:

	RenderingTraverser		mRenderTraverser;
	IEntity*				mCamera;
	IEntity*				mObject;

	ComPtr<IMesh>			sky_model;
	ComPtr<IMesh>			scene_model;
	ComPtr<IMesh>			object_model;
	ComPtr<IMesh>			text_model;

	// G-Buffer
	ComPtr<ITexture>		gbuf_depth;
	ComPtr<ITexture>		gbuf_normal;

	// Light accumulation texture
	ComPtr<ITexture>		acc_lighting;
	ComPtr<IMaterial>		mat_accumulation;

	ComPtr<IRenderTarget>	back_buffer;

	IInterpolatorVec3* itp;
	IInterpolatorQuat* orient;
};

#endif	// _CTESTGAME_H__