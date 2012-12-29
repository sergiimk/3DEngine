/*========================================================
* ParsingDescriptor.h
* @author Sergey Mikhtonyuk
* @date 09 July 2009
=========================================================*/
#ifndef _PARSINGDESCRIPTOR_H__
#define _PARSINGDESCRIPTOR_H__

#include "ClassDescriptor.h"
#include "typeof.h"

namespace Reflection
{

	/// Describes that class supports ToString() and TryParse() operations
	/** @ingroup Reflection */
	class ParsingDescriptor : public ClassDescriptor
	{
	public:

		ParsingDescriptor(Type* owner)
			: ClassDescriptor("io_support", type_of<void>(), owner, RL_DESC_SERVICE_PARSING)
		{
		}

		/// Converts value to string using the iostream operators
		virtual bool ToString(void* value, std::string& out) const = 0;

		/// String to value using the iostream operators
		virtual bool TryParse(void* value, const char* str) const = 0;

	};

	//////////////////////////////////////////////////////////////////////////

	template<class T>
	class ParsingDescriptorImpl : public ParsingDescriptor
	{
	public:
		/// Ctor
		ParsingDescriptorImpl(Type* owner)
			: ParsingDescriptor(owner)
		{
		}

		/// Converts value to string using the iostream operators
		bool ToString(void* value, std::string& out) const
		{
			std::ostringstream ss;
			ss << *(T*)value;
			out = ss.str();
			return true;			
		}

		/// String to value using the iostream operators
		bool TryParse(void* value, const char* str) const
		{
			std::istringstream ss(str);
			return !(!( ss >> *(T*)value));
		}
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _PARSINGDESCRIPTOR_H__