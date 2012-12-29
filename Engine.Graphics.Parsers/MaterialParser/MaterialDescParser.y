%{

// Bison specification author: Roman Hwang
// File: materialdescparser.cpp
// Description: Implementation of material parsing for Sekai Engine (c)

#include <sstream>
#include <iomanip>
#include <cassert>
#include "materialdescparser.cpp.h"
#include "MaterialParser.h"
#include "../Common/TypeParsing.h"

using namespace std;
using namespace Engine::Graphics;

extern char* mat_yytext;
extern FILE* mat_yyin;
extern int mat_yylex();
int hexToInt( const char* _hex );
void intToFloat4(int val);
//#define YYDEBUG 1


IMaterialParsingCallback*	mat_callback;
SMaterialBindings*			mat_bindings;

static float s_color[4];
static char s_str[256];
static int s_index;

%}

%token TK_MATERIAL
%token TK_EFFECT
%token TK_INDEX
%token TK_FLOAT2
%token TK_FLOAT3
%token TK_FLOAT4
%token TK_PARAM
%token TK_STRING
%token TK_INTEGER
%token TK_FLOAT

%%

material:			TK_MATERIAL TK_STRING										{
																					strncpy_s(s_str, 256, &mat_yytext[1], strlen(&mat_yytext[1]) - 1);
																					mat_callback->OnMaterialName(s_str);
																				}
																				
					'{' declaration_list '}'									{ }
		
		
declaration_list:	declaration													{ }
					
					| declaration_list declaration								{ }
					
		 		
declaration:		parameter '=' value	';'										{
																					// Append value
																					switch($3)
																					{
																						case TK_FLOAT: s_color[1] = 0.0f; /*fallthrough*/
																						case TK_FLOAT2: s_color[2] = 0.0f; /*fallthrough*/
																						case TK_FLOAT3: s_color[3] = 1.0f;
																					}
																					
																					// Set value
																					if($1 > FXP_START_FLOAT_TYPES && $1 < FXP_END_FLOAT_TYPES)
																					{
																						if($3 != TK_FLOAT)
																							mat_yyerror("bad value type");
																						mat_callback->OnFloatBinding((EEffectParam)$1, s_color[0]);
																					}
																					
																					if($1 > FXP_START_TEXTURE_TYPES && $1 < FXP_END_TEXTURE_TYPES)
																					{
																						if($3 != TK_STRING)
																							mat_yyerror("bad value type");
																						mat_callback->OnTextureBinding((EEffectParam)$1, s_str);
																					}
																					
																					if($1 > FXP_START_COLOR_TYPES && $1 < FXP_END_COLOR_TYPES)
																					{
																						if($3 != TK_FLOAT3 && $3 != TK_FLOAT4)
																							mat_yyerror("bad value type");
																						VML::Vector4 v(s_color[0], s_color[1], s_color[2], s_color[3]);
																						mat_callback->OnColorBinding((EEffectParam)$1, v);
																					}
																				}
																				
																				
					| TK_EFFECT '[' TK_FLOAT									{
																					s_index = atoi(mat_yytext);
																					if(errno) mat_yyerror("bad stage value");
																				}
																				
					']' '=' value ';'											{
																					if($7 != TK_STRING)
																							mat_yyerror("bad value type");
																							
																					mat_callback->OnEffectDefinition(s_index, s_str);
																				}
																				


parameter:			TK_PARAM													{
																					$$ = EEffectParam_FromString(mat_yytext);
																					if($$ == (EEffectParam)-1)
																						mat_yyerror("bad parameter name");
																				}
																					


value:				TK_INTEGER													{
																					int val = hexToInt(&mat_yytext[2]);
																					intToFloat4(val);
																					$$ = TK_FLOAT4 /* converted */;
																				}
																				
					|	TK_STRING												{
																					strncpy_s(s_str, 256, &mat_yytext[1], strlen(&mat_yytext[1]) - 1);
																					$$ = TK_STRING;
																				}
																				
					|	TK_FLOAT4 '('											
						TK_FLOAT												{ s_color[0] = (float)atof(mat_yytext); } 
						',' TK_FLOAT											{ s_color[1] = (float)atof(mat_yytext); } 
						',' TK_FLOAT											{ s_color[2] = (float)atof(mat_yytext); } 
						',' TK_FLOAT											{ s_color[3] = (float)atof(mat_yytext); }  
						')'														{ $$ = TK_FLOAT4; }
						
					|	TK_FLOAT3 '('											
						TK_FLOAT												{ s_color[0] = (float)atof(mat_yytext); } 
						',' TK_FLOAT											{ s_color[1] = (float)atof(mat_yytext); } 
						',' TK_FLOAT											{ s_color[2] = (float)atof(mat_yytext); }  
						')'														{ $$ = TK_FLOAT3; }
						
					|	TK_FLOAT2 '('											
						TK_FLOAT												{ s_color[0] = (float)atof(mat_yytext); } 
						',' TK_FLOAT											{ s_color[1] = (float)atof(mat_yytext); }  
						')'														{ $$ = TK_FLOAT2; }
						
					|	TK_FLOAT												{ s_color[0] = (float)atof(mat_yytext); $$ = TK_FLOAT; } 
		
%%

int hexToInt( const char* _hex )
{
	// \todo optimize
	unsigned int result;
	std::istringstream str_stream(_hex);

	str_stream >> std::setbase(16) >> result;
	return result;
}

void intToFloat4(int val)
{
	static const float c = 1.0f / 255.0f;
	s_color[3] = c * (0x000000ff & (val >> 24));	//A
	s_color[0] = c * (0x000000ff & (val >> 16));	//R
	s_color[1] = c * (0x000000ff & (val >> 8));		//G
	s_color[2] = c * (0x000000ff & (val));			//B
}