/*========================================================
 * FSExceptions.h
 * @author Sergey Mikhtonyuk
 * @date 01 May 2009
=========================================================*/
#ifndef _FSEXCEPTIONS_H__
#define _FSEXCEPTIONS_H__

#include <exception>

namespace Core
{
	namespace FileSystem
	{

		/// Base class for all exceptions generated in file system
		/** @ingroup FileSystem */
		class FSException : public std::exception
		{
		public:
			FSException() : std::exception() { }
			FSException(const char* msg) : std::exception(msg) { }
		};

		//////////////////////////////////////////////////////////////////////////

		/// Generated in adapters when parsing fails
		/** @ingroup FileSystem */
		class FSParsingException : public FSException
		{
		public:
			FSParsingException() : FSException() { }
			FSParsingException(const char* msg) : FSException(msg) { }
		};

	} // namespace
} // namespace

#endif	// _FSEXCEPTIONS_H__