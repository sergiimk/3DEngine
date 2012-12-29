/*========================================================
* CLogicController.cpp
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#include "CLogicController.h"
#include "../Interfaces/ICmpLogic.h"

namespace Engine
{
	//////////////////////////////////////////////////////////////////////////

	void CLogicController::RegisterLogicComponent(Engine::ICmpLogic *logic)
	{
		SThinkContext* context = logic->getThinkContext();
		context->TimeSinceLastThink = 0;
		mComponents.insert(logic);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogicController::UnRegisterLogicComponent(ICmpLogic* logic)
	{
		TComponentSet::iterator it = mComponents.find(logic);
		ASSERT_STRICT(it != mComponents.end());
		mComponents.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogicController::Notify(double time_delta)
	{
		for(TComponentSet::iterator it = mComponents.begin();
			it != mComponents.end();
			++it)
		{
			ICmpLogic* logic = *it;
			SThinkContext* context = logic->getThinkContext();

			if(context->Flags == THINK_EACH_FRAME)
			{
				context->TimeSinceLastThink = time_delta;
				logic->Think();
			}
			else if (context->Flags = THINK_SCHEDULED)
			{
				context->NextThinkTime -= time_delta;
				context->TimeSinceLastThink += time_delta;

				if(context->NextThinkTime <= 0)
				{
					context->NextThinkTime = 0;
					logic->Think();
					context->TimeSinceLastThink = 0;
				}
			}
			else
			{
				ASSERT_STRICT(false);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace