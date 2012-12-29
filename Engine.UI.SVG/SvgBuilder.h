/*========================================================
* SvgBuilder.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGBUILDER_H_
#define _SVGBUILDER_H_

#include <string>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgGroup;
			class SvgObject;
			class SvgPath;
			class SvgPathItem;
			class SvgStylizable;
			class SvgStyle;

			/// SvgBuilder class
			/** Base interface for builders of svg objects.
			* Write your own builder to change the algorithm of parsing svg code
			* @ingroup SVG */
			class SvgBuilder
			{
			public:
				virtual ~SvgBuilder()	{				}

				/// Construct group method.
				/** Builds new SvgGroup. Doesn't need parameters.
				* 
				*	@return Pointer to created SvgGroup object.
				*/
				virtual SvgGroup* ConstructGroup() const = 0;

				/// Construct path method.
				/** Builds new SvgPath from "d" attribute of the <path/> tag.
				*
				*	@param D_Attribute Value of "d" attribute of the <path/> tag. 
				*	@return Pointer to created SvgPath
				*/
				virtual SvgPath* ConstructPath(const std::string& D_Attribute) = 0;

				/// Construct path item method.
				/** Builds new SvgPathItem from an element of "d" attribute of the <path/> tag
				*
				*	@param TextItem element of "d" attribute of the <path/> tag.
				*	@return Pointer to created SvgPathItem
				*/
				virtual SvgPathItem* ConstructPathItem(const std::string& TextItem) /*const*/ = 0;

				/// Override style method.
				/** Adds style properties, described in TextStyle parameter to object.
				*	Doesn't modify any described properties.
				*
				*	@param TextStyle Style properties in CSS format
				*	@param Object Object, that needs for style overriding
				*/
				virtual void OverrideStyle(const std::string& TextStyle, SvgObject* Object) /*const*/ = 0;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	// _SVGBUILDER_H_
