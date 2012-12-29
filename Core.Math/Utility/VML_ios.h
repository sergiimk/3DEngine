/*========================================================
* VML_ios.h
* @author Sergey Mikhtonyuk
* @date 19 June 2009
=========================================================*/

#include "../VML.h"
#include <iosfwd>

//////////////////////////////////////////////////////////////////////////
inline std::ostream& operator<<(std::ostream& os, const VML::Vector3& val)
{
	os<<val.getX()<<' '<<val.getY()<<' '<<val.getZ();
	return os;
}

inline std::istream& operator>>(std::istream& os, VML::Vector3& val)
{
	return os;
}


/*std::ostream& operator<<(std::ostream& os, const VML::Vector4& val);
std::istream& operator>>(std::istream& os, VML::Vector4& val);

std::ostream& operator<<(std::ostream& os, const VML::Point2& val);
std::istream& operator>>(std::istream& os, VML::Point2& val);

std::ostream& operator<<(std::ostream& os, const VML::Point3& val);
std::istream& operator>>(std::istream& os, VML::Point3& val);

std::ostream& operator<<(std::ostream& os, const VML::Quat& val);
std::istream& operator>>(std::istream& os, VML::Quat& val);*/
//////////////////////////////////////////////////////////////////////////
