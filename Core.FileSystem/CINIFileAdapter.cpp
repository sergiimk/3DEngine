/*========================================================
* CINIFileAdapter.cpp
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/

#include "CINIFileAdapter.h"
#include "IFileSystem.h"
#include "FSExceptions.h"
#include <fstream>

namespace Core
{
	namespace FileSystem
	{
		//////////////////////////////////////////////////////////////////////////
		
		void CINIFileAdapter::FinalConstruct(IFile *pFile)
		{
			mFile = pFile;
		}

		//////////////////////////////////////////////////////////////////////////

		CINIFileAdapter::~CINIFileAdapter()
		{
			for(TFileMap::iterator it = mFileMap.begin(); it != mFileMap.end(); ++it)
				delete it->second;
		}

		//////////////////////////////////////////////////////////////////////////

		bool CINIFileAdapter::IsInitialized()
		{
			return mFileMap.size() != 0;
		}

		//////////////////////////////////////////////////////////////////////////

		IFile* CINIFileAdapter::WrappedFile()
		{
			return mFile;
		}

		//////////////////////////////////////////////////////////////////////////

		void CINIFileAdapter::Parse()
		{
			char *buf;
			std::ios::streamoff size;
			mFile->ReadFile(&buf, size);

			std::string line;
			std::istringstream ss(std::string(buf, size));
			std::string sectionName;
			TSection* currentSection = 0;
			delete[] buf;

			while(true)
			{
				// Save current section before leaving
				if(ss.eof())
				{
					if(currentSection)
						mFileMap.insert(std::make_pair(sectionName, currentSection));
					break;
				}

				// Read line
				std::getline(ss, line);

				TrimLine(line);

				// if empty or comment
				if(line.length() == 0 || line[0] == ';' || line[0] == '#')
					continue;

				// is section
				if(line[0] == '[' && line[line.length() - 1] == ']')
				{
					if(currentSection)
						mFileMap.insert(std::make_pair(sectionName, currentSection));

					currentSection = new TSection();
					sectionName = line.substr(1, line.length() - 2);
				}

				// found the attribute
				else if(!currentSection || !AddAttribute(currentSection, line))
					throw FSParsingException("bad INI format");
			}
		}

		//////////////////////////////////////////////////////////////////////////

		void CINIFileAdapter::TrimLine(std::string& line)
		{
			line.erase(0, line.find_first_not_of("\r\n\t ") );
			line.erase( line.find_last_not_of("\r\n\t ") + 1 , line.npos );
		}

		//////////////////////////////////////////////////////////////////////////

		bool CINIFileAdapter::AddAttribute(TSection *section, std::string &attribute)
		{
			size_t delimiterPosition = attribute.find('=');

			if(delimiterPosition == -1) return false;

			std::string name = attribute.substr(0, delimiterPosition);
			std::string value = attribute.substr(delimiterPosition + 1);

			TrimLine(name);
			TrimLine(value);

			section->insert(std::make_pair(name, value));

			return true;
		}

		//////////////////////////////////////////////////////////////////////////

		void CINIFileAdapter::ParseAsync(const boost::function<void ()>& handler)
		{
			mFile->FileSystem()->Proactor().ScheduleOperation(
				boost::function<void ()>(
					boost::bind(&CINIFileAdapter::Parse, this)),
				handler);
		}

		//////////////////////////////////////////////////////////////////////////

		SCOM::GUID** CINIFileAdapterFactory::SourceInterfaceList()
		{
			static const SCOM::GUID* pGuids[] = { &UUIDOF(IFile), 0 };
			return (SCOM::GUID**)&pGuids[0];
		}
	
		//////////////////////////////////////////////////////////////////////////
		
		SCOM::GUID** CINIFileAdapterFactory::DestInterfaceList()
		{
			static const SCOM::GUID* pGuids[] = { &UUIDOF(IINIFileAdapter), 0 };
			return (SCOM::GUID**)&pGuids[0];
		}

		//////////////////////////////////////////////////////////////////////////

		Core::SCOM::HResult CINIFileAdapterFactory::GetAdapter(Core::SCOM::IUnknown *object, const Core::SCOM::GUID &iid, void **ppAdapter)
		{
			if(iid != UUIDOF(IINIFileAdapter))
				return SCOM_E_NOINTERFACE;

			Core::SCOM::ComPtr<IFile> pFile(object);

			if(!pFile) 
				return SCOM_E_INVALIDARG;

			CINIFileAdapter *pAdapter;
			scom_new<CINIFileAdapter>(&pAdapter);
			pAdapter->FinalConstruct(pFile);

			*ppAdapter = static_cast<IINIFileAdapter*>(pAdapter);
			return SCOM_S_OK;
		}

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace