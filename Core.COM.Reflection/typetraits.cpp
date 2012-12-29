/*========================================================
* typetraits.cpp
* @author Sergey Mikhtonyuk
* @date 21 June 2009
=========================================================*/
#include "TypeTag.h"

namespace Reflection
{

	const char* get_type_name(TypeTag tag)
	{
		switch (tag) { 
		  case RL_T_VOID:
			  return "void";
		  case RL_T_CHAR:
			  return "char";
		  case RL_T_UCHAR:
			  return "unsigned char";
		  case RL_T_SHORT:
			  return "short";
		  case RL_T_USHORT:
			  return "unsigned short";
		  case RL_T_BOOL:
			  return "bool";
		  case RL_T_INT:
			  return "int";
		  case RL_T_UINT:
			  return "unsigned int";
		  case RL_T_LONG:
			  return "long";
		  case RL_T_ULONG:
			  return "unsigned long";
		  case RL_T_LONGLONG:
			  return "long long";
		  case RL_T_ULONGLONG:
			  return "unsigned long long";
		  case RL_T_FLOAT:
			  return "float";
		  case RL_T_DOUBLE:
			  return "double";
		  default:
			  return "unknown";
		}
	}

} // namespace
