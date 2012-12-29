/*========================================================
* MeshParser.cpp
* @author Sergey Mikhtonyuk
* @date 05 September 2009
=========================================================*/
#include "MeshParser.h"
#include <stdio.h>
#include <string>

//////////////////////////////////////////////////////////////////////////

bool mesh_error_flag;

//////////////////////////////////////////////////////////////////////////

extern FILE*											mesh_yyin;
extern int												mesh_yydebug;
extern Engine::Graphics::IMeshParsingCallback*			mesh_callback;

int mesh_yyparse();
void mesh_reset_lexer();

void mesh_yyerror(char *s)
{
	mesh_error_flag = true;
	mesh_callback->OnError(s);
}

//////////////////////////////////////////////////////////////////////////

namespace Engine
{
	namespace Graphics
	{

		bool MeshParser::Parse(	const char *file, IMeshParsingCallback* calback )
		{
			mesh_error_flag = false;
			mesh_callback = calback;

			if(!calback) return false;

			//mesh_yydebug = 1;
			fopen_s(&mesh_yyin, file, "rt");

			if(!mesh_yyin)
			{
				mesh_yyerror("file not found");
				return false;
			}

			mesh_yyparse();

			mesh_reset_lexer();
			fclose(mesh_yyin);

			return !mesh_error_flag;
		}

//////////////////////////////////////////////////////////////////////////

	} // namespace
} // namespace
