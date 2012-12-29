/*========================================================
* SvgDocument.h
* @author Roman Prikhodcheko
* @date 20 May 2009
=========================================================*/

#ifndef _SVGDOCUMENT_H_
#define _SVGDOCUMENT_H_

#include "SvgComplexObject.h"
#include <string>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{

			class SvgVisitor;
			class SvgBuilder;

			/// SvgDocument class
			/** Root element of any svg picture.
			* Containes svg elements, common styles, than defined in CSS stylesheet
			* and service information such as encoding etc.
			* @ingroup SVG */
			class SvgDocument : public SvgComplexObject
			{
			public:
				/// Creates new document and loads it from file
				/**
				*   @param FileName Full name of file, that will be loaded
				*/
				SvgDocument(std::string FileName);

				/// Creates new document and loads it from file
				/**
				*   @param FileName Full name of file, that will be loaded. Specified builder will be used for building of SVG components.
				*	@param Builder  Builder that will be used for building of SVG components.
				*/
				SvgDocument(std::string FileName, SvgBuilder* Builder);

				/// Parent method
				/** This method was inherited from SvgObject but SvgDocument can't
				*	have a parent, so calling of this method'll throw an exception
				*/
				virtual SvgObject* Parent() const;

				/// Acept method
				/** Inherited from SvgObject
				*	An easy way to walk through the svg tree and perform some actions
				*	on it's leaves.
				*
				*   @param visitor Referense to visitor, that will catch callbacks from svg elements in the tree
				*/
				virtual void Accept(SvgVisitor* visitor);

				/// Inherited from SvgObject. Returns false.
				virtual bool HasStyle() const {		return false;	}
			protected:

				/// SetParent method
				/** This method was inherited from SvgObject but SvgDocument can't
				*	have a parent, so calling of this method will throw an exception
				*
				*	@param parent Pointer to parent.
				*/
				virtual void SetParent(SvgObject* parent);
			private:
				std::string m_fileName;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	// _SVGDOCUMENT_H_
