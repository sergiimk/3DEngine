/*========================================================
* SvgBoostBuilder.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGBOOSTBUILDER_H_
#define _SVGBOOSTBUILDER_H_

#include "SvgBuilder.h"
#include "SvgPathItem.h"
#include <vector>
#include <hash_map>


namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			enum SvgCommand;
			class vector;
			struct Color;
			class SvgStylizable;
			class SvgErrorHandler;

			/// SvgBoostBuilder class
			/** Builds svg documents using boost library.
			*	@ingroup SVG
			*/
			class SvgBoostBuilder : public SvgBuilder
			{
			public:

				/// Creates default boost builder.
				SvgBoostBuilder();

				/// Inherited from SvgBuilder.
				/** Builds new SvgGroup. Doesn't need parameters.
				* 
				*	@return Pointer to created SvgGroup object.
				*/
				virtual SvgGroup* ConstructGroup() const;

				/// Inherited from SvgBuilder.
				/** Builds new SvgPath from "d" attribute of the <path/> tag.
				*
				*	@param D_Attribute Value of "d" attribute of the <path/> tag. 
				*	@return Pointer to created SvgPath
				*/
				virtual SvgPath* ConstructPath(const std::string& D_Attribute);

				/// Inherited from SvgBuilder.
				/** Builds new SvgPathItem from an element of "d" attribute of the <path/> tag
				*
				*	@param TextItem element of "d" attribute of the <path/> tag.
				*	@return Pointer to created SvgPathItem
				*/
				virtual SvgPathItem* ConstructPathItem(const std::string& TextItem) /*const*/;

				/// Inherited from SvgBuilder.
				/** Adds style properties, described in TextStyle parameter to object.
				*	Doesn't modify any described properties.
				*
				*	@param TextStyle Style properties in CSS format.
				*	@param object Object, that needs for style overriding.
				*/
				virtual void OverrideStyle(const std::string& TextStyle, SvgObject* object); /*const*/

			private:

				/// Parses string coordinate to double value and adds it to specified vector.
				/**	@param Coord String coordinate.
				*	@param Vector Pointer to vector.
				*/
				void CummulatePoints(std::string& Coord, SvgObject*, void * Vector);

				/// Process complex string method.
				/** Finds in the input string elements on a given pattern and gives results to handler.
				*
				*	@param ComplexString Input string, that contains some simple elements.
				*	@param Pattern Regex pattern, that will be used to search items in the input string.
				*	@param Handler Method of this class, that will process result of searching
				*	@param Object Object, that will be applied results of parsing a complex string.
				*/
				void ProcessComplexString(const std::string& ComplexString, const std::string& Pattern, void (SvgBoostBuilder::*pHandler)(std::string&, SvgObject*, void*) /*Handler*/, SvgObject* Object, void * misc = 0) ;

				/// Trim string method.
				/** Removes elements from the begin and the end of the string.
				*	@param str Input string.
				*	@param chr Elements, that will be removed.
				*/
				void TrimString(std::string& str, char chr = ' ') ;

				///// Check command method.
				///** Checks type of SvgPathItem from it's svg string.
				//*	The the first character of the input string must be in set {C, M, Z, L, Q}.
				//*
				//*	@param CommandChar Character of command
				//*	@return Instance of SvgCommand type, that conforms input PathItem
				//*/
				//SvgCommand CheckCommand(char CommandChar) const;

				/// Get coordinates method.
				/** Gets coordinates from input string.
				*	@param InputString String with coordinates in svg format.
				*	@param coords Output collection of coordinates.
				*/
				void GetItemCoords(const std::string& InputString, std::vector<SvgPoint>& coords);

				/// Get point method
				/** Creates an instanse of SvgPoint from input string
				*
				*	@param PointString Input string with X and Y coordinates
				*	@return Instance of SvgPoint that conform to input string
				*/
				//SvgPoint GetPoint(const std::string& PointString);

				/// Add path item.
				/** Builds path item from string and adds it to path.
				*	Handler for ProcessComplexString() method.
				*
				*	@param itemString Path item in svg format.
				*	@param path Path.
				*/
				void AddPathItem(std::string& itemString, SvgObject* path, void * misc = 0);

				/// Modify style method.
				/** Adds style property to object from CSS string.
				*	Object must be SvgStylizable.
				*	Handler for ProcessComplexString() method.
				*
				*	@param styleString CSS string of style property
				*	@param obj Object
				*/
				void ModifyStyle(std::string& styleString, SvgObject* obj, void * misc = 0);

				/// Process color method
				/** Convert input string with color to an instarne of Color type
				*	Input string must be if "rgb(r,g,b)" or "#RRGGBB" format
				*
				*	@param colorString Input string with color
				*	@return Instance of Color type, that conform to input string
				*/
				Color ProcessColor( std::string& colorString);

				/// Converts string to deximal value
				/** If it's impossible to convert input string, method throws SvgException.
				*
				*	@param str Input string
				*	@returns deximal value, that conform to input string
				*/
				double StrToDec(const std::string& str);

				SvgErrorHandler * m_err_handler;						///< Handler of errors
				std::hash_map<char, SvgCommand> m_svgCommands;	///< Collection of supported SVG commands
			};

			// Typedef for handler of ProcessComplexString() method's results
			typedef void (SvgBoostBuilder::*pHandler)(std::string&, SvgObject*, void*);
		}
	}
}

#endif
