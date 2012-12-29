/*========================================================
* Reflection_fwd.h
* @author Sergey Mikhtonyuk
* @date 23 June 2009
=========================================================*/
#ifndef _REFLECTION_FWD_H__
#define _REFLECTION_FWD_H__

namespace Reflection
{
	enum TypeTag;
	enum ArchType;

	class Type;
	class ArrayType;
	class PointerType;
	class FunctionType;
	class UserType;

	class ClassDescriptor;
	class BaseClass;
	class Field;
	class Method;
	class Accessor;
	class ConstructDescriptor;
	class ParsingDescriptor;
	class AssignmentDescriptor;

} // namespace

#endif // _REFLECTION_FWD_H__