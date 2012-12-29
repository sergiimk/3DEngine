/*========================================================
* AssignmentDescriptor.h
* @author Sergey Mikhtonyuk
* @date 09 July 2009
=========================================================*/
#ifndef _ASSIGNMENTDESCRIPTOR_H__
#define _ASSIGNMENTDESCRIPTOR_H__

#include "ClassDescriptor.h"
#include "typeof.h"

namespace Reflection
{

	/// Describes the custom assignment logic of type
	/** @ingroup Reflection */
	class AssignmentDescriptor : public ClassDescriptor
	{
	public:
		typedef void (*TAs)(void* a, void* b);

		AssignmentDescriptor(TAs assign, Type* owner)
			: ClassDescriptor("io_support", type_of<void>(), owner, RL_DESC_SERVICE_ASSIGN),
			mAs(assign)
		{
		}

		/// Calls the assignment
		void Assign(void* a, void* b) const
		{
			mAs(a, b);
		}

	private:
		TAs mAs;
	};
} // namespace


#endif // _ASSIGNMENTDESCRIPTOR_H__