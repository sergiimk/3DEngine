/*========================================================
* Engine_classid.h
* @author Sergey Mikhtonyuk
* @date 30 June 2009
=========================================================*/
#ifndef _ENGINE_CLASSID_H__
#define _ENGINE_CLASSID_H__

namespace Engine
{

	// {56e36340-fd95-4033-af09-c1ae7bef7136} 
	static const Core::SCOM::GUID CLSID_CFSFrameWrapper = 
	{ 0x56e36340, 0xfd95, 0x4033, { 0xaf, 0x09, 0xc1, 0xae, 0x7b, 0xef, 0x71, 0x36 } };

	// {575baae7-a419-49cb-9b05-eaf7338cfda3} 
	static const Core::SCOM::GUID CLSID_CCmpAppearance = 
	{ 0x575baae7, 0xa419, 0x49cb, { 0x9b, 0x05, 0xea, 0xf7, 0x33, 0x8c, 0xfd, 0xa3 } };

	// {93eb90be-000b-4723-a17c-800d42b76c97} 
	static const Core::SCOM::GUID CLSID_CCmpSpatialNode = 
	{ 0x93eb90be, 0x000b, 0x4723, { 0xa1, 0x7c, 0x80, 0x0d, 0x42, 0xb7, 0x6c, 0x97 } };

	// {d8027fc9-d412-4255-a193-059218389631} 
	static const Core::SCOM::GUID CLSID_CCmpPhysicalBody = 
	{ 0xd8027fc9, 0xd412, 0x4255, { 0xa1, 0x93, 0x05, 0x92, 0x18, 0x38, 0x96, 0x31 } };

} // namespace

#endif // _ENGINE_CLASSID_H__