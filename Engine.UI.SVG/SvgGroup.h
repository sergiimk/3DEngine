/*========================================================
* SvgGroup.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGGROUP_H_
#define _SVGGROUP_H_

#include "SvgComplexObject.h"
#include "SvgStylizable.h"

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgVisitor;

			/// SvgGroup class.
			/** Group of svg elements that contain some common properties.
			*	@ingroup SVG */
			class SvgGroup : public SvgComplexObject, public SvgStylizable
			{
			public:
				/// Inherited from SvgObject.		 
				/** Attaches object to hierarchy by seting it's parent.
				*
				*	@param parent Parent object
				*/
				virtual void SetParent(SvgObject* parent);
				
				/// Inherited from SvgObject.
				/** Returns pointer to parent object in the svg hierarchy.
				*	If path doesn't have parent, returns 0;
				*/
				virtual SvgObject* Parent() const;

				/// Inherited from SvgObject.			 
				/** Visitor is used to iterate nodes of the 
				*	document and to perform some actions on them.
				*
				*	@param visitor Reference to visitor, that will perform actions
				*/
				virtual void Accept(SvgVisitor* visitor);

				/// Inherited from SvgObject. Returns true.
				virtual bool HasStyle() const {		return true;	}
			private:
				SvgObject* m_parent;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	// _SVGGROUP_H_
