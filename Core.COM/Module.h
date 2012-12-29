/*========================================================
* PackageImpl.h
* @author Sergey Mikhtonyuk
* @date 03 November 2008
=========================================================*/

#ifndef _MODULECLASS_H__
#define _MODULECLASS_H__

#include "ModuleAccessor.h"
#include <exception>

namespace Core
{
	namespace SCOM
	{

		/// Module managing class
		/** Used to easily load the module and gain access to module map
		 *  @ingroup SCOM */
		class Module : Utils::NonCopyable
		{
			/// Module init function type
			typedef void (*INIT_FUNC)();
			/// Module shutdown function type
			typedef void (*SHUTDOWN_FUNC)();

			void*			mModule;		///< Module handle
			INIT_FUNC		mInitFunc;		///< Init function
			SHUTDOWN_FUNC	mShutdownFunc;	///< Init function
			ModuleAccessor	mModuleAccessor;///< accessor to loaded module

		public:

			/// Creates uninitialized module object
			Module() : mModule(0), mInitFunc(0), mShutdownFunc(0)
			{ 
			}

			/// Creates and initializes module object
			Module(const char* moduleName)
			{
				if(SCOM_FAILED(Init(moduleName)))
					throw std::exception("Failed to initialize module");
			}

			/// Unloads the package
			~Module() 
			{ 
				Shutdown();
				UnloadPackage();
			}

			/// Used to bind module object to some dll and extract module map accessor
			HResult Init(const char* moduleName);

			/// Calls module shutdown routine
			void Shutdown();

			/// Checks if module is loaded and module map extracted
			bool IsLoaded() const 
			{ 
				return (mModuleAccessor.IsInitialized() && mModule != 0); 
			}


			/// Used to free library
			void UnloadPackage();


			/// Creates instance of the class and tries to cast it to desired interface
			/** @param clsid CLS_ID of the class to create
			 *  @param riid Interface ID of interface to cast to
			 *  @param ppv location where to put the interface pointer */
			HResult CreateInstance(SCOM_RIID clsid, SCOM_RIID riid, void** ppv)
			{
				// Redirect call
				return mModuleAccessor.CreateInstance(clsid, riid, ppv);
			}


			/// Creates first found implementation of specified interface
			/**@param riid Interface ID of desired interface
			 * @param ppv location where to put the interface pointer */
			HResult CreateInstance(SCOM_RIID riid, void** ppv)
			{
				// Redirect call
				return mModuleAccessor.CreateInstance(riid, ppv);
			}

			/// Returns first entry of module map
			MODULE_MAP_ENTRY* GetFirstEntry()
			{
				return mModuleAccessor.GetFirstEntry();
			}
		};


	} // namespace
} // namespace

#endif // _MODULECLASS_H__