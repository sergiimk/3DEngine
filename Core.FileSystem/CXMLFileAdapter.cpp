/*========================================================
* CXMLFileAdapter.cpp
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/

#include "CXMLFileAdapter.h"
#include "IFileSystem.h"
#include <fstream>

namespace Core
{
	namespace FileSystem
	{
		//////////////////////////////////////////////////////////////////////////

		void CXMLFileAdapter::FinalConstruct(IFile *pFile)
		{
			mFile = pFile;
		}

		//////////////////////////////////////////////////////////////////////////

		CXMLFileAdapter::~CXMLFileAdapter()
		{
		}

		//////////////////////////////////////////////////////////////////////////

		bool CXMLFileAdapter::IsInitialized()
		{
			return mDocument.FirstChild() != 0;
		}

		//////////////////////////////////////////////////////////////////////////

		IFile* CXMLFileAdapter::WrappedFile()
		{
			return mFile;
		}

		//////////////////////////////////////////////////////////////////////////

		void CXMLFileAdapter::Parse()
		{
			mDocument.LoadFile(mFile->FullPath().c_str());
		}

		//////////////////////////////////////////////////////////////////////////

		TiXmlDocument& CXMLFileAdapter::GetDoc()
		{
			return mDocument;
		}

		//////////////////////////////////////////////////////////////////////////

		void CXMLFileAdapter::ParseAsync(boost::function<void ()>& handler)
		{
			mFile->FileSystem()->Proactor().ScheduleOperation(
				boost::function<void ()>(
					boost::bind(&CXMLFileAdapter::Parse, this)),
				handler);
		}

		//////////////////////////////////////////////////////////////////////////

		SCOM::GUID** CXMLFileAdapterFactory::SourceInterfaceList()
		{
			static const SCOM::GUID* pGuids[] = { &UUIDOF(IFile), 0 };
			return (SCOM::GUID**)&pGuids[0];
		}

		//////////////////////////////////////////////////////////////////////////

		SCOM::GUID** CXMLFileAdapterFactory::DestInterfaceList()
		{
			static const SCOM::GUID* pGuids[] = { &UUIDOF(IXMLFileAdapter), 0 };
			return (SCOM::GUID**)&pGuids[0];
		}

		//////////////////////////////////////////////////////////////////////////

		Core::SCOM::HResult CXMLFileAdapterFactory::GetAdapter(Core::SCOM::IUnknown *object, const Core::SCOM::GUID &iid, void **ppAdapter)
		{
			if(iid != UUIDOF(IXMLFileAdapter))
				return SCOM_E_NOINTERFACE;

			Core::SCOM::ComPtr<IFile> pFile(object);

			if(!pFile) 
				return SCOM_E_INVALIDARG;

			CXMLFileAdapter *pAdapter;
			scom_new<CXMLFileAdapter>(&pAdapter);
			pAdapter->FinalConstruct(pFile);

			*ppAdapter = static_cast<IXMLFileAdapter*>(pAdapter);
			return SCOM_S_OK;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace