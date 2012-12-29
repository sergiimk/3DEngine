/*========================================================
* CBaseResource.h
* @author Sergey Mikhtonyuk
* @date 21 May 2009
=========================================================*/
#ifndef _CBASERESOURCE_H__
#define _CBASERESOURCE_H__

#include "../Core.Utils/URL.h"
#include <cassert>
#include "../Core.Utils/EnvironmentDefs.h"

namespace DXRenderer
{
	/// Base class that implements common resource behavior
	/** @ingroup DX9 */
	template<class IRES>
	class CBaseResource : public IRES
	{
	public:
		CBaseResource() : mRefs(0) { }

		//////////////////////////////////////////////////////////////////////////

		bool					IsLoaded() const	{ return mRefs != 0; }
		void					AddUser()			{ ASSERT_STRICT(mRefs >= 0); if(!mRefs++) Load(); }
		void					RemoveUser()		{ ASSERT_STRICT(mRefs >  0); if(!(--mRefs)) Unload(); }
		Utils::URL*				GetURL()			{ return &mUrl; }

		//////////////////////////////////////////////////////////////////////////

		/// Special version for resources that relinked from one parent to another to preserve right ref-count
		void					AddUser(int uc)		
		{ 
			ASSERT_STRICT(mRefs >=  0);
			mRefs += uc;
			if(mRefs && mRefs == uc) Load(); // was unloaded and linked to loaded parent
			if(!mRefs) Unload(); // Resource should properly withstand multiple Unload()s
		}

		/// Special version for resources that relinked from one parent to another to preserve right ref-count
		void					RemoveUser(int uc)
		{
			ASSERT_STRICT(mRefs >=  uc);
			mRefs -= uc; // No unload called on relink
		}

		protected:

			Utils::URL		mUrl;

			int				mRefs;
	};

} // namespace

#endif	// _CBASERESOURCE_H__