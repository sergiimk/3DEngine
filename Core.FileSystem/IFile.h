/*========================================================
* IFile.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _IFILE_H__
#define _IFILE_H__

#include "IResource.h"
#include "FileSystem_fwd.h"
#include <iosfwd>
#include <boost/function.hpp>

namespace Core
{
	namespace FileSystem
	{
		/// IFile interface
		/** Extends IResource with file operations,
		 *  leaf in IResource hierarchy 
		 *
		 *  @ingroup FileSystem */
		SCOM_INTERFACE(IFile, "131dcbbc-0920-4a2d-a463-1f29fe96fc89", IResource)
		{
		public:
			/// File system object
			virtual IFileSystem* FileSystem() = 0;

			/// Gets file extension
			virtual const std::string& Extension() = 0;

			/// Returns file stream
			virtual std::fstream& Stream(std::ios::open_mode mode = std::ios::in) = 0;

			/// Reads all file to dynamically allocated buffer
			virtual void ReadFile(char **ppBuffer, std::ios::streamoff &size) = 0;

			/// Schedules the read operation
			/** Async operation performed by FileSystem's Proactor, which invokes file reading in
			  * background thread. After completion you will be notified by provided handler.
			  * Handler is always invoked from main thread. It is safe to release file handle right after scheduling */
			virtual void ReadFileAsync(char **ppBuffer, std::ios::streamoff &size, boost::function<void ()> &handler) = 0;
		};

	
	} // namespace
} // namespace


#endif // _IFILE_H__