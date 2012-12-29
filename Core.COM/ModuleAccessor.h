/*========================================================
* ModuleAccessor.h
* @author Sergey Mikhtonyuk
* @date 02 May 2009
=========================================================*/
#include "Implementations.h"
#include "../Core.Utils/NonCopyable.h"

namespace Core
{
	namespace SCOM
	{
		/// This class provides convenient access to module map
		/** As it receives pointer to get map function it's can be used 
		 *  for access to the map of current module.
		 *
		 *  @ingroup SCOM */
		class ModuleAccessor : Utils::NonCopyable
		{
		public:
			/// Map getter type
			typedef MODULE_MAP_ENTRY* (*GET_MAP_FUNC)();
			/// Map getter
			GET_MAP_FUNC	mGetModuleMap;	

		public:

			/// Default ctor
			ModuleAccessor() : mGetModuleMap(0) { }

			/// Ctor
			ModuleAccessor(GET_MAP_FUNC gmf) : mGetModuleMap(gmf) { }

			/// Initialize accessor
			void Init(GET_MAP_FUNC gmf) { mGetModuleMap = gmf; }

			/// Check if map accessor was initialized
			bool IsInitialized() const
			{
				return mGetModuleMap != 0;
			}

			/// Creates instance of the class and tries to cast it to desired interface
			/** @param clsid CLS_ID of the class to create
			*  @param riid Interface ID of interface to cast to
			*  @param ppv location where to put the interface pointer */
			HResult CreateInstance(SCOM_RIID clsid, SCOM_RIID riid, void** ppv);


			/// Creates first found implementation of specified interface
			/**@param riid Interface ID of desired interface
			* @param ppv location where to put the interface pointer */
			HResult CreateInstance(SCOM_RIID riid, void** ppv);

			/// Returns first entry of module map
			MODULE_MAP_ENTRY* GetFirstEntry() { return mGetModuleMap(); }
		};

	} // namespace
} // namespace