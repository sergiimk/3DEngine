/*========================================================
* AdapterFactoyContainer.h
* @author Sergey Mikhtonyuk
* @date 23 November 2008
=========================================================*/
#ifndef _ADAPTERFACTOYCONTAINER_H__
#define _ADAPTERFACTOYCONTAINER_H__

#include "IAdapterFactory.h"
#include <hash_map>
#include "../Core.Utils/GuidHashCmp.h"
#include <vector>

namespace Core
{
	/// Provides means to combine multiple adapter factories
	/** @ingroup Core */
	class AdapterFactoyContainer
	{
	public:
		/// Releases all factories
		~AdapterFactoyContainer()
		{
			for(size_t i = 0; i != mFactories.size(); ++i)
				mFactories[i]->Release();
		}

		/// Adds factory to registry
		void AddFactory(IAdapterFactory *pFactory)
		{
			pFactory->AddRef();
			mFactories.push_back(pFactory);

			SCOM::GUID** ppGuid = pFactory->DestInterfaceList();
			while(*ppGuid)
			{
				/// \todo use multimap
				if(mAdatperFactoryMap.find(**ppGuid) == mAdatperFactoryMap.end())
					mAdatperFactoryMap.insert(std::make_pair(**ppGuid, pFactory));
				else
					assert(false);

				++ppGuid;
			}
		}

		/// Creates adapter from first suitable factory
		SCOM::HResult CreateAdapter(SCOM::IUnknown* object, SCOM_RIID uid, void **ppAdapter)
		{
			TAdapterFactoryMap::const_iterator it = mAdatperFactoryMap.find(uid);

			if(it == mAdatperFactoryMap.end())
				return SCOM_E_NOINTERFACE;

			return it->second->GetAdapter(object, uid, ppAdapter);
		}

	protected:
		typedef std::hash_map<SCOM::GUID, IAdapterFactory*> TAdapterFactoryMap;
		
		TAdapterFactoryMap				mAdatperFactoryMap;

		std::vector<IAdapterFactory*>	mFactories;
	};

} // namespace


#endif // _ADAPTERFACTOYCONTAINER_H__