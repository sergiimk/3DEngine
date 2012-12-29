/*========================================================
* CINIFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _CINIFILEADAPTER_H__
#define _CINIFILEADAPTER_H__

#include "IINIFileAdapter.h"
#include "../Core/IAdapterFactory.h"
#include "../Core.COM/Implementations.h"
#include "../Core.COM/Intellectual.h"

namespace Core
{
	namespace FileSystem
	{
		/// Implementation of INI adapter interface
		/** @ingroup FileSystem */
		class NOVTABLE CINIFileAdapter : 
			public SCOM::ComRootObject<SCOM::MultiThreadModel>,
			public IINIFileAdapter
		{
		public:
			DECLARE_IMPLEMENTATION(CINIFileAdapter)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IINIFileAdapter)
			END_INTERFACE_MAP()

			~CINIFileAdapter();
		
			bool		IsInitialized();
			IFile*		WrappedFile();
			void		Parse();
			TFileMap&	FileMap() { return mFileMap; }
			void		ParseAsync(const boost::function<void ()>& handler);

			void FinalConstruct(IFile* pFile);
			void TrimLine(std::string& line);
			bool AddAttribute(TSection *section, std::string &attribute);

		protected:
			SCOM::ComPtr<IFile> mFile;
			TFileMap			mFileMap;
		};



		/// Adapter factory for IINIFileAdapter
		/** @ingroup FileSystem */
		class NOVTABLE CINIFileAdapterFactory : 
			public SCOM::ComRootObject<>,
			public IAdapterFactory
		{
		public:
			DECLARE_IMPLEMENTATION(CINIFileAdapterFactory)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IAdapterFactory)
			END_INTERFACE_MAP()
		
			SCOM::GUID**	SourceInterfaceList();
			SCOM::GUID**	DestInterfaceList();
			SCOM::HResult	GetAdapter(SCOM::IUnknown* object, SCOM_RIID iid, void **ppAdapter);
		};

	} // namespace
} // namespace


#endif // _CINIFILEADAPTER_H__