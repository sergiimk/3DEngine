/*========================================================
* SvgBuildVisitor.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGBUILDVISITOR_H_
#define _SVGBUILDVISITOR_H_

#include "../Core.FileSystem.TinyXML/tinyxml.h"
#include <string>


namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgDocument;
			class SvgComplexObject;
			class SvgBuilder;
			class string;

			/// SvgBuildVisitor class
			/** Visitor, that walks through the XML document and builds SVG object model
			*	@ingroup SVG */
			class SvgBuildVisitor : public TiXmlVisitor
			{
			public:
				~SvgBuildVisitor();

				/// Default constructor
				/**	Creates new instance of SvgBuildVisitor class and builds an svg document
				*	@param doc An instance of empty svg document, that need for build.
				*/
				SvgBuildVisitor(SvgDocument* doc);

				/// Constructor with builder specified
				/**	Creates new instance of SvgBuildVisitor class and builds an svg document
				*	@param doc An instance of empty svg document, that need for build.
				*/
				SvgBuildVisitor(SvgDocument* doc, SvgBuilder* builder);

				/// Enter an xml element. If returns true, visitor will visit child elements
				virtual bool VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute );

				/// Exit an xml element.
				virtual bool VisitExit( const TiXmlElement& element);
			private:

				/// Get tag name method.
				/** Gets tag name from xml element.
				*	
				*	@param element XML element.
				*	@param tagName Output string for tag name.
				*/
				std::string GetTagName(const TiXmlElement& element/*, std::string& tagName*/);

				/// Convert string method.
				/** Converts all characters to upper case and trims spaces.
				*
				*	@param str Input string, that will be converted.
				*/
				void ConvertString(std::string& str);

				/// Trims specified characters
				void TrimString(std::string& str, char chr = ' ');

				/// Adds a float point to all non float numbers in string
				void FloatString(std::string& str);

				SvgComplexObject* m_parent;
				SvgBuilder* m_builder;
			};
		}	// SVG
	}	// UI
}	// Engne

#endif	// _SVGBUILDVISITOR_H_
