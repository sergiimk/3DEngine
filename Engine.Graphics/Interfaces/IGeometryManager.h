/*========================================================
* IGeometryManager.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __IGEOMETRY_MANAGER_H__
#define __IGEOMETRY_MANAGER_H__

#include "MeshTypes.h"
#include "IResourceManager.h"
#include "../../Core.Utils/URL.h"
#include "../../Core.Math/VML_fwd.h"

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////
		class IProceduralMeshCallback;
		//////////////////////////////////////////////////////////////////////////

		/// Interface for managing the meshes
		/** @ingroup Graphics */
		SCOM_INTERFACE(IGeometryManager, "ccaba053-99f3-4163-b5a3-ad42429b84d1", IResourceManager)
		{
		public:
			/// Tries to find and then to load mesh (url should point to mesh description file)
			/** Throws: ResourceException */
			virtual void FindOrLoadMesh(const Utils::URL &url, IMesh** outMesh) = 0;

			/// Creates plane mesh
			virtual void CreatePlane(float x, float y, IMesh** outPlane) = 0;

			/// Creates box mesh
			virtual void CreateBox(const VML::Vector3& a, const VML::Vector3& b, IMesh** outBox) = 0;

			/// Creates sphere mesh with specified properties
			virtual void CreateSphere(int nSegments, int nRings, float radius, IMesh** outSphere) = 0;

			/// Creates mesh that uses procedural callback to fill the internal data on load
			/** @param callback callback that should be used during initialization (not creation, but first AddUser)
			 *  @param outProcMesh output procedural mesh */
			virtual void CreateProceduralMesh(IProceduralMeshCallback* callback, IMesh** outProcMesh) = 0;
		};

		//////////////////////////////////////////////////////////////////////////

		/// Callback for procedural mesh creation
		/** @ingroup Graphics */
		SCOM_INTERFACE(IProceduralMeshCallback, "a67fd179-c3ad-482c-b44a-1086a3f89fc9", Core::SCOM::IUnknown)
		{
		public:
			
			/// Request to fill mesh with a procedural data
			virtual void FillMeshData(IMesh* pMesh) = 0;
		};

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif