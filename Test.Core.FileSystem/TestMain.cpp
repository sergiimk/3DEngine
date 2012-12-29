#include "../Core.COM/Module.h"
#include "../Core.FileSystem/FileSystem.h"
#include "../Core.COM/Intellectual.h"
#include "Misc.h"

#define BOOST_TEST_MODULE FileSystem test
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <crtdbg.h>

using namespace Core;
using namespace FileSystem;

SCOM::Module module("Core.FileSystem.dll");


BOOST_AUTO_TEST_SUITE( my_suite1 );


BOOST_AUTO_TEST_CASE( TestForSingleton )
{
	SCOM::Module m2("Core.FileSystem.dll");

	SCOM::ComPtr<IFileSystem> fs1;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs1.wrapped()))));

	SCOM::ComPtr<IFileSystem> fs2;
	BOOST_CHECK(SCOM_SUCCEEDED(m2.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs2.wrapped()))));

	BOOST_CHECK_EQUAL(fs1, fs2);
}


BOOST_AUTO_TEST_CASE( TestHandles )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFile> fh = fs->GetResource("TestMain.cpp");
	BOOST_CHECK(fh);

	BOOST_CHECK_NE(fh->FullPath().find("/TestMain.cpp"), -1);

	SCOM::ComPtr<IFolder> fld = fh->Parent();
	BOOST_CHECK(fld);

	BOOST_CHECK_NE(fld->FullPath().find("/Test.Core.FileSystem"), -1);
	BOOST_CHECK_EQUAL(fld->BaseName(), std::string("Test.Core.FileSystem"));
}

BOOST_AUTO_TEST_CASE( testRoot )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFolder> root =  fs->GetResource("c:/");
	BOOST_CHECK(root);

	SCOM::ComPtr<IFolder> pf = root->FindChild("Program Files");
	BOOST_CHECK(pf);
}


BOOST_AUTO_TEST_CASE( TestFolderChildren )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFolder> pFld = fs->GetResource("Debug");
	
	if(!pFld)
		pFld = fs->GetResource("Release");

	BOOST_CHECK(pFld);

	const std::vector<IResource*>& children = pFld->GetChildren();
	SCOM::ComPtr<IResource> pFound;
	for(size_t i = 0; i < children.size(); ++i)
		if(children[i]->FullPath().find("TestMain.obj") != -1)
			pFound = children[i];

	BOOST_CHECK(pFound);
}


BOOST_AUTO_TEST_CASE( TestFileReading )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFolder> pFld1 = fs->CurrentFolder();

	SCOM::ComPtr<IFolder> pFld2 = pFld1->Parent();

	pFld1.Release();
	pFld1 = pFld2->FindChild("Resources");
	BOOST_CHECK(pFld1);

	SCOM::ComPtr<IFile> pFile = pFld1->FindChild("PluginDescSample.xml");
	BOOST_CHECK(pFile);

	std::fstream& ifs = pFile->Stream();
	
	BOOST_CHECK(ifs.is_open());

	char c;
	while(ifs.get(c));

	ifs.close();
}


BOOST_AUTO_TEST_CASE( TestXMLAdapter )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));
	
	SCOM::ComPtr<IFile> pFile = fs->GetResource("../Resources/PluginDescSample.xml");
	BOOST_CHECK(pFile);

	SCOM::ComPtr<IXMLFileAdapter> pXMLAdapter;
	BOOST_CHECK(SCOM_SUCCEEDED(fs->CreateFileAdapter(pFile, UUID_PPV(IXMLFileAdapter, pXMLAdapter.wrapped()))));
	BOOST_CHECK(pXMLAdapter);

	BOOST_CHECK_EQUAL(pXMLAdapter->IsInitialized(), false);
	pXMLAdapter->Parse();
	BOOST_CHECK_EQUAL(pXMLAdapter->IsInitialized(), true);

	TiXmlDocument& doc = pXMLAdapter->GetDoc();

	doc.Accept(&CTestVisitor());
}



BOOST_AUTO_TEST_CASE( TestINIAdapter )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFile> pFile = fs->GetResource("../Resources/ConfigSample.ini");
	BOOST_CHECK(pFile);

	SCOM::ComPtr<IINIFileAdapter> pINIAdapter;
	BOOST_CHECK(SCOM_SUCCEEDED(fs->CreateFileAdapter(pFile, UUID_PPV(IINIFileAdapter, pINIAdapter.wrapped()))));
	BOOST_CHECK(pINIAdapter);

	BOOST_CHECK_EQUAL(pINIAdapter->IsInitialized(), false);
	pINIAdapter->Parse();
	BOOST_CHECK_EQUAL(pINIAdapter->IsInitialized(), true);
}



BOOST_AUTO_TEST_CASE( TestReadAll )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFile> pFile = fs->GetResource("../Resources/PluginDescSample.xml");
	BOOST_CHECK(pFile);

	char *buf;
	std::ios::streamoff size;
	pFile->ReadFile(&buf, size);

	BOOST_CHECK_NE((int)size, 0);

	delete[] buf;
}

BOOST_AUTO_TEST_CASE( TestArchives )
{
	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IFile> stxt2 = fs->GetResource("../Resources/test_arch.zip/sub/sub.txt", true);
	BOOST_CHECK(stxt2);

	SCOM::ComPtr<IResource> pRes = fs->GetResource("../Resources/test_arch.zip");
	BOOST_CHECK(pRes);

	// Test interface map
	SCOM::ComPtr<IArchive> pArch = pRes;
	{
		SCOM::ComPtr<IResourceContainer> pResCont = pRes;
		SCOM::ComPtr<IFile> pFile = pRes;
		BOOST_CHECK(pRes); BOOST_CHECK(pResCont); BOOST_CHECK(pFile); BOOST_CHECK(pArch);
	}

	// Navigation test
	SCOM::ComPtr<IFolder> sub = pArch->FindChild("sub");
	BOOST_CHECK(sub);

	SCOM::ComPtr<IFile> stxt = sub->FindChild("sub.txt");
	BOOST_CHECK(stxt);

	// Unpack test
	char *buf;
	std::ios::streamoff size;
	stxt->ReadFile(&buf, size);

	BOOST_CHECK_NE((int)size, 0);

	delete[] buf;

	BOOST_CHECK_EQUAL(stxt, stxt2);
}

BOOST_AUTO_TEST_CASE( testTravers )
{
	class _testTraverser : public IFSTraverser
	{
		bool VisitFolder(IFolder* fld) 
		{ 
			return true; 
		}
		void LeaveFolder(IFolder* fld) 
		{
		}
		bool VisitArchive(IArchive* arch) 
		{ 
			return true; 
		}
		void LeaveArchive(IArchive* arch) 
		{
		}
		void VisitFile(IFile* file) 
		{
		}
	} tr;

	SCOM::ComPtr<IFileSystem> fs;
	BOOST_CHECK(SCOM_SUCCEEDED(module.CreateInstance(CLSID_CFileSystem, UUID_PPV(IFileSystem, fs.wrapped()))));

	SCOM::ComPtr<IResource> pRes = fs->GetResource("../Resources");

	pRes->Accept(&tr);
}

BOOST_AUTO_TEST_SUITE_END();