/*========================================================
* CXMLFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _CXMLFILEADAPTER_H__
#define _CXMLFILEADAPTER_H__

#include "IXMLFileAdapter.h"
#include "../Core/IAdapterFactory.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"

namespace Core
{
	namespace FileSystem
	{
		/// Implementation of XML adapter interface
		/** This is just a wrapper class to integrate TinyXML
		  * into the system 
		  *
		  * @ingroup FileSystem */
		class NOVTABLE CXMLFileAdapter : 
			public SCOM::ComRootObject<SCOM::MultiThreadModel>,
			public IXMLFileAdapter
		{
		public:
			DECLARE_IMPLEMENTATION(CXMLFileAdapter)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IXMLFileAdapter)
			END_INTERFACE_MAP()

			~CXMLFileAdapter();

			void			FinalConstruct(IFile* pFile);
		
			bool			IsInitialized();
			IFile*			WrappedFile();
			void			Parse();
			TiXmlDocument&	GetDoc();
			void			ParseAsync(boost::function<void ()>& handler);

		protected:
			SCOM::ComPtr<IFile> mFile;
			TiXmlDocument mDocument;
		};



		/// Adapter factory for IXMLFileAdapter
		/** @ingroup FileSystem */
		class NOVTABLE CXMLFileAdapterFactory : 
			public SCOM::ComRootObject<>,
			public IAdapterFactory
		{
		public:
			DECLARE_IMPLEMENTATION(CXMLFileAdapterFactory)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IAdapterFactory)
			END_INTERFACE_MAP()
		
			SCOM::GUID**	SourceInterfaceList();
			SCOM::GUID**	DestInterfaceList();
			SCOM::HResult	GetAdapter(SCOM::IUnknown* object, SCOM_RIID iid, void **ppAdapter);
		};

	} // namespace
} // namespace


#endif // _CXMLFILEADAPTER_H__