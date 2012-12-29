/*========================================================
* IUIManager.h
* @author Sergey Mikhtonyuk
* @date 20 September 2009
=========================================================*/
#ifndef _IUIMANAGER_H__
#define _IUIMANAGER_H__

#include "../../Core.COM/Interfaces.h"
#include "../../Engine.Graphics.VG/VGLib_fwd.h"

namespace Engine
{
	namespace UI
	{
		//////////////////////////////////////////////////////////////////////////

		/// User interface manager
		/** @ingroup UI */
		SCOM_INTERFACE(IUIManager, "a0218d5b-7368-4fc0-a18e-8d9c8bfa7dc0", Core::SCOM::IUnknown)
		{
		public:
		
			/// Creates new vector graphics layer
			virtual void CreateLayer(VG::ILayer** outLayer) = 0;
		};
		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif // _IUIMANAGER_H__