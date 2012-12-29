#include "../Engine.Graphics.Parsers/EffectParser/EffectParser.h"
#include "../Engine.Graphics.Parsers/Common/TypeParsing.h"
#include "../Engine.Graphics.Parsers/MaterialParser/MaterialParser.h"
#include "../Engine.Graphics.Parsers/MeshParser/MeshParser.h"
#include <stdio.h>

#define BOOST_TEST_MODULE GE_Parsers_test
#include <boost/test/unit_test.hpp>

using namespace Engine::Graphics;

BOOST_AUTO_TEST_SUITE( ParsersTest );

BOOST_AUTO_TEST_CASE( TestEffectParser )
{
	EffectParser p;
	SEffectDesc cur_effect;
	std::string fxfile;
	BOOST_CHECK(p.Parse("../Resources/Test/ResourceDefs/EffectTest.fxd", &cur_effect, &fxfile));

	/*printf("%s\n", fxfile.c_str());

	printf("Global\n");
	for(int j = 0; j != FXP_NUM_PARAMS; ++j)
	{
		if(cur_effect.getGlobalParameters()->getUsageState((EEffectParam)j))
			printf("\t%s\n", EEffectParam_ToString((EEffectParam)j));
	}

	for(SEffectDesc::iterator dit = cur_effect.begin(); dit != cur_effect.end(); ++dit)
	{
		if(dit->params) printf("%s\n", EEffectCap_ToString(dit->cap));
		else continue;

		for(SEffectParams::iterator it = dit->params->begin(); it != dit->params->end(); ++it)
		{
			if((*it).state)
				printf("\t%s\n", EEffectParam_ToString((*it).param));

		}
	}*/
}

BOOST_AUTO_TEST_CASE( TestMaterialParser )
{
	MaterialParser p;
	SMaterialBindings mat;
	std::string effect, name;

	/*class CTestCallback : public IMaterialParsingCallback
	{
	public:
		void OnError(const char* msg) { }
		void OnMaterialName(const char* name) { printf("material = %s\n", name); }
		void OnEffectDefinition(size_t stage, const char* effect) { printf("effect[%d] = %s\n", stage, effect); }
		void OnFloatBinding(EEffectParam param, float val) { printf("%s = %f\n", EEffectParam_ToString(param), val); }
		void OnTextureBinding(EEffectParam param, const char* path) { printf("%s = %s\n", EEffectParam_ToString(param), path); }
		void OnColorBinding(EEffectParam param, const VML::Vector4& val)
		{ printf("%s = %f, %f, %f, %f\n", EEffectParam_ToString(param), val.getXf(), val.getYf(), val.getZf(), val.getWf()); }
	} clb;*/

	class CTestCallback : public IMaterialParsingCallback
	{
	public:
		void OnError(const char* msg) { }
		void OnMaterialName(const char* name) { }
		void OnEffectDefinition(size_t stage, const char* effect) { }
		void OnFloatBinding(EEffectParam param, float val) { }
		void OnTextureBinding(EEffectParam param, const char* path) { }
		void OnColorBinding(EEffectParam param, const VML::Vector4& val) { }
	} clb;

	BOOST_CHECK(p.Parse("../Resources/Test/ResourceDefs/MaterialTest.mt", &clb));
}


BOOST_AUTO_TEST_CASE( TestMeshParser )
{
	MeshParser p;
	
	/*class CTestCallback : public IMeshParsingCallback
	{
		void OnError(const char* msg) { }
		void OnGeometryFile(const char* file)
		{ printf("%s\n", file); }
		void OnSubsetMaterial(int sid, const char* material)
		{ printf("subset %d material = %s\n", sid, material); }
		void OnFinished(int nsubsets) { }
	} clb;*/

	class CTestCallback : public IMeshParsingCallback
	{
		void OnError(const char* msg) { }
		void OnGeometryFile(const char* file) { }
		void OnSubsetMaterial(int sid, const char* material) { }
		void OnFinished(int nsubsets) { }
	} clb;

	BOOST_CHECK(p.Parse("../Resources/Test/ResourceDefs/MeshTest.md", &clb ));

}

BOOST_AUTO_TEST_SUITE_END();