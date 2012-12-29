/*========================================================
* IINIFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _IINIFILEADAPTER_H__
#define _IINIFILEADAPTER_H__

#include "IFile.h"
#include "../Core.COM/Interfaces.h"
#include "../Core.FileSystem.TinyXML/tinyxml.h"
#include <map>

namespace Core
{
	namespace FileSystem
	{
		/// File adapter interface for INI
		/** @ingroup FileSystem */
		SCOM_INTERFACE(IINIFileAdapter, "5d64c487-1787-4603-8553-ae05485ba236", SCOM::IUnknown)
		{
		public:
			typedef std::map<std::string, std::string> TSection;
			typedef std::map<std::string, TSection*> TFileMap;

			/// Determines if document is already parsed
			virtual bool IsInitialized() = 0;

			/// Returns the file, wrapped by adapter
			virtual IFile* WrappedFile() = 0;

			/// Returns the INI-file map
			virtual TFileMap& FileMap() = 0;

			/// Initiate the file parsing
			virtual void Parse() = 0;
			
			/// Initiates parsing in the background thread (see IFile::ReadFileAsync for details)
			virtual void ParseAsync(const boost::function<void ()>& handler) = 0;
		};	
	
	} // namespace
} // namespace


#endif // _IINIFILEADAPTER_H__