/*========================================================
* ModuleAccessor.cpp
* @author Sergey Mikhtonyuk
* @date 02 May 2009
=========================================================*/
#include "ModuleAccessor.h"

namespace Core
{
	namespace SCOM
	{
		//////////////////////////////////////////////////////////////////////////

		HResult ModuleAccessor::CreateInstance(SCOM_RIID clsid, SCOM_RIID riid, void** ppv)
		{
			HResult hr = SCOM_E_POINTER;
			if(ppv == 0) return hr;

			MODULE_MAP_ENTRY* ent = mGetModuleMap();			
			while(ent->pClsid)
			{
				if(clsid == *ent->pClsid)
				{
					if(!ent->pClassFactory)
					{
						hr = ent->pCreateFactoryFn(UUID_PPV(IClassFactory, &ent->pClassFactory));
						if(SCOM_FAILED(hr)) 
							return hr;
					}
					hr = ent->pClassFactory->CreateInstance(riid, ppv);
					return hr;
				}
				++ent;
			}
			return SCOM_E_FAIL;
		}

		//////////////////////////////////////////////////////////////////////////

		HResult ModuleAccessor::CreateInstance(SCOM_RIID riid, void** ppv)
		{
			HResult hr = SCOM_E_POINTER;
			if(ppv == 0) return hr;

			MODULE_MAP_ENTRY* ent = mGetModuleMap();			
			while(ent->pClsid)
			{
				if(ent->pInterfaceId && riid == *ent->pInterfaceId)
				{
					if(!ent->pClassFactory)
					{
						hr = ent->pCreateFactoryFn(UUID_PPV(IClassFactory, &ent->pClassFactory));
						if(SCOM_FAILED(hr)) 
							return hr;
					}
					hr = ent->pClassFactory->CreateInstance(riid, ppv);
					return hr;
				}
				++ent;
			}
			return SCOM_E_FAIL;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace