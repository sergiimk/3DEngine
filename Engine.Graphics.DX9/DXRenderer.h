/*========================================================
* Graphics.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
/** @defgroup DX9 DirectX9
 *  Rendering library implementation using DirectX9
 *  @ingroup Graphics */

#ifndef _DXRENDERER_H__
#define _DXRENDERER_H__

#include "../Core.COM/GUID.h"

namespace DXRenderer
{
	// {0e90bbd4-00cf-41e1-a214-b376370924a9} 
	const Core::SCOM::GUID CLSID_CD3DRenderer = 
	{ 0x0e90bbd4, 0x00cf, 0x41e1, { 0xa2, 0x14, 0xb3, 0x76, 0x37, 0x09, 0x24, 0xa9 } };

} // namespace


#endif // _DXRENDERER_H__
