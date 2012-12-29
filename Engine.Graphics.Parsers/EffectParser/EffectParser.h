#ifndef _EFFECTPARSER_H__
#define _EFFECTPARSER_H__

#include "../../Engine.Graphics/Interfaces/EffectTypes.h"
#include <string>


namespace Engine
{
	namespace Graphics
	{
		/// Wrapper for flex/bison parser for effect description files
		/** @ingroup  */
		class EffectParser
		{
		public:

			bool Parse(	const char *file, 
						SEffectDesc *dest,
						std::string *fxsource,
						std::string *error_buffer_ = 0);

		};

	} // namespace
} // namespace

#endif // _EFFECTPARSER_H__