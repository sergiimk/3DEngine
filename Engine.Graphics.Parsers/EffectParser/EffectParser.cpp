/*========================================================
* EffectParser.cpp
* @author Sergey Mikhtonyuk
* @date 06 August 2009
=========================================================*/
#include "EffectParser.h"
#include <stdio.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

std::string* fx_error_buffer;
bool fx_error_flag;

//////////////////////////////////////////////////////////////////////////

extern FILE*							fx_yyin;
extern int								fx_yydebug;
extern std::string*						effect_source;
extern Engine::Graphics::SEffectDesc*	cur_effect;

int fx_yyparse();
void fx_reset_lexer();

void fx_yyerror(char *s)
{
	fx_error_flag = true;

	if(fx_error_buffer)
		*fx_error_buffer = s;
}

//////////////////////////////////////////////////////////////////////////

namespace Engine
{
	namespace Graphics
	{

		bool EffectParser::Parse(	const char *file,
									SEffectDesc *dest,
									std::string *fxsource,
									std::string *error_buffer_)
		{
			fx_error_buffer = error_buffer_;
			fx_error_flag = false;
			effect_source = fxsource;

			if(!dest) 
				return false;

			cur_effect = dest;

			//fx_yydebug = 1;
			fopen_s(&fx_yyin, file, "rt");

			if(!fx_yyin)
			{
				if(fx_error_buffer) *fx_error_buffer = "file not found";
				return false;
			}

			fx_yyparse();

			fx_reset_lexer();

			fclose(fx_yyin);

			return !fx_error_flag;
		}

//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace
