#include "SvgBoostBuilder.h"
#include "SvgGroup.h"
#include "SvgPath.h"
#include "SvgPathItem.h"
#include "SvgStylizable.h"
#include "SvgException.h"
#include "SvgErrorHandler.h"
#include "SvgDefaultErrorHandler.h"

#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cctype>
#include <memory>
#include <sstream>
#include <cassert>
#include <functional>
#include <boost/regex.hpp>


namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgBoostBuilder::SvgBoostBuilder()
			:m_err_handler(new SvgDefaultErrorHandler())
			{
				// Initializing collection of supported SVG commands
				m_svgCommands['A'] = SVG_ARCH;
				m_svgCommands['C'] = SVG_CUBIC_BEZIER;
				m_svgCommands['L'] = SVG_LINE;
				m_svgCommands['M'] = SVG_MOVETO;
				m_svgCommands['Q'] = SVG_QUADRATIC_BEZIER;
				m_svgCommands['Z'] = SVG_CLOSE;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgGroup* SvgBoostBuilder::ConstructGroup() const
			{
				return new SvgGroup;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgPath* SvgBoostBuilder::ConstructPath(const std::string& TextPath) 
			{
				std::auto_ptr<SvgPath> path(new SvgPath);

				ProcessComplexString(TextPath, "[A-Z][^A-Z]*", &SvgBoostBuilder::AddPathItem, path.get());

				return path.release();
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgPathItem* SvgBoostBuilder::ConstructPathItem(const std::string& itemString)
			{
				SvgCommand				cmd = m_svgCommands[itemString[0]];
				
				if(!cmd)
					m_err_handler->BadPathItem(SvgException(strcat("Bad command character ", &itemString[0])));

				std::vector<SvgPoint>	coords;

				GetItemCoords(itemString, coords);

				SvgPathItem *			item = new SvgPathItem(cmd, coords);

				return item;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::ProcessComplexString(const std::string& commandLine, const std::string& pattern, pHandler handler, SvgObject* element, void * misc) 
			{
				boost::regex				searchPattern(pattern.c_str());
				boost::smatch				what;
				std::string::const_iterator start  = commandLine.begin(), end = commandLine.end();
				boost::match_flag_type		flags  = boost::match_default;

				while(boost::regex_search(start, end, what, searchPattern, flags))
				{
					std::string resString(what[0].first, what[0].second);

					(this->*handler)(resString, element, misc);

					start  = what[0].second;
					flags |= boost::match_prev_avail;
					flags |= boost::match_not_bob;
				}
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::TrimString(std::string& str, char chr) 
			{
				std::string::size_type pos1 = str.find_first_not_of(chr);
				std::string::size_type pos2 = str.find_last_not_of(chr);
				str = str.substr(
					pos1 == std::string::npos ? 0 : pos1,
					pos2 == std::string::npos ? str.length() - 1 : pos2 - pos1 + 1
					);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//SvgCommand SvgBoostBuilder::CheckCommand(char commandChar) const
			//{
			//	switch(Item[0])
			//	{
			//	case 'M':
			//		return SVG_MOVETO;
			//	case 'Q':
			//		return SVG_QUADRATIC_BEZIER;
			//	case 'C':
			//		return SVG_CUBIC_BEZIER;
			//	case 'Z':
			//		return SVG_CLOSE;
			//	case 'L':
			//		return SVG_LINE;
			//	case 'A':
			//		return SVG_ARCH;
			//	default:
			//		return SVG_UNKNOWN;
			//	}

			//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::GetItemCoords(const std::string& itemString, std::vector<SvgPoint>& points)
			{
				std::vector<double> coords;

				ProcessComplexString(itemString, "[^ ,A-Z]+", &SvgBoostBuilder::CummulatePoints, 0 , &coords);

				assert(coords.size() % 2 == 0);

				for (std::vector<double>::const_iterator it = coords.begin(); it != coords.end(); it++)
				{
					SvgPoint point;
					point.x = *it;
					point.y = *++it;

					points.push_back(point);
				}

			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::CummulatePoints(std::string& coord, SvgObject*, void * Vector)
			{
				std::stringstream ss(coord);
				double val = 0;
				ss >> val;

				if (ss.fail())
				{
					SvgException ex("Can't parse coordinates");
					m_err_handler->BadCoordinates(ex, coord);
				}

				reinterpret_cast<std::vector<double>*>(Vector)->push_back(val);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//SvgPoint SvgBoostBuilder::GetPoint(const std::string& pointString)
			//{
			//	double	x = 0,	y = 0;			
			//	std::stringstream sx(pointString);

			//	sx >> x;	sx >> y;

			//	if (sx.fail())
			//		throw SvgException("Couldn't parse coordinates");

			//	SvgPoint point;
			//	point.x = x;	point.y = y;

			//	return point;
			//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::OverrideStyle(const std::string& TextStyle, SvgObject* object) /*const*/
			{
				assert(object->HasStyle());
				try
				{
					ProcessComplexString(TextStyle, "[^;]+", &SvgBoostBuilder::ModifyStyle, object);
				}
				catch(SvgException ex)
				{
					m_err_handler->BadStyle(ex, TextStyle, object);
				}
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::AddPathItem(std::string& itemString, SvgObject* path, void *)
			{
				SvgPathItem* item = ConstructPathItem(itemString);
				((SvgPath*)path)->AddItem(item);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBoostBuilder::ModifyStyle(std::string& styleString, SvgObject* object, void * )
			{
				SvgStyle&		style	= dynamic_cast<SvgStylizable*>(object)->Style();
				std::string		name	= styleString.substr(0, styleString.find(':'));
				std::string		val		= styleString.substr(styleString.find(':') + 1, styleString.size() - 1);

				TrimString(name);
				TrimString(val);

				if (name == "fill")
				{

					if (val == "none")
					{
						style.SetFillStyle(FS_NONE);
					}
					else
					{
						style.SetFillStyle(FS_SOLID);
						style.SetFillColor(ProcessColor(val));
					}
				}
				else if (name == "stroke")
				{
					if (val == "none")
					{
						style.SetStrokeStyle(SS_NONE);
					}
					else
					{
						style.SetStrokeStyle(SS_LINE_SOLID);
						style.SetStrokeColor(ProcessColor(val));
					}
				}
				else if (name == "stroke-width")
				{
					style.SetStrokeWidth(StrToDec(val));
				}
				else if (name == "fill-opacity")
				{
					style.SetOpacity(StrToDec(val));
				}

			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Color SvgBoostBuilder::ProcessColor( std::string& colorString)
			{
				Color col;
				if (colorString[0] == '#')
				{
					TrimString(colorString, '#'); 
					register int i = 0;
					for (std::string::iterator it = colorString.begin(); it != colorString.end(); it++, i++)
					{
						if (!(i % 2))
						{
							colorString.insert(it, ' ');
							it++;
						}
					}

					std::stringstream ss(colorString);
					ss << std::hex;

					ss >> col.Red; ss >> col.Green; ss >> col.Blue;
				}
				else
				{
					std::replace_if(colorString.begin(), colorString.end(), std::not1(std::ptr_fun(static_cast<int (*)(int)>(std::isdigit))), ' ' );
					TrimString(colorString);
					std::stringstream ss(colorString);

					ss >> col.Red; ss >> col.Green; ss >> col.Blue;

					if (ss.fail())
						throw SvgException();
				}

				return col;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			double SvgBoostBuilder::StrToDec(const std::string& str)
			{
				std::stringstream	ss(str);
				double				d = 0;

				ss >> d;

				if (ss.fail())
					throw SvgException();

				return d;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}
