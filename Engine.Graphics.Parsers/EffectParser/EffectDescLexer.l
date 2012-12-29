%{
	#include "../Common/Token.h"
	#include "effectdescparser.cpp.h"
	#include "string.h"
	#include "../../Engine.Graphics/Interfaces/EffectTypes.h"
	#include "../Common/TypeParsing.h"

	using namespace Engine::Graphics;
	
	void fx_yyerror(char* s);
	
	void fx_reset_lexer() 
	{ 
		YY_FLUSH_BUFFER; 
		// Flex bug workaround
		yy_delete_buffer( yy_current_buffer );
		yy_init = 1;
	}
%}

%option noyywrap
%option always-interactive
%option prefix="fx_yy"


spec_symbol		[;=(){},]
string			\".*\"
comment			"//".*
param_feature	("mat"|"vec"|"tex"|"flt"|"clr")[A-Za-z]+

%%

[ \t\n]+					{ }
"effect"					{ return TK_EFFECT; }
{string}					{ fx_yylval.text = fx_yytext; return TK_STRING; }
{spec_symbol}				{ return fx_yytext[0];  }
{comment}					{ }




{param_feature}				{
								fx_yylval.intval = EEffectParam_FromString(fx_yytext);
								if(fx_yylval.intval == (EEffectParam)-1)
									fx_yyerror("bad parameter name");
									
								return TK_PARAM;
							}



"DIFFUSE_MAP"				{ fx_yylval.intval = FXC_DIFFUSE_MAP;			return TK_CAP; }
"NORMAL_MAP"				{ fx_yylval.intval = FXC_NORMAL_MAP;			return TK_CAP; }
"HEIGHT_MAP"				{ fx_yylval.intval = FXC_HEIGHT_MAP;			return TK_CAP; }
"SPECULAR_MAP"				{ fx_yylval.intval = FXC_SPECULAR_MAP;			return TK_CAP; }
"EMISSIVE_MAP"				{ fx_yylval.intval = FXC_EMISSIVE_MAP;			return TK_CAP; }
"SHININESS_MAP"				{ fx_yylval.intval = FXC_SHININESS_MAP;			return TK_CAP; }
"CUBE_MAP"					{ fx_yylval.intval = FXC_CUBE_MAP;				return TK_CAP; }
"SSAO_MAP"					{ fx_yylval.intval = FXC_SSAO_MAP;				return TK_CAP; }
"AMBIENT_LIGHT"				{ fx_yylval.intval = FXC_AMBIENT_LIGHT;			return TK_CAP; }
"DIRECTIONAL_LIGHT"			{ fx_yylval.intval = FXC_DIRECTIONAL_LIGHT;		return TK_CAP; }


.							{ fx_yyerror("unexpected symbol"); }


%%
