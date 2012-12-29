/*========================================================
* SvgPathItem.h
* @author Roman Prikhodcheko
* @date 21 May 2009
=========================================================*/

#ifndef _SVGPATHITEM_H_
#define _SVGPATHITEM_H_

#include "SvgObject.h"
#include <vector>
#include <hash_map>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
			/// SvgPoint structure.
			/** Point, that may have double coordinates 
			*	@ingroup SVG */
			struct SvgPoint
			{
				/// X-coordinate
				double x;

				/// Y-coordinate
				double y;
			};

			/// Enum of possible commands for path items
			/** @ingroup SVG */
			enum SvgCommand
			{
				SVG_UNKNOWN = 0,		///< Unknown item
				SVG_ARCH,				///< Arch
				SVG_CLOSE,				///< Close path with line
				SVG_CUBIC_BEZIER,		///< Cubic Bezier curve
				SVG_LINE,				///< Line
				SVG_MOVETO,				///< Moving to point
				SVG_QUADRATIC_BEZIER	///< Quadratic Bezier curve
			};


			/// SvgPathItem class.
			/** Item of svg path. 
			*	@ingroup SVG */
			class SvgPathItem
			{
			public:
				/// Creates new SvgPathItem with requested type and points
				/**	@param cmd Command type
				*	@param points Collection of points
				*/
				SvgPathItem(SvgCommand cmd, std::vector<SvgPoint>& points);

				/// Returns type of the path item.
				SvgCommand Type() const;

				/// Returns coordinates of the path item.
				const std::vector<SvgPoint>& Coordinates() const;
			private:
				std::vector<SvgPoint> m_points;
				SvgCommand m_type;

				//static std::hash_map<SvgCommand, int> m_ptsCntChk;
				//static bool m_mapsInitialized;
			};

		}	// SVG
	}	// UI
}	// Engine

#endif	// _SVGPATHITEM_H_
