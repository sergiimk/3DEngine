/*========================================================
* CCmpLogicBase.h
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#ifndef _CCMPLOGICBASE_H__
#define _CCMPLOGICBASE_H__

#include "../Interfaces/ICmpLogic.h"
#include "../../Core.COM/Implementations.h"
#include "../Interfaces/GlobalEnvironment.h"
#include "../Interfaces/ILogicController.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	struct SLogicDescBase : public SComponentDesc
	{
		EThinkFlags ThinkFlag;	///< type of think scheduling

		SLogicDescBase(const Core::SCOM::GUID* clsid)
			:	SComponentDesc(clsid),
			ThinkFlag(THINK_NEVER)
		{}

		SLogicDescBase(const Core::SCOM::GUID* clsid, EThinkFlags thinkFlag)
			:	SComponentDesc(clsid),
			ThinkFlag(thinkFlag)
		{}

		void ResetDefaults() 
		{
			ThinkFlag = THINK_NEVER;
		}
	};

	//////////////////////////////////////////////////////////////////////////

	/// Base implementation of logical component
	/** @ingroup Engine */
	class NOVTABLE CCmpLogicBase : 
		public Core::SCOM::ComRootObject<>,
		public ICmpLogic
	{
	public:
		
		DECLARE_IMPLEMENTATION(CCmpLogicBase)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ICmpLogic)
			INTERFACE_ENTRY(IComponent)
		END_INTERFACE_MAP()

		CCmpLogicBase() : mEntity(0)
		{
			mThinkContext.Flags = THINK_NEVER;
			mThinkContext.TimeSinceLastThink = 0;
			mThinkContext.NextThinkTime = 0;
		}

		~CCmpLogicBase()
		{
			if(mThinkContext.Flags != THINK_NEVER)
				gEnv->LogicController->UnRegisterLogicComponent(this);
		}
	
		const char* getComponentName()	const { return "Logic"; }

		IEntity*	getEntity()			const { return mEntity; }

		bool		Bind(IEntity* entity, SComponentDesc* desc)
		{
			SLogicDescBase* ld = (SLogicDescBase*)desc;

			mEntity = entity;
			ChangeThinkType(ld->ThinkFlag);
			return true;
		}

		SThinkContext* getThinkContext() { return &mThinkContext; }

		void setThinkFlag(EThinkFlags flag) { ChangeThinkType(flag); }

	private:

		void ChangeThinkType(EThinkFlags newType)
		{
			if(mThinkContext.Flags == newType) return;

			mThinkContext.Flags = newType;

			if(mThinkContext.Flags == THINK_NEVER)
				gEnv->LogicController->UnRegisterLogicComponent(this);
			else
				gEnv->LogicController->RegisterLogicComponent(this);
		}

	private:
		IEntity*		mEntity;
		SThinkContext	mThinkContext;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _CCMPLOGICBASE_H__