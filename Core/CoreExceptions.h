/*========================================================
* CoreExceptions.h
* @author Sergey Mikhtonyuk
* @date 28 November 2008
=========================================================*/
#ifndef _COREEXCEPTIONS_H__
#define _COREEXCEPTIONS_H__

#include <exception>

namespace Core
{
	/// Base class for all exception generated in core
	/** @ingroup Core */
	class CoreException : public std::exception
	{
	public:
		CoreException() : std::exception() { }
		CoreException(const char* msg) : std::exception(msg) { }
	};

	/// Exception generated during the plug-in shadow loading
	/** @ingroup Core */
	class ParsingException : public CoreException
	{
	public:
		ParsingException() : CoreException() { }
		ParsingException(const char* msg) : CoreException(msg) { }
	};

} // namespace


#endif // _COREEXCEPTIONS_H__