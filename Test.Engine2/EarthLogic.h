/*========================================================
* EarthLogic.h
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#ifndef _EARTHLOGIC_H__
#define _EARTHLOGIC_H__

#include "../Engine/Scene/CCmpLogicBase.h"



class NOVTABLE CEarthLogic : public CCmpLogicBase
{
public:
	
	DECLARE_IMPLEMENTATION_DERIVED(CEarthLogic, CCmpLogicBase)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(ICmpLogic)
		INTERFACE_ENTRY_CHAIN(CCmpLogicBase)
	END_INTERFACE_MAP()

	bool Bind(IEntity* entity, SComponentDesc* desc)
	{
		if(!CCmpLogicBase::Bind(entity, desc)) return false;

		sp = (ICmpSpatialNode*)entity->getComponent(UUIDOF(ICmpSpatialNode));
		
		return sp ? true : false;
	}

	void Think()
	{
		float time_delta = (float)getThinkContext()->TimeSinceLastThink;
		VML::Quat r = VML::Quat::rotationY(time_delta / -6.0f);
		sp->setRotation(sp->getRotation() * r);
	}

private:
	ICmpSpatialNode* sp;
};

// {a46a711a-29c6-4b17-803c-85e12cdb859e} 
static const Core::SCOM::GUID CLSID_CEarthLogic = 
{ 0xa46a711a, 0x29c6, 0x4b17, { 0x80, 0x3c, 0x85, 0xe1, 0x2c, 0xdb, 0x85, 0x9e } };

#endif // _EARTHLOGIC_H__