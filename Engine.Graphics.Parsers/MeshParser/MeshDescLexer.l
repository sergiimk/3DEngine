%{
	#include "meshdescparser.cpp.h"
	#include "string.h"

	//using namespace Engine::Graphics;
	
	void mesh_yyerror(char* s);
	
	void mesh_reset_lexer() 
	{ 
		YY_FLUSH_BUFFER; 
		// Flex bug workaround
		yy_delete_buffer( yy_current_buffer );
		yy_init = 1;
	}
%}

%option noyywrap
%option always-interactive
%option prefix="mesh_yy"


spec_symbol		[;=(){},]
string			\".*\"
comment			"//".*
int				[0-9]+

%%

[ \t\n]+					{ }
"mesh"						{ return TK_MESH; }
"subset"					{ return TK_SUBSET; }
"material"					{ return TK_MATERIAL; }
{string}					{ return TK_STRING; }
{spec_symbol}				{ return mesh_yytext[0]; }
{comment}					{ }
{int}						{ return TK_INT; }

.							{ mesh_yyerror("unexpected symbol"); }


%%
