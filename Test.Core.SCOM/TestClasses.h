/*========================================================
* TestClasses.h
* @author Sergey Mikhtonyuk
* @date 23 July 2009
=========================================================*/
#include "../Core.COM/Implementations.h"

//////////////////////////////////////////////////////////////////////////

SCOM_INTERFACE(ITest, "835ca580-8bc7-40a7-913e-49bbb4987085", Core::SCOM::IUnknown)
{
public:

	virtual void Test() = 0;
};

SCOM_INTERFACE(ITest2, "123ca580-8bc7-40a7-913e-49bbb4987085", Core::SCOM::IUnknown)
{
public:

	virtual void Test() = 0;
};

//////////////////////////////////////////////////////////////////////////

class NOVTABLE CTest : 
	public Core::SCOM::ComRootObject<>,
	public ITest,
	public ITest2
{
public:
	
	DECLARE_IMPLEMENTATION(CTest)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(ITest)
		INTERFACE_ENTRY(ITest2)
	END_INTERFACE_MAP()

	void Test()
	{
	}
};

//////////////////////////////////////////////////////////////////////////
