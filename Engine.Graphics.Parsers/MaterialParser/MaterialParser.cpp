#include "MaterialParser.h"
#include <stdio.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

std::string* mat_error_buffer;
bool mat_error_flag;

//////////////////////////////////////////////////////////////////////////

extern FILE*			mat_yyin;
extern int				mat_yydebug;
extern Engine::Graphics::IMaterialParsingCallback*	mat_callback;

int mat_yyparse();
void mat_reset_lexer();

void mat_yyerror(char *s)
{
	mat_error_flag = true;
	mat_callback->OnError(s);
}

//////////////////////////////////////////////////////////////////////////

namespace Engine
{
	namespace Graphics
	{
	
		bool MaterialParser::Parse(const char *file, IMaterialParsingCallback *callback)
		{
			mat_callback = callback;
			mat_error_flag = false;
			//mat_yydebug = 1;

			if(!callback) 
				return false;

			fopen_s(&mat_yyin, file, "rt");

			if(!mat_yyin)
			{
				callback->OnError("file not found");
				return false;
			}

			mat_yyparse();
			mat_reset_lexer();
			fclose(mat_yyin);

			return !mat_error_flag;
		}

	} // namespace
} // namespace
