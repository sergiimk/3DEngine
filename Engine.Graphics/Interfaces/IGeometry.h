/*========================================================
* IGeometry.h
* @author Sergey Mikhtonyuk
* @date 09 May 2009
=========================================================*/
#ifndef _IGEOMETRY_H__
#define _IGEOMETRY_H__

#include "../Graphics_fwd.h"
#include "../../Core.COM/Interfaces.h"
#include <utility>

namespace Engine
{
	namespace Graphics
	{
		/// Rendering primitive, associates some material with subset in vertex and index buffers inside mesh
		/** @ingroup Graphics */
		SCOM_INTERFACE(IGeometry, "d626c165-6012-4e55-a2b5-d6d7f7cbec03", Core::SCOM::IUnknown)
		{
		public:
			/// Interval type, defines beginning and the number of points
			typedef std::pair<size_t, size_t> TInterval;

			/// Returns the mesh which possesses the referenced index & vertex buffers
			virtual IMesh* GetMesh() const = 0;

			/// Returns the material associated with this geometry set
			virtual IMaterial* GetMaterial() const = 0;

			/// Sets the material of this geometry set
			virtual void SetMaterial(IMaterial* mat) = 0;

			/// Returns the interval of faces in mesh buffer that belong to this geometry set
			/** @return interval in form of (start, length) */
			virtual const TInterval& GetIndexInterval() const = 0;

			/// Returns the interval of vertices in mesh buffer that belong to this geometry set
			/** @return interval in form of (start, length) */
			virtual const TInterval& GetVertexInterval() const = 0;
		};

	} // namespace
} // namespace

#endif	// _IGEOMETRY_H__