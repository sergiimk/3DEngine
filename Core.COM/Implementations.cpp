#include "Implementations.h"

namespace Core
{
	namespace SCOM
	{
		//////////////////////////////////////////////////////////////////////////

		HResult _Chain(void *pThis, void* pChain, SCOM_RIID riid, void **ppv)
		{
			_CHAINDATA* pcd = static_cast<_CHAINDATA*>(pChain);
			void* p = (void*)((unsigned long)pThis + pcd->dwOffset);
			return _QueryInterface(p, pcd->pFunc(), riid, ppv);
		}

		//////////////////////////////////////////////////////////////////////////

		HResult _QueryInterface(void* pThis, const INTERFACE_MAP_ENTRY* pEntries, SCOM_RIID riid, void** ppvObject)
		{
			// To avoid ambiguity always cast first entry to IUnknown
			if (riid == UUIDOF(IUnknown))
			{
				// first entry must be an offset
				assert( pEntries->locator == SCOM_OFFSET_ENTRY );
				*ppvObject = (char*)pThis + reinterpret_cast<unsigned long>(pEntries->OffChain); 
				((IUnknown*) (*ppvObject))->AddRef () ;
				return SCOM_S_OK;
			} 
			else 
			{
				HResult hr = SCOM_E_NOINTERFACE; 
				// until end
				while (pEntries->locator)
				{
					if (!pEntries->piid || (riid == *pEntries->piid))
					{
						if (pEntries->locator == SCOM_OFFSET_ENTRY)
						{ 
							*ppvObject = (char*)pThis + reinterpret_cast<unsigned long>(pEntries->OffChain); 
							((IUnknown*)(*ppvObject))->AddRef();
							hr = SCOM_S_OK; 
							break; 
						} 
						else
						{ 
							hr = pEntries->locator(pThis, pEntries->OffChain, riid, ppvObject); 
							if (hr == SCOM_S_OK)
								break; 
						} 
					} 
					++pEntries; 
				} 
				if (hr != SCOM_S_OK)
					*ppvObject = 0; 
				return hr; 
			}
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace