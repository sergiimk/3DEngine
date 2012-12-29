/*========================================================
* IXMLFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _IXMLFILEADAPTER_H__
#define _IXMLFILEADAPTER_H__

#include "IFile.h"
#include "../Core.COM/Interfaces.h"
#include "../Core.FileSystem.TinyXML/tinyxml.h"

namespace Core
{
	namespace FileSystem
	{
		/// File adapter interface for XML
		/** @ingroup FileSystem */
		SCOM_INTERFACE(IXMLFileAdapter, "f4d1c8d7-c45a-4b52-9fe2-9464dcc2d588", SCOM::IUnknown)
		{
		public:
			/// Determines if document is already parsed
			virtual bool IsInitialized() = 0;

			/// Returns the file, wrapped by adapter
			virtual IFile* WrappedFile() = 0;

			/// Returns the root xml element
			virtual TiXmlDocument& GetDoc() = 0;

			/// Initiate the file parsing
			virtual void Parse() = 0;
			
			/// Initiates parsing in the background thread (see IFile::ReadFileAsync for details)
			virtual void ParseAsync(boost::function<void ()>& handler) = 0;
		};	
	
	} // namespace
} // namespace


#endif // _IXMLFILEADAPTER_H__