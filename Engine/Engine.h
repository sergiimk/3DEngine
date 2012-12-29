/*========================================================
* Engine.h
* @author Sergey Mikhtonyuk
* @date 12 December 2008
=========================================================*/
/** @defgroup Engine Engine 
 *  Engine binds all system components together */
#ifndef _ENGINE_H__
#define _ENGINE_H__

//////////////////////////////////////////////////////////////////////////
#include "Interfaces/GlobalEnvironment.h"
#include "Interfaces/IEngine.h"
#include "Interfaces/IMainLoop.h"
#include "Interfaces/IFrameListener.h"
//////////////////////////////////////////////////////////////////////////
#include "Interfaces/IComponentRegistry.h"
#include "Interfaces/ISceneManager.h"
#include "Interfaces/IPhysicsManager.h"
#include "Interfaces/ILogicController.h"
#include "Interfaces/IAnimationController.h"
#include "Interfaces/ITransformGraph.h"
#include "Interfaces/ITransformTraverser.h"
#include "Interfaces/IEntity.h"
#include "Interfaces/ICmpAppearance.h"
#include "Interfaces/ICmpPhysicalBody.h"
#include "Interfaces/ICmpSpatialNode.h"
#include "Interfaces/ICmpLogic.h"
#include "Interfaces/SEntitySpawnParams.h"
//////////////////////////////////////////////////////////////////////////

// {e2800685-9262-4152-a0c5-bcd0cdadbba0} 
static const Core::SCOM::GUID CLSID_CEngine = { 0xe2800685, 0x9262, 0x4152, { 0xa0, 0xc5, 0xbc, 0xd0, 0xcd, 0xad, 0xbb, 0xa0 } };

//////////////////////////////////////////////////////////////////////////

#endif // _ENGINE_H__