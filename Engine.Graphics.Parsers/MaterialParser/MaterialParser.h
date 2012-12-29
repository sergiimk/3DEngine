/*========================================================
* MaterialParser.h
* @author Roman Hwang
* @date 11 August 2009
=========================================================*/

#ifndef __MATERIALPARSER_H__
#define __MATERIALPARSER_H__

#include "../../Engine.Graphics/Interfaces/MaterialTypes.h"
#include <string>

namespace Engine
{
	namespace Graphics
	{

		//////////////////////////////////////////////////////////////////////////

		/// Parsing callback of material definition files
		/** @ingroup Graphics */
		class IMaterialParsingCallback
		{
		public:
			virtual void OnError(const char* msg) = 0;
			virtual void OnMaterialName(const char* name) = 0;
			virtual void OnEffectDefinition(size_t stage, const char* effect) = 0;
			virtual void OnFloatBinding(EEffectParam param, float val) = 0;
			virtual void OnTextureBinding(EEffectParam param, const char* path) = 0;
			virtual void OnColorBinding(EEffectParam param, const VML::Vector4& val) = 0;
		};

		//////////////////////////////////////////////////////////////////////////
	
		/// Wrapper for flex\bison parser for material description files
		/** @ingroup Graphics */
		class MaterialParser
		{
		public:

			bool Parse(const char *file, IMaterialParsingCallback *callback);
		};

	} // namespace
} // namespace

#endif