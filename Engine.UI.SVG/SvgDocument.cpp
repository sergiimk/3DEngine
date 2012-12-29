/*========================================================
* SvgDocument.cpp
* @author Roman Prikhodcheko
* @date 19 March 2009
=========================================================*/
/** @defgroup UI Svg */

#include "SvgDocument.h"
#include "SvgBuildVisitor.h"
#include "SvgVisitor.h"
#include "SvgException.h"
#include "../Core.FileSystem.TinyXML/tinyxml.h"

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgDocument::SvgDocument(std::string fileName)
				:m_fileName(fileName)
			{
				TiXmlDocument doc(fileName);
				doc.LoadFile(TIXML_DEFAULT_ENCODING);
				SvgBuildVisitor vis(this);
				doc.Accept(&vis);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgDocument::SvgDocument(std::string fileName, SvgBuilder* builder)
			{
				if (builder == 0)
					throw new SvgException("Using of uninitialized builder");

				TiXmlDocument doc(fileName);
				doc.LoadFile(TIXML_DEFAULT_ENCODING);
				SvgBuildVisitor vis(this, builder);
				doc.Accept(&vis);
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgObject* SvgDocument::Parent() const
			{
				throw SvgException("Root element can't have a parent");
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgDocument::SetParent(Engine::UI::SVG::SvgObject *parent)
			{
				throw SvgException("Root element can't have a parent");
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgDocument::Accept(SvgVisitor* visitor)
			{
				if(!visitor->Visit(this))
					return;

				for(std::vector<SvgObject*>::const_iterator i = Children().begin(); i != Children().end(); i++)
				{
					(*i)->Accept(visitor);
				}

			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} //SVG
	} //UI
} //Engine