/*========================================================
 * RendererExceptions.h
 * @author Sergey Mikhtonyuk
 * @date 01 May 2009
=========================================================*/
#ifndef _RENDEREREXCEPTIONS_H__
#define _RENDEREREXCEPTIONS_H__

#include <exception>

namespace Engine
{
	namespace Graphics
	{

		/// Base class for all exceptions generated in renderer
		/** @ingroup Graphics */
		class RendererException : public std::exception
		{
		public:
			RendererException() : std::exception() { }
			RendererException(const char* msg) : std::exception(msg) { }
		};

		//////////////////////////////////////////////////////////////////////////

		/// Raised in case of incompatible surface format
		/** @ingroup Graphics */
		class FormatException : public RendererException
		{
		public:
			FormatException() : RendererException() { }
			FormatException(const char* msg) : RendererException(msg) { }
		};

		//////////////////////////////////////////////////////////////////////////

		/// Raised in case of wrong operation call
		/** @ingroup Graphics */
		class InvalidOperationException : public RendererException
		{
		public:
			InvalidOperationException() : RendererException() { }
			InvalidOperationException(const char* msg) : RendererException(msg) { }
		};

		//////////////////////////////////////////////////////////////////////////

		/// Raised in case of resource-related errors
		/** @ingroup Graphics */
		class ResourceException : public RendererException
		{
		public:
			ResourceException() : RendererException() { }
			ResourceException(const char* msg) : RendererException(msg) { }
		};

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif	// _RENDEREREXCEPTIONS_H__