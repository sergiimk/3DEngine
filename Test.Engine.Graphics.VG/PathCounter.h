///*========================================================
//* PathCounter.h.h
//* @author Roman Prikhodcheko
//* @date 22 May 2009
//=========================================================*/
//#ifndef _PATHCOUNTER_H_
//#define _PATHCOUNTER_H_
//
//#include "CommonTypes.h"
//
//#include "../Engine.UI.SVG/SvgVisitor.h"
//#include "../Engine.UI.SVG/SvgPathItem.h"
//#include "../Engine.UI.SVG/SvgPath.h"
//
//#include <vector>
//
//class SvgPath;
//
///// PathInfo class.
///** Contains count of path items and count of point collections in path.
//*/
//
///// PathCounter class.
///** Counts count of pathes in svg document
//*/
//class PathCounter : public Engine::UI::SVG::SvgVisitor
//{
//public:
//
//	/// Visit svg path
//	virtual bool Visit(Engine::UI::SVG::SvgPath* path);
//
//	/// Count of path commands in the specified file.
////	inline int CommandsCount() const;
//
//	/// Count of point collections in the specified file 
////	inline int PointsCount() const;
//
//	 std::vector<PathInfo>& Infos() ;
//	
//private:
//	std::vector<PathInfo> m_infos;
//};
//
// std::vector<PathInfo>& PathCounter::Infos() 
//{
//	return m_infos;
//}
//
//bool PathCounter::Visit(Engine::UI::SVG::SvgPath *path)
//{
//	PathInfo info;
//	const std::vector<Engine::UI::SVG::SvgPathItem*>& items = path->Items();
//	info.CmdCount = items.size();
//	
//	for (std::vector<Engine::UI::SVG::SvgPathItem*>::const_iterator it = path->Items().begin(); it != items.end(); it++)
//			info.PointsCount += (*it)->Coordinates().size();
//
//	m_infos.push_back(info);
//
//	return true;
//}
//
//#endif	// _PATHCOUNTER_H_
