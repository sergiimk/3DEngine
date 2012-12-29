/*========================================================
* Misc.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
=========================================================*/
#ifndef _MISC_H__
#define _MISC_H__

#include "../Core.FileSystem/IXMLFileAdapter.h"


class CTestVisitor : public TiXmlVisitor
{
public:
	virtual bool VisitEnter( const TiXmlDocument& doc)			{ return true; }
	virtual bool VisitExit( const TiXmlDocument& doc )			{ return true; }
	virtual bool VisitEnter( const TiXmlElement& element, 
		const TiXmlAttribute* firstAttribute )					{ return true; }
	virtual bool VisitExit( const TiXmlElement& element )		{ return true; }
	virtual bool Visit( const TiXmlDeclaration& declaration )	{ return true; }
	virtual bool Visit( const TiXmlText& text )					{ return true; }
	virtual bool Visit( const TiXmlComment& comment )			{ return true; }
	virtual bool Visit( const TiXmlUnknown& unknown )			{ return true; }
};


#endif // _MISC_H__