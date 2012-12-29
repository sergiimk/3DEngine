/*========================================================
* CFSFrameWrapper.h
* @author Sergey Mikhtonyuk
* @date 10 April 2009
=========================================================*/
#ifndef _CFSFRAMEWRAPPER_H__
#define _CFSFRAMEWRAPPER_H__

#include "../Interfaces/IFrameListener.h"
#include "../../Core.FileSystem/IFileSystem.h"
#include "../../Core.COM/Implementations.h"
#include "../../Core.COM/Intellectual.h"

namespace Engine
{
	/// Frame wrapper for file system
	/** Each frame initiates event dispatching
	  * @ingroup Engine */
	class NOVTABLE CFSFrameWrapper : 
		public Core::SCOM::ComRootObject<>,
		public IFrameListener
	{
	public:
		DECLARE_IMPLEMENTATION(CFSFrameWrapper)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IFrameListener)
		END_INTERFACE_MAP()
	
		CFSFrameWrapper();
		virtual void Initialize(IMainLoop *pMainLoop);
		virtual int OnFrame();
	};



} // namespace


#endif // _CFSFRAMEWRAPPER_H__