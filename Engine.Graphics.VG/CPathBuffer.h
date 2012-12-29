/*========================================================
* CPathBuffer.h
* @author Sergey Mikhtonyuk
* @date 19 July 2009
=========================================================*/
#ifndef _CPATHBUFFER_H__
#define _CPATHBUFFER_H__

#include "IPathBuffer.h"

namespace VG
{

	/// Implementation of IPathBuffer interface
	/** @ingroup VG */
	class CPathBuffer : public IPathBuffer
	{
	public:
		/// Ctor for empty buffer
		CPathBuffer() : mPoints(0), mPointsNum(0), mCommands(0), mCmdsNum(0)
		{ }

		~CPathBuffer()
		{
			FreePointsBuffer();
			FreeCommandsBuffer();
		}

		VML::Vector2* getPoints() { return mPoints; }

		size_t getPointsNumber() const { return mPointsNum; }

		void setPoints(const VML::Vector2* points, size_t npoints);

		void FreePointsBuffer();


		PathCommand* getCommands() { return mCommands; }

		size_t getCommandsNumber() const { return mCmdsNum; }

		void setCommands(const PathCommand* commands, size_t ncmds);

		void FreeCommandsBuffer();


		bool IsValid() const;

	private:
		VML::Vector2 *mPoints;
		PathCommand *mCommands;
		size_t		mPointsNum;
		size_t		mCmdsNum;
	};

} // namespace

#endif // _CPATHBUFFER_H__