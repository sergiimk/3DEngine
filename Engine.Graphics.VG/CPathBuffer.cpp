/*========================================================
* CPathBuffer.cpp
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#include "CPathBuffer.h"
#include "../Core.Math/VML.h"
#include <memory.h>

namespace VG
{
	//////////////////////////////////////////////////////////////////////////

	void CPathBuffer::setPoints(const VML::Vector2* points, size_t npoints)
	{
		FreePointsBuffer();
		mPoints = new VML::Vector2[npoints];
		mPointsNum = npoints;
		memcpy(mPoints, points, sizeof(VML::Vector2) * npoints);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPathBuffer::FreePointsBuffer()
	{
		if(mPoints)
			delete[] mPoints;

		mPoints = 0;
		mPointsNum = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CPathBuffer::setCommands(const VG::PathCommand *commands, size_t ncmds)
	{
		FreeCommandsBuffer();
		mCommands = new PathCommand[ncmds];
		mCmdsNum = ncmds;
		memcpy(mCommands, commands, sizeof(PathCommand) * ncmds);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPathBuffer::FreeCommandsBuffer()
	{
		if(mCommands)
			delete[] mCommands;

		mCommands = 0;
		mCmdsNum = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPathBuffer::IsValid() const
	{
		size_t np = 0;
		for(size_t i = 0; i != mCmdsNum; ++i)
			np += getPointCount(mCommands[i]);

		return np == mPointsNum;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace