/*========================================================
* IMaterialManager.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __IMATERIAL_MANAGER_H__
#define __IMATERIAL_MANAGER_H__

#include "IResourceManager.h"
#include "..\Core.Utils\URL.h"

namespace Engine
{
	namespace Graphics
	{
		/// Interface for managing the materials
		/** @ingroup Graphics */
		SCOM_INTERFACE(IMaterialManager, "96d548f2-34dd-46aa-8671-acf4bf921889", IResourceManager)
		{
		public:
			/// Tries to find and then to load material
			virtual void FindOrLoadMaterial(const Utils::URL &url, IMaterial** outMaterial) = 0;

			/// Creates material that will be filled manually
			virtual void CreateMaterial(IMaterial** outMaterial) = 0;

			/// Returns default material
			virtual void GetDefaultMaterial(IMaterial** outMaterial) = 0;
		};

	} // namespace
} // namespace

#endif