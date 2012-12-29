/*========================================================
* CExtension.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
=========================================================*/
#ifndef _CEXTENSION_H__
#define _CEXTENSION_H__

#include "IExtension.h"
#include "../Core.COM/Implementations.h"
#include <boost/scoped_ptr.hpp>

namespace Core
{
	
	/// Implementation of IExtension interface
	/** @ingroup Core */
	class NOVTABLE CExtension : 
		public SCOM::ComRootObject<>,
		public IExtension
	{
		typedef std::map<std::string, std::string> TParameterMap;

	public:
		DECLARE_IMPLEMENTATION(CExtension)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IExtension)
		END_INTERFACE_MAP()

		IPluginShadow*		Extender()			{ return pExtender; }
		IExtensionPoint*	ExtensionPoint()	{ return pExtensionPoint; }
		const SCOM::GUID&	ImplClassID()		{ return mImplClassID; }
		const char*			getParameter(const char* name)		
		{
			TParameterMap::const_iterator it = mParameterMap.find(name);
			return (it == mParameterMap.end()) ? 0 : it->second.c_str();
		}
	
	/* internal: */
		IPluginShadow*		pExtender;
		IExtensionPoint*	pExtensionPoint;
		SCOM::GUID			mImplClassID;
		TParameterMap		mParameterMap;
	};


} // namespace


#endif // _CEXTENSION_H__