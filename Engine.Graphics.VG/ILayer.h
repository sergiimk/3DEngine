/*========================================================
* ILayer.h
* @author Sergey Mikhtonyuk
* @date 20 July 2009
=========================================================*/
#ifndef _ILAYER_H__
#define _ILAYER_H__

#include "../Core.COM/Interfaces.h"
#include "VGLib_fwd.h"

namespace VG
{

	/// Organizes paths rendered in one layer
	/** Layers are used for correct drawing of VG geometry.
	 *  Inside one layer all paths are rendered front-to-back,
	 *  this not only reduces overdraw, bu also eliminates path overlapping,
	 *  that will otherwise cause artifacts in case of usage of transparency.
	 *  
	 *  @ingroup VG */
	SCOM_INTERFACE(ILayer, "f63f4747-94c3-49cc-a823-c6b9c7e940d9", Core::SCOM::IUnknown)
	{
	public:

		/// Returns the number of paths in this layer
		virtual size_t getComponentsNum() const = 0;

		/// Returns path at the specified index (component with small indices will be obscured by other)
		virtual IPath* getComponent(size_t index) const = 0;

		/// Adds component to the end of the container (will be at the front of all)
		virtual void AddComponent(IPath* path) = 0;

		/// Creates new path and returns pointer to it for further initialization
		virtual IPath* AddNewComponent();

		/// Removes specified component
		virtual void RemoveComponent(IPath* path) = 0;

		/// Recalculates all paths in this layer
		virtual void RecalculateAll();

		/// Sets equal tolerance to all paths in this layer
		virtual void setToleranceToAll(float tolerance) = 0;


		/// Used to indicate that layer is in use and should be loaded
		virtual void AddUser() = 0;

		/// Layer can be unloaded when no one uses it
		virtual void RemoveUser() = 0;
		
		/// Performs rendering of layer components
		virtual void Render() = 0;
	};

} // namespace

#endif // _ILAYER_H__