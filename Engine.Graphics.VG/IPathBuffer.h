/*========================================================
* IPathBuffer.h
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#ifndef _IPATHBUFFER_H__
#define _IPATHBUFFER_H__

#include "VGTypes.h"
#include "../Core.Math/VML_fwd.h"

namespace VG
{

	/// Holds vector graphics commands and points of path
	/** @ingroup VG */
	class IPathBuffer
	{
	public:

		/// Returns the pointer to array of points
		virtual VML::Vector2* getPoints() = 0;

		/// Returns the size of points array
		virtual size_t getPointsNumber() const = 0;

		/// Copies the data to point buffer
		virtual void setPoints(const VML::Vector2* points, size_t npoints) = 0;

		/// Clears points buffer
		virtual void FreePointsBuffer() = 0;


		/// Returns the pointer to array of points
		virtual PathCommand* getCommands() = 0;

		/// Returns the size of commands array
		virtual size_t getCommandsNumber() const = 0;

		/// Copies the data to command buffer
		virtual void setCommands(const PathCommand* commands, size_t ncmds) = 0;

		/// Clears commands buffer
		virtual void FreeCommandsBuffer() = 0;


		/// Compares the types of commands and the number of points to the required
		virtual bool IsValid() const = 0;

	};

} // namespace

#endif // _IPATHBUFFER_H__