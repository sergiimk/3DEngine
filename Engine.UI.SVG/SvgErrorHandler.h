/*========================================================
* SvgErrorHandler.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGERRORHANDLER_H_
#define _SVGERRORHANDLER_H_

#include "SvgException.h"
#include <string>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			class SvgObject;
			class SvgPath;
			class SvgGroup;
			class SvgPathItem;
			class SvgException;

			/// SvgErrorHandler interface
			/** Base interface for error handlers.
			*	@ingroup SVG
			*/
			class SvgErrorHandler
			{
			public:
				virtual ~SvgErrorHandler() {		}

				/// Proceed bad coordinades. If returns true, parser continues working
				virtual void BadCoordinates(SvgException exception, const std::string& input) = 0;

				/// Proceed bad path. If returns true, parser continues working
				virtual bool BadPath(SvgException exception, SvgPath* path = 0) = 0;

				/// Proceed bad group. If returns true, parser continues working
				virtual bool BadGroup(SvgException exception, SvgGroup* group = 0) = 0;

				/// Proceed bad path item. If returns true, parser continues working
				virtual bool BadPathItem(SvgException exception, SvgPathItem* item = 0) = 0;
				
				/// Proceed bad style. If returns true, parser continues working
				virtual bool BadStyle(SvgException exception, const std::string& input, SvgObject* object = 0) = 0;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif // _SVGERRORHANDLER_H_
