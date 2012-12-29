/*========================================================
* VGTypes.h
* @author Sergey Mikhtonyuk
* @date 24 January 2009
=========================================================*/
#ifndef _VGTYPES_H__
#define _VGTYPES_H__

/////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>
/////////////////////////////////
#include <vector>

namespace VG
{
	/// Threshold for float comparison
	extern const float FLOAT_CMP_EPSILON;

	/// Available path commands (in brackets - required point count for command)
	/** @ingroup VG */
	enum PathCommand
	{
		PC_MOVE,			///< First point / degenerated triangle connection [1]
		PC_LINE,			///< Line to command [1]
		PC_CLOSE,			///< Close path with a line [0]
		PC_BEZIER_2,		///< Quadratic bezier curve [2]
		PC_BEZIER_3,		///< Cubic bezier curve [3]
		PC_G1_BEZIER_2,		///< Smooth connection with quadratic bezier [1]
		PC_G1_BEZIER_3,		///< Smooth connection with cubic bezier [2]

		_PATH_COMMANDS_TOP = 1000,	///< Separates path commands from style commands

		// Style of line joint
		LJOINT_TOFIRST,		///< Calculates points for 1st line and lints 2nd to them
		LJOINT_SEPARATE,	///< No connection between lines [0]
		LJOINT_MITER,		///< Outer line edges will be extended until intersect [0]
		LJOINT_BEVEL,		///< Connected with triangle [0]
		LJOINT_ROUND,		///< Smooth line connection [0]

		_JOIT_STYLE_TOP = 2000, ///< Separates joint styles from ending styles

		// Styles of line end
		LEND_BUTT,			///< No ending [0]
		LEND_SQUARE,		///< Square with length of line's width [0]
		LEND_ROUND,			///< Smooth end [0]
	};

	//////////////////////////////////////////////////////////////////////////

	inline size_t getPointCount(PathCommand cmd)
	{
		switch(cmd)
		{
		case PC_MOVE:			return 1;
		case PC_LINE:			return 1;
		case PC_BEZIER_2:		return 2;
		case PC_BEZIER_3:		return 3;
		case PC_G1_BEZIER_2:	return 1;
		case PC_G1_BEZIER_3:	return 2;
		default:				return 0;
		}
	}


	//////////////////////////////////////////////////////////////////////////


	/// Style of stroke
	/** @ingroup VG */
	enum StrokeStyle
	{
		SS_NONE,			///< No stroke (can be used for filled polygons with no border)
		SS_LINE_SOLID,		///< Strokes path with a line with solid color
		SS_LINE_GRAD_LENGTH,///< Line with color interpolation along the path between start and end points
		SS_LINE_GRAD_WIDTH,	///< Line with color interpolation along the path by line's width
		SS_LINE_GRAD_X,		///< Line with color interpolation along X axis
		SS_LINE_GRAD_Y,		///< Line with color interpolation along Y axis
	};


	//////////////////////////////////////////////////////////////////////////


	/// Fill style of closed paths
	/** @ingroup VG */
	enum FillStyle
	{
		FS_NONE,			///< No fill
		FS_SOLID,			///< Solid-color fill
		FS_GRAD_X,			///< Gradient fill with color interpolation along X axis
		FS_GRAD_Y,			///< Gradient fill with color interpolation along Y axis
	};


	//////////////////////////////////////////////////////////////////////////


	/// Properties of the path
	/** @ingroup VG */
	enum PathProperty
	{
		PP_DEFAULT_JOINT,	///< Default joint style
		PP_DEFAULT_ENDING,	///< Default ending style
		PP_STROKE_STYLE,	///< Style of stroke
		PP_FILL_STYLE,		///< Fill style, valid only for closed paths

		PP_STROKE_COLOR1,	///< Color of the stroke path
		PP_STROKE_COLOR2,	///< Second stroke color, used in gradient

		PP_FILL_COLOR1,		///< Color of the fill path
		PP_FILL_COLOR2,		///< Second fill color, used in gradient

		_NUM_PATH_PROPERTIES,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Gathers all path properties
	/** @ingroup VG */
	struct PathProperties
	{
		float				strokeWidth;
		float				tolerance;
		unsigned long		properties[_NUM_PATH_PROPERTIES];
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace


#endif // _VGTYPES_H__