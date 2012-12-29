%{
	#include <string>
	#include "MeshParser.h"
	
	using namespace Engine::Graphics;
	
	extern char* mesh_yytext;
	extern FILE* mesh_yyin;
	extern int mesh_yylex();
	//#define YYDEBUG 1
	
	IMeshParsingCallback*	mesh_callback = 0;
	static int cur_subset = -1;
	static int subset_cnt;
%}

%token TK_MESH
%token TK_STRING
%token TK_INT
%token TK_SUBSET
%token TK_MATERIAL

%%

mesh_definition:		TK_MESH TK_STRING										{
																					subset_cnt = 0;
																					char buf[256];
																					strncpy_s(buf, 256, &mesh_yytext[1], strlen(&mesh_yytext[1]) - 1);
																					mesh_callback->OnGeometryFile(buf); 
																				}
																				
						'{' subset_list '}'										{ mesh_callback->OnFinished(subset_cnt); }
						
						;
						


subset_list:			subset													{ }
						
						| subset_list subset									{ }
						
						;
						


subset:					TK_SUBSET TK_INT										{
																					++subset_cnt;
																					cur_subset = atoi(mesh_yytext);
																					if(errno) mesh_yyerror("Bad subset index");
																				}

						'{' subset_property_list '}'							{ }

						;
						
				
						
subset_property_list:	subset_property	';'										{ }
						
						| subset_property_list subset_property					{ }
						
						;
						
						
						
subset_property:		material												{ }
						
						;
						
						
						
material:				TK_MATERIAL '=' TK_STRING								{
																					char buf[256];
																					strncpy_s(buf, 256, &mesh_yytext[1], strlen(&mesh_yytext[1]) - 1);
																					mesh_callback->OnSubsetMaterial(cur_subset, buf);
																				}
																				
						;
						
						
%%
