/*========================================================
* IPath.h
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#ifndef _IPATH_H__
#define _IPATH_H__

#include "VGTypes.h"
#include "VGLib_fwd.h"
#include "../Engine.Graphics/Graphics_fwd.h"
#include "../Core.COM/Interfaces.h"

namespace VG
{
	/// Stores initial vector graphics data
	/** @ingroup VG */
	SCOM_INTERFACE(IPath, "4f903fac-9d8f-41e8-a7c1-b36c3f93a90c", Core::SCOM::IUnknown)
	{
	public:

		/// Returns path buffer
		virtual IPathBuffer* getPathBuffer() const = 0;

		/// Approximates and tessellates path
		virtual void RecalculatePath() = 0;

		/// Returns the calculated mesh
		virtual Engine::Graphics::IMesh* getFillMesh() = 0;

		virtual Engine::Graphics::IMesh* getStrokeMesh() = 0;


		/// Gets specified path property
		virtual unsigned int getProperty(PathProperty p) const	= 0;

		/// Sets specified path property
		virtual void setProperty(PathProperty p, unsigned int val)	= 0;

		/// Resets path properties to default
		virtual void ResetProperties() = 0;

		/// Returns the stroke width
		virtual float getStrokeWidth() const = 0;

		/// Sets the stroke width
		virtual void setStrokeWidth(float w) = 0;

		/// Returns the approximation tolerance
		virtual float getTolerance() const = 0;

		/// Sets the approximation tolerance
		virtual void setTolerance(float t) = 0;

		/// Increase usage count to make sure resource is loaded
		virtual void AddUser() = 0;

		/// Decrease usage count
		virtual void RemoveUser() = 0;
	};

} // namespace

#endif // _IPATH_H__