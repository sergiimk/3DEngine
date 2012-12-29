%{
	#include "materialdescparser.cpp.h"

	void mat_yyerror(char*);
	
	void mat_reset_lexer() 
	{ 
		YY_FLUSH_BUFFER; 
		// Flex bug workaround
		yy_delete_buffer( yy_current_buffer );
		yy_init = 1;
	}
%}

%option noyywrap
%option always-interactive
%option prefix="mat_yy"

string			\".*\"
ws				[ \t\n]
digit			[0-9a-fA-F]
exponent		[eE][+-]?{digit}+
int				"0x"{digit}+
index			[0-9]+
float			-?{digit}+("."{digit}+)?{exponent}?
param_feature	("mat"|"vec"|"tex"|"flt"|"clr")[A-Za-z]+

%%

{ws}+			{ /* skip whitespaces */ }
{int}			{ return TK_INTEGER;}
{float}			{ return TK_FLOAT; }

"//".*			{  }
{string}		{ return TK_STRING; }

"material"		{ return TK_MATERIAL; }
"effect"		{ return TK_EFFECT; }
"float2"		{ return TK_FLOAT2; }
"float3"		{ return TK_FLOAT3; }
"float4"		{ return TK_FLOAT4; }

{param_feature}	{ return TK_PARAM; }

[\[\];=(){},]	{ return yytext[0];  }

.				{ mat_yyerror("unexpected symbol"); }

%%
