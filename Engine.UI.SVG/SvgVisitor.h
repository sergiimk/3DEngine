/*========================================================
* SvgVisitor.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGVISITOR_N_
#define _SVGVISITOR_N_

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgDocument;
			class SvgGroup;
			class SvgPath;

			/// SvgVisitor interface
			/** Base interface for visitors for svg trees.
			*	@ingroup SVG SVG */
			class SvgVisitor
			{
			public:
				virtual ~SvgVisitor()							{					}

				/// Visit svg document
				virtual bool Visit(SvgDocument* doc)			{	return true;	}
				
				/// Enter svg group
				virtual bool VisitEnter(SvgGroup* group)		{	return true;	}
				
				/// Exit from svg group
				virtual void VisitExit(SvgGroup* group)			{	return;			}
				
				/// Visit svg path
				virtual bool Visit(SvgPath* path)				{	return true;	}
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	//_SVGVISITOR_N_
