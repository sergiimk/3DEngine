/*========================================================
* SvgPath.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGPATH_H_
#define _SVGPATH_H_

#include "SvgObject.h"
#include "SvgPathItem.h"
#include "SvgStylizable.h"
#include <vector>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgVisitor;

			
			/// SvgPath class.
			/** Svg path. Consists of some items such as cubic bezier, line, etc. 
			*	@ingroup SVG */
			class SvgPath : public SvgObject, public SvgStylizable
			{
			public:
				virtual ~SvgPath();

				/// Add item method.
				/** Adds item to the path
				*
				*   @param item Pointer to item that will be added to path. Must be not 0 
				*/
				void AddItem(SvgPathItem* item);

				/// Inherited from SvgObject.
				/** Returns pointer to parent object in the svg hierarchy.
				*	If path doesn't have parent, returns 0;
				*/
				virtual SvgObject* Parent() const;

				/// Inherited from SvgObject.		 
				/** Attaches object to hierarchy by seting it's parent.
				*
				*	@param parent Parent object
				*/
				void SetParent(SvgObject* parent);

				/// Items method.
				/**	Returns a collection of items of the path
				*/
				const std::vector<SvgPathItem*>& Items() const;
				
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
				std::vector<SvgPathItem*> m_items;
				SvgObject* m_parent;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	// _SVGPATH_H_
