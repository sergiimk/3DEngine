/*========================================================
* SvgStyle.h
* @author Roman Prikhodcheko
* @date 20 May 2009
=========================================================*/

#ifndef _SVGSTYLE_H_
#define _SVGSTYLE_H_

#include "SvgException.h"
#include <string>


namespace Engine
{
	namespace UI
	{
		namespace SVG
		{

			/// Color structure
			/** Structure, that implements type
			*	for three chanel color, used in svg documents
			*	@ingroup SVG
			*/
			struct Color
			{
				/// Red chanel
				unsigned short Red;

				/// Green chanel
				unsigned short Green;

				/// Blue chanel
				unsigned short Blue;
			};

			/// Fill styles
			/**
			*	@ingroup SVG
			*/
			enum SVG_FILL_STYLE
			{
				FS_NONE,			///< No fill
				FS_SOLID,			///< Solid-color fill
				FS_GRAD_X,			///< Gradient fill with color interpolation along X axis
				FS_GRAD_Y,			///< Gradient fill with color interpolation along Y axis
			};

			/// Stroke styles
			/**
			*	@ingroup SVG
			*/
			enum SVG_STROKE_STYLE
			{
				SS_NONE,			///< No stroke (can be used for filled polygons with no border)
				SS_LINE_SOLID,		///< Strokes path with a line with solid color
				SS_LINE_GRAD_LENGTH,///< Line with color interpolation along the path between start and end points
				SS_LINE_GRAD_WIDTH,	///< Line with color interpolation along the path by line's width
				SS_LINE_GRAD_X,		///< Line with color interpolation along X axis
				SS_LINE_GRAD_Y,		///< Line with color interpolation along Y axis
			};

			/// SvgStyle class
			/** Contains properties of style that can contain svg element 
			*	@ingroup SVG
			*/
			class SvgStyle
			{
			public:

				/// Constructor
				/**	Creates default style.
				*	Default settings:
				*	stroke color - black;
				*	stroke style - SS_LINE_SOLID;
				*	fill color - black;
				*	fill style - FS_SOLID
				*	opacity - 1;
				*/
				SvgStyle();

				/// Returns fill color
				const Color& FillColor() const;

				/// Returns border color
				const Color& StrokeColor() const;

				/// Returns width of the border
				double StrokeWidth() const;

				/// Returns opacity. May be between 0 and 1
				double Opacity() const;

				/// Returns style of filling
				SVG_FILL_STYLE FillStyle() const;

				/// Returns stroke style
				SVG_STROKE_STYLE StrokeStyle() const;

				/// Sets fill color
				/**
				*   @param color Reference to color
				*/
				void SetFillColor(const Color& color);

				/// Sets border color
				/**
				*   @param color Reference to color
				*/
				void SetStrokeColor(const Color& color);

				/// Sets border width
				/**
				*   @param Width New border width
				*/
				void SetStrokeWidth(double Width);

				/// Sets opacity
				/**
				*   @param Opacity New opacity
				*/
				void SetOpacity(double Opacity);

				/// Sets style of filling
				/**
				*	@param style Style of filling
				*/
				void SetFillStyle(SVG_FILL_STYLE style);

				/// Sets stroke style
				/**
				*	@param style Stroke style
				*/
				void SetStrokeStyle(SVG_STROKE_STYLE style);


			private:
				Color m_fillColor;
				Color m_strokeColor;
				double m_strokeWidth;
				double m_opacity;
				SVG_FILL_STYLE m_fillStyle;
				SVG_STROKE_STYLE m_strokeStyle;
			};
		}	// SVG
	}	// UI
}	// Engine

#endif	//_SVGSTYLE_H_
