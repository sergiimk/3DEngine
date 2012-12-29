/*========================================================
* BaseClass.h
* @author Sergey Mikhtonyuk
* @date 22 June 2009
=========================================================*/
#ifndef _BASECLASS_H__
#define _BASECLASS_H__

#include "ClassDescriptor.h"

namespace Reflection
{
	/// Describes base class of the type
	/** @ingroup Reflection */
	class BaseClass : public ClassDescriptor
	{
	public:
		/// Ctor
		BaseClass(const char* name, Type* type, Type* owner)
			: ClassDescriptor(name, type, owner, RL_DESC_BASE)
		{
		}
	};

} // namespace

#endif // _BASECLASS_H__