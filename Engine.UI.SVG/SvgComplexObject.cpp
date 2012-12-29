/*========================================================
* SvgComplexObject.cpp
* @author Roman Prikhodcheko
* @date 19 March 2009
=========================================================*/
/** @defgroup UI Svg */

#include "SvgComplexObject.h"
#include <cassert>

namespace Engine
{
	namespace UI
	{
		namespace SVG
		{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			void SvgComplexObject::AddChild(SvgObject* child)
			{
				assert(child != 0);
				m_children.push_back(child);
				child->SetParent(this);
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			const std::vector<SvgObject*>& SvgComplexObject::Children() const
			{
				return m_children;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SvgComplexObject::~SvgComplexObject()
			{
				
				for (unsigned int i = 0; i < m_children.size(); i++)
					delete m_children[i];

			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} //SVG
	} //UI
} //Engine
