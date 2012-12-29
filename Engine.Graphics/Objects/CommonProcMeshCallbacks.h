/*========================================================
* CommonProcMeshCallbacks.h
* @author Sergey Mikhtonyuk
* @date 20 May 2009
=========================================================*/
#ifndef _COMMONPROCMESHCALLBACKS_H__
#define _COMMONPROCMESHCALLBACKS_H__

#include "../Interfaces/IGeometryManager.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		/// Common callback for creating a box-mesh
		/** @ingroup Graphics */
		class NOVTABLE CBoxCallback : 
			public Core::SCOM::ComRootObject<>,
			public IProceduralMeshCallback
		{
		public:
			DECLARE_IMPLEMENTATION(CBoxCallback)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IProceduralMeshCallback)
			END_INTERFACE_MAP()
		
			void FinalConstruct(const VML::Vector3& a, const VML::Vector3& b);

			void FillMeshData(IMesh* pMesh);

		private:
			float mA[3];
			float mB[3];
		};

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		/// Common callback for creating a sphere-mesh
		/** @ingroup Graphics */
		class NOVTABLE CSphereCallback : 
			public Core::SCOM::ComRootObject<>,
			public IProceduralMeshCallback
		{
		public:
			DECLARE_IMPLEMENTATION(CSphereCallback)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IProceduralMeshCallback)
			END_INTERFACE_MAP()

			void FinalConstruct(int rings, int segments, float r);

			void FillMeshData(IMesh* pMesh);

		private:
			int mRings;
			int mSegments;
			float mRadius;
		};

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		/// Common callback for creating a plane-mesh
		/** @ingroup Graphics */
		class NOVTABLE CPlaneCallback : 
			public Core::SCOM::ComRootObject<>,
			public IProceduralMeshCallback
		{
		public:
			DECLARE_IMPLEMENTATION(CPlaneCallback)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IProceduralMeshCallback)
			END_INTERFACE_MAP()

			void FinalConstruct(float x, float y);

			void FillMeshData(IMesh* pMesh);

		private:
			float m_x;
			float m_y;
		};

	} // namespace
} // namespace

#endif	// _COMMONPROCMESHCALLBACKS_H__