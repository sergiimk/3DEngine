/*========================================================
* FileSystem.cpp
* @author Eugene Kuznetsov
* @date 19 November 2008
=========================================================*/

#include "Input.h"
#include "CInputController.h"

namespace Engine
{
	namespace Input
	{
		// {860b5c8f-cb3f-442d-a732-664a921f313b} 
		static const Core::SCOM::GUID CLSID_CInputController = 
		{ 0x860b5c8f, 0xcb3f, 0x442d, { 0xa7, 0x32, 0x66, 0x4a, 0x92, 0x1f, 0x31, 0x3b } };

		BEGIN_MODULE_MAP()
			OBJECT_ENTRY_I(CLSID_CInputController, UUIDOF(IInputController), CInputController)
		END_MODULE_MAP()

	} // namespace
} // namespace
