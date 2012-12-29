/*========================================================
* TypeParsing.h
* @author Sergey Mikhtonyuk
* @date 17 August 2009
=========================================================*/
#ifndef _TYPEPARSING_H__
#define _TYPEPARSING_H__

#include "../../Engine.Graphics/Interfaces/EffectTypes.h"
#include "../../Engine.Graphics/Interfaces/MeshTypes.h"
#include "../../Engine.Graphics/Interfaces/SSurfaceDesc.h"
#include <iosfwd>

namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////
		const char* EElemUsage_ToString(EElemUsage val);
		EElemUsage EElemUsage_FromString(const char* s);

		std::ostream& operator << (std::ostream& os, const EElemUsage& fmt);
		std::istream& operator >> (std::istream& is, EElemUsage& fmt);
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		const char* EElemType_ToString(EElemType val);
		EElemType EElemType_FromString(const char* s);

		std::ostream& operator << (std::ostream& os, const EElemType& fmt);
		std::istream& operator >> (std::istream& is, EElemType& fmt);
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		const char* EEffectParam_ToString(EEffectParam val);
		EEffectParam EEffectParam_FromString(const char* s);

		std::ostream& operator << (std::ostream& os, const EEffectParam& fmt);
		std::istream& operator >> (std::istream& is, EEffectParam& fmt);
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		const char* EEffectCap_ToString(EEffectCap val);
		EEffectCap EEffectCap_FromString(const char* s);

		std::ostream& operator << (std::ostream& os, const EEffectCap& fmt);
		std::istream& operator >> (std::istream& is, EEffectCap& fmt);
		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif // _TYPEPARSING_H__