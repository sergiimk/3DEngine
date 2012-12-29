#ifndef _MESHPARSER_H__
#define _MESHPARSER_H__

#include <string>


namespace Engine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////

		/// Parsing callback of mesh definition files
		/** @ingroup Graphics */
		class IMeshParsingCallback
		{
		public:
			/// Called when parsing error occur
			virtual void OnError(const char* msg) = 0;

			/// Called when geometry file name found
			virtual void OnGeometryFile(const char* file) = 0;

			/// Called when material is defined for subset
			virtual void OnSubsetMaterial(int sid, const char* material) = 0;

			/// Called when parsing is finished
			virtual void OnFinished(int nsubsets) = 0;
		};

		//////////////////////////////////////////////////////////////////////////

		/// Wrapper for flex/bison parser for mesh description files
		/** @ingroup Graphics */
		class MeshParser
		{
		public:

			bool Parse(	const char *file, IMeshParsingCallback* calback );

		};

		//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace

#endif // _MESHPARSER_H__