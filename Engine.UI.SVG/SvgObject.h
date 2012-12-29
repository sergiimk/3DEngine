/*========================================================
* SvgObject.h
* @author Roman Prikhodcheko
* @date 19 March 2009
=========================================================*/
/** @defgroup UI Svg */

#ifndef _SVGOBJECT_H_
#define _SVGOBJECT_H_


namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgVisitor;

			/// SvgObject interface
			/** Base interface for all independent svg elements
			*	@ingroup SVG */
			class SvgObject
			{
			public:
				virtual ~SvgObject() {	}

				/// Parent method
				/** Returns pointer to parent object in the svg hierarchy.
				*	If object doesn't have parent, returns 0;
				*	If object can not have a parent, method throws
				*	an SvgException
				*/
				virtual SvgObject* Parent() const = 0;

				/// Accept visitor method.			 
				/** Visitor is used to iterate nodes of the 
				*	document and to perform some actions on them.
				*
				*	@param visitor Reference to visitor, that will perform actions
				*/
				virtual void Accept(SvgVisitor* visitor) = 0;

				/// Set parent method.			 
				/** Attaches object to hierarchy by seting it's parent.
				*	If it's impossible to set parent for object, method throws
				*	an SvgException
				*
				*	@param parent Parent object
				*/
				virtual void SetParent(SvgObject* parent) = 0;

				/// Has style method
				/** Returns true if object can have style.
				*	Else returns false
				*/
				virtual bool HasStyle() const = 0;
			};
		} //SVG
	} //UI
} //Engine

#endif //_SVGOBJECT_H_
