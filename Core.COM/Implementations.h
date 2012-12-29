/*========================================================
* Implementations.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
=========================================================*/

#ifndef _IMPLEMENTATIONS_H__
#define _IMPLEMENTATIONS_H__

#include "Interfaces.h"
#include "Maps.h"
#include "ThreadingModel.h"
#include "allocators.h"
#include <cassert>

namespace Core
{
	namespace SCOM
	{
		/// Inherit this class for IUnknown method implementation
		/** Template parameter defines threading model for operations
		 *  @ingroup SCOM */
		template<class ThreadingModel = SingleThreadModel>
		class ComRootObject
		{
		public:
			virtual ~ComRootObject() { }
	
		protected:	
			/// Implementation of IUnknown::AddRef method
			/** This implementation is binded to your class by ComObject class */
			static unsigned long _AddRef(long& refCount) 
			{
				ThreadingModel::Increment(refCount);
				return refCount;
			}
	
			/// Implementation of IUnknown::Release method
			/** This implementation is binded to your class by ComObject class */
			static unsigned long _Release(long& refCount)
			{
				assert(refCount > 0);
				ThreadingModel::Decrement(refCount);
				return refCount;
			}
		};


		//////////////////////////////////////////////////////////////////////////


		/// Implementation of IUnknown::QueryInterface method
		/** This method uses interface table, which you define by BEGIN_INTERFACE_MAP macro */
		HResult _QueryInterface(void* pThis, const INTERFACE_MAP_ENTRY* pEntries, SCOM_RIID riid, void** ppvObject);

		/// Used for chaining QueryInterface
		/** This method used when you have an hierarchy of implementations
		*  and passing QueryInterface to the top of the tree */
		HResult _Chain(void *pThis, void* pChain, SCOM_RIID riid, void **ppv);


		//////////////////////////////////////////////////////////////////////////

	
		/// ComClassFactory class
		/** Implements IClassFactory methods
		 *  @ingroup SCOM */
		template <class T>
		class NOVTABLE ComClassFactory : 
			public ComRootObject<>, 
			public IClassFactory
		{
		public:
			/// This class type
			typedef ComClassFactory _ThisClass;
	
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IClassFactory)
			END_INTERFACE_MAP()
			
			/// Redirects creation to T::CreateInstance()
			HResult CreateInstance(SCOM_RIID riid, void** ppvObj)
			{
				return T::_CreateInstance(riid, ppvObj);
			}
		};


		//////////////////////////////////////////////////////////////////////////

		
		/// ComClassFactorySingleton class
		/** Implements IClassFactory methods 
		 *  caching the pointer received after first query
		 *  and returns it for the following queries 
		 * 
		 *  @ingroup SCOM */
		template <class T>
		class NOVTABLE ComClassFactorySingleton : 
			public ComRootObject<>, 
			public IClassFactory
		{
		public:
			/// This class type
			typedef ComClassFactorySingleton _ThisClass;

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IClassFactory)
			END_INTERFACE_MAP()

			/// Ctor
			ComClassFactorySingleton() : pCached(0)
			{
			}

			/// Releases cached pointer
			virtual ~ComClassFactorySingleton()
			{
				if(pCached)
					pCached->Release();
			}

			/// Creates object for first call and then return cached pointer after casting it
			HResult CreateInstance(SCOM_RIID riid, void** ppvObj)
			{
				if(!pCached)
				{
					HResult hr = T::_CreateInstance(UUIDOF(IUnknown), (void**)&pCached);
					if(SCOM_FAILED(hr))
						return hr;
				}
				return pCached->QueryInterface(riid, ppvObj);
			}

		private:
			/// Cached pointer for singleton object
			IUnknown *pCached;
		};
	
	
		//////////////////////////////////////////////////////////////////////////
	
	
		/// ComObject class
		/** Inherits your class and binds IUnknown methods to implementation in ComRootObject
		 *
		 *  @ingroup SCOM
		 *  @see ComRootObject */
		template<typename Base, template<typename> class Alloc = NewAllocator>
		class ComObject : public Base
		{
		public:

			typedef ComObject<Base, Alloc>	_thisType;
			typedef Alloc<_thisType>		allocator;

			/// Ctor
			ComObject() : mRefCount(0)
			{
			}
	
			/// Binds ComRootObject impl to your class
			unsigned long AddRef() 
			{
				return _AddRef(mRefCount);
			}
	
			/// Binds ComRootObject impl to your class
			unsigned long Release() 
			{
				unsigned long t = _Release(mRefCount);
				if(!t)
				{
					allocator alloc;
					alloc.destroy(this);
					alloc.deallocate(this, 1);
				}
				return t;
			}
	
			/// Binds ComRootObject impl to your class
			HResult QueryInterface(SCOM_RIID iid, void **ppObject)
			{
				return _QueryInterface(this, _GetEntries(), iid, ppObject);
			}

			/// Used to create instance of implementation class inside the package (do not increases the ref counter)
			static _thisType* _CreateInstance()
			{
				allocator alloc;
				_thisType* p = alloc.allocate(1);
				p->_thisType::ComObject();
				return p;
			}

			/// Creates and checks for required interface
			static HResult _CreateInstance(SCOM_RIID riid, void** ppv)
			{
				if (ppv == 0) return SCOM_E_POINTER;
				*ppv = 0;

				HResult hRes = SCOM_E_OUTOFMEMORY;
				_thisType* p = 0;

				p = _CreateInstance();

				if (p != 0)
				{
					p->AddRef();
					hRes = p->QueryInterface(riid, ppv);
					p->Release();
				}
				return hRes;
			}


		private:
			/// Reference counter
			long mRefCount;
		};		

	} // namespace
} // namespace

//////////////////////////////////////////////////////////////////////////


/// Creates implementation class instance (refCount == 1)
/** @ingroup SCOM */
template<class Impl, class Ptr>
Core::SCOM::HResult scom_new(Ptr** pp)
{
	if(!pp) return SCOM_E_POINTER;
	*pp = 0;

	Impl::_ObjectClass* pImpl = Impl::_ObjectClass::_CreateInstance();
	if(!pImpl) return SCOM_E_FAIL;

	pImpl->AddRef();
	*pp = pImpl;
	return SCOM_S_OK;
}

//////////////////////////////////////////////////////////////////////////


/// Creates implementation and checks for specified interface (refCount == 1)
/** @ingroup SCOM */
template<class Impl, class Itf>
Core::SCOM::HResult scom_new(Itf** pp, const Core::SCOM::GUID& iid)
{
	assert(iid == UUIDOF(Itf));
	return Impl::_ObjectClass::_CreateInstance(iid, (void**)pp);
}

//////////////////////////////////////////////////////////////////////////


#endif // _IMPLEMENTATIONS_H__