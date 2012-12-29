/*========================================================
* SvgStylizable.h
* @author Roman Prikhodcheko
* @date 20 May 2009
=========================================================*/


#ifndef _SVGSTYLIZABLE_H_
#define _SVGSTYLIZABLE_H_

#include "SvgStyle.h"
#include <string>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			/// SvgStylizable interface
			/** Base interface for all independent svg elements,
			*	that have style
			*	@ingroup SVG
			*/
			class SvgStylizable
			{
			public:
				/// Common style name method
				/** Name of the style, that is defined in CSS style sheet.
				*/
				const std::string& CommonStyleName() const;

				/// Set common style name method
				/**	Applies style defined in CSS sheet
				*	@param StyleName Name of the style in the CSS sheet
				*/
				void SetCommonStyleName(const std::string& StyleName);

				/// Style method
				/** Returns style of an svg element.
				*/
				SvgStyle& Style();

				/// Set style method
				/** Sets style of an svg element.
				*   @param style Reference to style than will be applied for object. 
				*/
				void SetStyle(const SvgStyle& style);
			private:
				std::string m_commonStyle;
				SvgStyle m_style;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	// _SVGSTYLIZABLE_H_
