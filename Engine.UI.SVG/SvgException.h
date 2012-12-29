/*========================================================
* SvgException.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGEXCEPTION_H_
#define _SVGEXCEPTION_H_

#include <exception>
#include <string>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			/// SvgException class
			/** Thrown when exceptional situation is occurred.
			*	@ingroup SVG
			*/
			class SvgException : public std::exception
			{
			public:
				/// Creates a new instance of SvgException.
				SvgException();

				/// Dtor
				virtual ~SvgException() throw();

				/// Creates a new instance of SvgExceprion with error message.
				SvgException(const std::string& what);

				/// Inherited from std::exception
				/** Returns error message.
				*	Can't throw.
				*	@return Error message.
				*/
				virtual const char* what() const throw();
			private:
				std::string m_what;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	/*_SVGEXCEPTION_H_*/
