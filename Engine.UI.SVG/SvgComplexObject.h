/*========================================================
* SvgComplexObject.h
* @author Roman Prikhodcheko
* @date 19 March 2009
=========================================================*/
#ifndef _SVGCOMPLEXOBJECT_H_
#define _SVGCOMPLEXOBJECT_H_

#include "SvgObject.h"
#include <vector>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{


			/// SvgObject class
			/** Base class for all composite svg elements.
			*	Contains collection of children. 
			*	@ingroup SVG  */
			class SvgComplexObject : public SvgObject
			{
			public:
				virtual ~SvgComplexObject();

				/// Add child method
				/** Adds child to child collection
				*
				*   @param child Pointer to child that will be added. Must be not 0 
				*/
				virtual void AddChild(SvgObject* child);

				/// Children method
				/** Returns a colleclion of children
				*/
				const std::vector<SvgObject*>& Children() const;
			private:
				std::vector<SvgObject*> m_children;
			};
		} //SVG
	} //UI
} //Engine

#endif //_SVGCOMPLEXOBJECT_H_
