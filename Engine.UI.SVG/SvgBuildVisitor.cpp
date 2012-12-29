#include "SvgBuildVisitor.h"
#include "SvgGroup.h"
#include "SvgPath.h"
#include "SvgDocument.h"
#include "SvgBuilder.h"
#include "SvgBoostBuilder.h"

#include <algorithm>
#include <cctype>
#include <cassert>
#include <memory>
#include <functional>
#include <boost/regex.hpp>


namespace Engine
{
	namespace UI
	{
		namespace SVG
		{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgBuildVisitor::~SvgBuildVisitor()
			{
				delete m_builder;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgBuildVisitor::SvgBuildVisitor(SvgDocument* doc)
				:m_parent(doc), m_builder(new SvgBoostBuilder())
			{
				assert(doc);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgBuildVisitor::SvgBuildVisitor(SvgDocument* doc, SvgBuilder* builder)
				:m_parent(doc), m_builder(builder)
			{
				assert(doc);
				assert(m_builder);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			bool SvgBuildVisitor::VisitEnter( const TiXmlElement& element, const TiXmlAttribute* firstAttribute  )
			{
				std::string tagName(GetTagName(element));
                                ConvertString(tagName);

				bool		changeParrent = false;
				SvgObject*  child = 0;

				if (tagName == "G")
				{
					child = m_builder->ConstructGroup();
					SvgGroup* group = static_cast<SvgGroup*>(child);

					changeParrent = true;
				}
				else if (tagName == "PATH")
				{
					std::string path(element.Attribute("d"));

					ConvertString(path);
					//FloatString(path);

					child = m_builder->ConstructPath(path);
				}
				else
				{
					return true;
				}


				if (child->HasStyle())
				{
					SvgStylizable* stylizable = dynamic_cast<SvgStylizable*>(child);

					if (m_parent->HasStyle())
						stylizable->SetStyle(dynamic_cast<SvgStylizable*>(m_parent)->Style());


					if( element.Attribute("style"))
					{
						std::string textStyle = element.Attribute("style") == 0 ? "" : element.Attribute("style");

						std::auto_ptr<SvgObject> ptr(child);
						m_builder->OverrideStyle(textStyle, ptr.get());
						ptr.release();
					}
				}

				m_parent->AddChild(child);

				if (changeParrent)
					m_parent = static_cast<SvgComplexObject*>(child);

				return true;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			bool SvgBuildVisitor::VisitExit( const TiXmlElement& element)
			{
				std::string tagName(GetTagName(element));
                                ConvertString(tagName);
                                
				if (tagName == "G")
				{
					m_parent = static_cast<SvgComplexObject*>(m_parent->Parent());
				}

				return true;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			std::string SvgBuildVisitor::GetTagName(const TiXmlElement& element/*, std::string& tagName*/)
			{
				return  element.Value();
				//std::transform(tagName.begin(), tagName.end(), tagName.begin(), std::toupper);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBuildVisitor::ConvertString(std::string & str)
			{
				std::transform(str.begin(), str.end(), str.begin(), /*std::ptr_fun(toupp)*/static_cast<int (*)(int)>(std::toupper));
				TrimString(str);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBuildVisitor::TrimString(std::string& str, char chr) 
			{
				std::string::size_type pos1 = str.find_first_not_of(chr);
				std::string::size_type pos2 = str.find_last_not_of(chr);
				str = str.substr(
					pos1 == std::string::npos ? 0 : pos1,
					pos2 == std::string::npos ? str.length() - 1 : pos2 - pos1 + 1
					);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgBuildVisitor::FloatString(std::string &str)
			{
				std::string	temp(str);

				boost::regex				searchPattern("[ A-Z]\\d+[ A-Z]");
				std::string				floatPoint(".0");
				boost::smatch				what;
				std::string::const_iterator start  = temp.begin(), end = temp.end();
				boost::match_flag_type		flags  = boost::match_default;

				while(boost::regex_search(start, end, what, searchPattern, flags))
				{
					std::string res(what[0].first, what[0].second);

					int first = str.find(res);

					str = str.insert(first + res.size() - 1, ".0");

					start  = what[0].second;
					flags |= boost::match_prev_avail;
					flags |= boost::match_not_bob;
				}


				return;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}
