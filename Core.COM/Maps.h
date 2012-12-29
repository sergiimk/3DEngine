/*========================================================
* Maps.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _SCOM_MAPS_H__
#define _SCOM_MAPS_H__

namespace Core
{
	namespace  SCOM
	{
		/////////////////////////////////////////////////////////////////////////
		//  Interface map
		/////////////////////////////////////////////////////////////////////////


		/// Interface locator function type
		typedef HResult (*INTERFACE_LOCATOR_FUNC)(void *pThis, void* pChain, SCOM_RIID riid, void **ppv);
	
		/// Indicate entry is just offset 
		#define SCOM_OFFSET_ENTRY ((Core::SCOM::INTERFACE_LOCATOR_FUNC)1)


		/////////////////////////////////////////////////////////////////////////


		/// Interface entry in interface map
		struct INTERFACE_MAP_ENTRY
		{
			const SCOM_IID*			piid;		///< pointer to interface ID
			void*					OffChain;	///< offset of class from IUnknown or chain pointer
			INTERFACE_LOCATOR_FUNC	locator;	///< 0 - table end; 1 - offset entry; else - real locator
		};


		/////////////////////////////////////////////////////////////////////////

	
		/// Interface query chaining structure
		struct _CHAINDATA
		{
			long long dwOffset;
			const INTERFACE_MAP_ENTRY* (*pFunc)();
		};


		/////////////////////////////////////////////////////////////////////////
	

		template <class base, class derived>
		class _ComChainData	{ public: static _CHAINDATA data; };
	
		template <class base, class derived>
		_CHAINDATA _ComChainData<base, derived>::data = {classoffset(base, derived), base::_GetEntries};


		/////////////////////////////////////////////////////////////////////////


		#define BEGIN_INTERFACE_MAP() public:																				\
		Core::SCOM::IUnknown* GetUnknown() throw() {return (Core::SCOM::IUnknown*)((long long)this+(long long)_GetEntries()->OffChain); }	\
		const static Core::SCOM::INTERFACE_MAP_ENTRY* _GetEntries() throw() {												\
		static const Core::SCOM::INTERFACE_MAP_ENTRY _entries[] = {

		/////////////////////////////////////////////////////////////////////////
		
		#define INTERFACE_ENTRY(intrfc)\
		{&UUIDOF(intrfc), (void*)classoffset(intrfc, _ThisClass), SCOM_OFFSET_ENTRY},

		/////////////////////////////////////////////////////////////////////////
	
		#define INTERFACE_ENTRY_BRANCHED(intrfc, branch)\
		{&UUIDOF(intrfc), static_cast<void*>(static_cast<intrfc*>(static_cast<branch*>(reinterpret_cast<_ThisClass*>(8))))-8, SCOM_OFFSET_ENTRY},

		/////////////////////////////////////////////////////////////////////////
	
		#define INTERFACE_ENTRY_CHAIN(baseclass)\
		{0, (void*)&Core::SCOM::_ComChainData<baseclass, _ThisClass>::data, Core::SCOM::_Chain},

		/////////////////////////////////////////////////////////////////////////
	
		#define END_INTERFACE_MAP() \
		{0, 0, 0}}; return &_entries[0];}


	
		/////////////////////////////////////////////////////////////////////////
		//  Module map implementation
		/////////////////////////////////////////////////////////////////////////

		#define DECLARE_IMPLEMENTATION(className)																		\
		DECLARE_IMPLEMENTATIONA(className, Core::SCOM::NewAllocator)

		/////////////////////////////////////////////////////////////////////////

		#define DECLARE_IMPLEMENTATIONA(className, Allocator)															\
		DECLARE_IMPLEMENTATION2A(className, Allocator, Core::SCOM::ComClassFactory)

		/////////////////////////////////////////////////////////////////////////
	
		#define DECLARE_IMPLEMENTATION2(className, factoryClass)														\
		DECLARE_IMPLEMENTATION2A(className, Core::SCOM::NewAllocator, factoryClass)

		/////////////////////////////////////////////////////////////////////////
	
		#define DECLARE_IMPLEMENTATION2A(className, Allocator, factoryClass)											\
		public:																											\
		typedef className _ThisClass;																					\
		typedef Core::SCOM::ComObject<className, Allocator> _ObjectClass;												\
		typedef factoryClass< _ObjectClass > _FactoryClass;

		/////////////////////////////////////////////////////////////////////////

		#define DECLARE_IMPLEMENTATION_DERIVED(className, baseClassName)												\
		DECLARE_IMPLEMENTATION_DERIVED2(className, baseClassName, Core::SCOM::ComClassFactory)

		/////////////////////////////////////////////////////////////////////////

		#define DECLARE_IMPLEMENTATION_DERIVED2(className, baseClassName, factoryClass)									\
		public:																											\
		typedef baseClassName _BaseClass;																				\
		typedef className _ThisClass;																					\
		typedef Core::SCOM::ComObject<className> _ObjectClass;															\
		typedef factoryClass< _ObjectClass > _FactoryClass;

		/////////////////////////////////////////////////////////////////////////
	
		typedef HResult (_CREATOR_FUNC)(SCOM_RIID riid, void** ppv);

		/////////////////////////////////////////////////////////////////////////
	

		/// Object entry in module map
		struct MODULE_MAP_ENTRY
		{
			const SCOM_CLSID*	pClsid;
			const SCOM_IID*		pInterfaceId;
			_CREATOR_FUNC*		pCreateFactoryFn;
			IClassFactory*		pClassFactory;
		};


		/////////////////////////////////////////////////////////////////////////
	
		#define BEGIN_MODULE_MAP()																						\
		extern "C" __declspec(dllexport) Core::SCOM::MODULE_MAP_ENTRY* GetModuleMap()									\
		{ static Core::SCOM::MODULE_MAP_ENTRY e[] = {

		/////////////////////////////////////////////////////////////////////////
	
		#define OBJECT_ENTRY(clssid, clss)																				\
		{ &clssid, 0, Core::SCOM::ComObject<clss::_FactoryClass>::_CreateInstance, 0 },

		/////////////////////////////////////////////////////////////////////////
	
		#define OBJECT_ENTRY_I(clssid, intrfID, clss)																	\
		{ &clssid, &intrfID, Core::SCOM::ComObject<clss::_FactoryClass>::_CreateInstance, 0 },
	
		/////////////////////////////////////////////////////////////////////////

		#define END_MODULE_MAP()																						\
		{ 0, 0, 0, 0 } };																								\
		return e; }																										\
																														\
		extern "C" __declspec(dllexport) void ModuleInit() { }															\
		extern "C" __declspec(dllexport) void ModuleShutdown()															\
		{																												\
			Core::SCOM::MODULE_MAP_ENTRY* e = GetModuleMap();															\
			while(e->pClsid)																							\
			{																											\
				if(e->pClassFactory)																					\
				{																										\
					e->pClassFactory->Release();																		\
					e->pClassFactory = 0;																				\
				}																										\
				++e;																									\
			}																											\
		}

		/////////////////////////////////////////////////////////////////////////	
	
	} // namespace
} // namespace


#endif // _SCOM_MAPS_H__