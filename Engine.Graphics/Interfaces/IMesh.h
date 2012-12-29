/*========================================================
* IMesh.h
* @author Sergey Mikhtonyuk
* @date 03 January 2009
=========================================================*/
#ifndef __IMESH_H__
#define __IMESH_H__

#include "MeshTypes.h"
#include "SBoundingVolume.h"
#include "IGeometry.h"
#include "IResourceInternal.h"

namespace Engine
{
	namespace Graphics
	{
		/// Proxy that loads geometry data split by subsets
		/** @ingroup Graphics */
		SCOM_INTERFACE(IMesh, "92510cdf-2e74-4b46-a193-fb2c7d020bf8", IResourceInternal)
		{
		public:

			/// Returns the primitive type that describe an object
			virtual EPrimitiveType getPrimitiveType() const = 0;

			/// Set new primitive type
			virtual void setPrimitiveType(EPrimitiveType t) = 0;

			/// Returns the number of geometry subsets
			virtual size_t GetSubsetCount() const = 0;

			/// Returns the specified subset of mesh
			virtual IGeometry* GetSubset(int index) const = 0;

			/// Removes all subsets
			virtual void ClearSubsets() = 0;

			/// Add new mesh subset
			virtual IGeometry* AddSubset(	const IGeometry::TInterval& vert,
											const IGeometry::TInterval& indx) = 0;


			/// Returns bounding volume of the mesh
			virtual const SBoundingVolume& GetBoundingVolume() const = 0;

			/// Sets the new bounding volume
			virtual void SetBoundingVolume(const SBoundingVolume& bv) = 0;

			/// Locks buffer and recalculates bounding volume
			virtual void UpdateBoundingVolume() = 0;


			/// Returns the number of vertices in mesh (computed as sum of intervals of subsets)
			virtual size_t GetVertexCount() const = 0;

			/// Returns the number of indices in mesh (computed as sum of intervals of subsets)
			virtual size_t GetIndexCount() const = 0;

			/// Returns the number of faces or other primitives in mesh
			virtual size_t GetPrimitiveCount() const = 0;

			/// Returns the size of the vertex (based on current declaration)
			virtual size_t GetVertexSize() const = 0;

			/// Returns the declaration of the vertex
			/** elems should have at least MAX_VERTEX_ELEMENTS elements */
			virtual void GetVertexDeclaration(SVertexElement* elems) const = 0;

			/// Changes the vertex declaration
			virtual void SetVertexDeclaration(const SVertexElement* elems) = 0;


			/// Returns the vertex buffer
			virtual IBuffer* GetVertexBuffer() const = 0;

			/// Returns the index buffer
			virtual IBuffer* GetIndexBuffer() const = 0;

			
			/// Returns geometry manager that created this mesh
			virtual IGeometryManager* GetManager() = 0;
		};

	} // namespace
} // namespace

#endif