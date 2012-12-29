/*========================================================
* IFileSystem.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
=========================================================*/

#ifndef _IFILESYSTEM_H__
#define _IFILESYSTEM_H__

#include "../Core.Utils/Proactor.h"
#include "../Core.COM/Interfaces.h"
#include "../Core.COM/Intellectual.h"
#include "FileSystem_fwd.h"
#include <string>

namespace Core
{
	class IAdapterFactory;


	namespace FileSystem
	{

		/// IFileSystem interface
		/** Facade interface from which you begin working 
		 *  with resource handles 
		 *
		 *  @ingroup FileSystem */
		SCOM_INTERFACE(IFileSystem, "afc9ed7f-1158-48bc-99c1-1853cb0e8c62", SCOM::IUnknown)
		{
		public:
			/// Returns resource by specified path
			virtual Core::SCOM::ComPtr<IResource> GetResource(const std::string& path, bool searchArchives = false) = 0;

			/// Retrieves current folder
			virtual Core::SCOM::ComPtr<IFolder> CurrentFolder() = 0;


			/// Used to register adapter factory for the IFile interface
			/** @see IAdapterFactory */
			virtual void RegisterFileAdapterFactory(IAdapterFactory *pFactory) = 0;

			/// Creates file adapter by interface ID
			virtual SCOM::HResult CreateFileAdapter(IFile* file, SCOM_RIID uid, void **ppAdapter) = 0;


			/// Gets the FileSystem's Proactor, to make Proactor dispatch messages, call it's method in frame loop
			virtual Utils::Proactor<1>& Proactor() = 0;


			/// Returns parent folder of path
			virtual std::string PathGetParentFolder(const char* path) const = 0;
			/// Combines two paths
			virtual std::string PathCombine(const char* path1, const char* path2) const = 0;
			/// Makes full path from relative
			virtual std::string PathGetFull(const char* path) const = 0;
		};
	
	
	} // namespace
} // namespace


#endif // _IFILESYSTEM_H__