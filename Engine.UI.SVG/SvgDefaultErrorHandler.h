#ifndef _SVGDEFAULTERRORHANDLER_H_
#define _SVGDEFAULTERRORHANDLER_H_

#include "SvgErrorHandler.h"

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			///	SvgDefaultErrorHandler class
			/** Implements default logic of error processing
			*	@ingroup SVG
			*/
			class SvgDefaultErrorHandler : public SvgErrorHandler
			{
			public:
				/// Proceed bad coordinates. If returns true, parser continues working
				virtual void BadCoordinates(SvgException exception, const std::string& input);

				/// Proceed bad path. If returns true, parser continues working
				virtual bool BadPath(SvgException exception, SvgPath* path = 0);

				/// Proceed bad group. If returns true, parser continues working
				virtual bool BadGroup(SvgException exception, SvgGroup* group = 0);

				/// Proceed bad path item. If returns true, parser continues working
				virtual bool BadPathItem(SvgException exception, SvgPathItem* item = 0);
				
				/// Proceed bad style. If returns true, parser continues working
				virtual bool BadStyle(SvgException exception, const std::string& input, SvgObject* object = 0);
			};
		}	// SVG
	}	// UI
}	// Engine

#endif // _SVGDEFAULTERRORHANDLER_H_