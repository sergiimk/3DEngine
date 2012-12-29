/*========================================================
* SekaiCore.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
=========================================================*/
/** @defgroup Core Core 
 *  Core libraries and utilities */

#ifndef _SEKAICORE_H__
#define _SEKAICORE_H__

#include "ICore.h"
#include "IPlugin.h"
#include "IPluginManager.h"
#include "IPluginShadow.h"
#include "IExtension.h"
#include "IStartListener.h"
#include "IExtensionPoint.h"
#include "../Core.Logging/ILogger.h"
#include "CoreExceptions.h"

namespace Core
{
	// {654d7750-4574-4c6a-9393-b5fae3419621} 
	const SCOM::GUID CLSID_CCore = { 0x654d7750, 0x4574, 0x4c6a, { 0x93, 0x93, 0xb5, 0xfa, 0xe3, 0x41, 0x96, 0x21 } };

	// {116d3da4-6e60-4566-8fbf-036f5dce2229} 
	const SCOM::GUID CLSID_CLogger = { 0x116d3da4, 0x6e60, 0x4566, { 0x8f, 0xbf, 0x03, 0x6f, 0x5d, 0xce, 0x22, 0x29 } };

} // namespace


/*! \mainpage Sekai Engine API Reference
*
* \section intro_sec Introduction
*
* Welcome to the Sekai Engine.
*
* Sekai is the middleware for multimedia applications with real-time graphics processing. 
* This is not only the rendering package, it consist of multiple modules that can help you develop your applications
* faster. It also provides platform abstraction to achieve maximum portability.
* 
* For detailed description see our wiki: http://mail.virtual.kharkov.ua:7777/index.php/Sekai:Home
*
* \subsection structure Structure
*
* Engine was design for maximum reusability and extendability. It consist of only one main module - Core. 
* Core's task is to scan startup directory and load all plug-ins declared there. Plug-in consist of
* the plug-in description (XML-file) and actual code (DLL). Core and modules interact using extension-extender paradigm.
* Those relationships are defined in XML file to achieve "lazy loading" (plug-in won't be loaded until its actualy needed).
*
* This architecture in fact is so agile that was used in multiple projects, from desktop applications to compilers.
* And we achieved 100% reuse of low-level components between those projects.
*
* \subsection modules Main modules
*
* Here is the description of main modules of the engine:
* - Core - binds all plug-ins together, holds the relation graph of plug-ins.
* - Core.SCOM - lightweight implementation of COM, supports interface qurying, factories and module maps.
* - Core.Logging - provides logging facilities, also supports exception handling with call-stack generation.
* - Core.FileSystem - provides platform abstraction of file system, also supports file filter mechanism, archives, and async loading.
* - Core.Reflection - means of adding reflection (introspection) for your classes, function invokation and events are here too.
* - Core.Math - vector math library, provides optimized math routines for SSE and SPU(Play Station 3 cell processor)
* - Core.Utils - utility classes, functors etc.
* - Engine - frame loop, scene management, game objects, space partition and many more
* - Engine.Graphics - provides rendering API abstractions, material system, shader graph etc.
* - Engine.Graphics.VG - low-level library for vector graphics rendering, in future will be used in GUI subsystem.
* - Engine.Input - abstraction on input devices
*
* \section install_sec Installation
*
* For detailed instalation procedure see http://mail.virtual.kharkov.ua:7777/index.php/Sekai:Building_the_solution
*
* \section lic_sec License
*
* We will have one soon :)
*
* \section contacts_sec Contacts:
*
* If you have any questions - mail me:
* Sergey Mikhtonyuk - mikhtonyuk@gmail.com
* 
*/




#endif // _SEKAICORE_H__