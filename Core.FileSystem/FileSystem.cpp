/*========================================================
* FileSystem.cpp
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#include "FileSystem.h"
#include "CFileSystem.h"
#include "../Core/CommonPlugin.h"

namespace Core
{
	GlobalEnvironment* gEnv;
	CommonPlugin* CommonPlugin::Instance;

	namespace FileSystem
	{

		BEGIN_MODULE_MAP()
			OBJECT_ENTRY(CLSID_CFileSystem, CFileSystem)
			OBJECT_ENTRY_I(CLSID_CommonPlugin, UUIDOF(IPlugin), CommonPlugin)
		END_MODULE_MAP()

	} // namespace
} // namespace