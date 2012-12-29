/*========================================================
* CExtensionPoint.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
=========================================================*/
#ifndef _CEXTENSIONPOINT_H__
#define _CEXTENSIONPOINT_H__

#include "IExtensionPoint.h"
#include "../Core.COM/Implementations.h"

namespace Core
{
	
	/// Implementation of IExtensionPoint interface
	/** @ingroup Core */
	class NOVTABLE CExtensionPoint : 
		public SCOM::ComRootObject<>,
		public IExtensionPoint
	{
	public:
		DECLARE_IMPLEMENTATION(CExtensionPoint)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IExtensionPoint)
		END_INTERFACE_MAP()

		const std::string&	ID()						{ return mName; }
		const std::string&	UniqueID()					{ return mFullName; }
		IPluginShadow*		Provider()					{ return mProvider; }
		const SCOM::GUID&	InterfaceID()				{ return mInterfaceID; }
		size_t				getExtensionCount()			{ return mExtensions.size(); }
		IExtension*			getExtension(size_t index)	{ return mExtensions[index]; }
	
	/* internal: */
		std::string					mName;
		std::string					mFullName;
		IPluginShadow*				mProvider;
		SCOM::GUID					mInterfaceID;
		std::vector<IExtension*>	mExtensions;
	};


} // namespace


#endif // _CEXTENSIONPOINT_H__