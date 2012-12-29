/*========================================================
* CUIManager.h
* @author Sergey Mikhtonyuk
* @date 20 September 2009
=========================================================*/
#ifndef _CUIMANAGER_H__
#define _CUIMANAGER_H__

#include "../Interfaces/IUIManager.h"
#include "../../Core.COM/Implementations.h"

namespace Engine
{
	namespace UI
	{

		/// Implementation of UI manager
		/** @ingroup UI */
		class NOVTABLE CUIManager : 
			public Core::SCOM::ComRootObject<>,
			public IUIManager
		{
		public:
			
			DECLARE_IMPLEMENTATION(CUIManager)
		
			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IUIManager)
			END_INTERFACE_MAP()

			void CreateLayer(VG::ILayer** outLayer);
		};

	} // namespace
} // namespace

#endif // _CUIMANAGER_H__