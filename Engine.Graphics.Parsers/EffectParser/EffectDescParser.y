%{
	#include <string>
	#include "../Common/Token.h"
	#include "../../Engine.Graphics/Interfaces/EffectTypes.h"
	
	using namespace Engine::Graphics;
	
	extern char* fx_yytext;
	extern FILE* fx_yyin;
	extern int fx_yylex();
	//#define YYDEBUG 1
	
		
	SEffectDesc* cur_effect;
	std::string* effect_source;
	static SEffectParams* sParamScope; 
%}

%token TK_EFFECT
%token TK_STRING
%token TK_PARAM
%token TK_CAP

%%

effect:				TK_EFFECT TK_STRING											{
																					sParamScope = cur_effect->getGlobalParameters();
																					if(effect_source) effect_source->assign(fx_yytext, 1, strlen(fx_yytext) - 2);
																				}
																				
					'{' declaration_list '}'									{ }
					;
					


declaration_list:	declaration													{ }

					| declaration_list declaration 								{ }
					
					;


declaration:		parameter_list												{ }

					| effect_cap												{ }
					
					| scoped_cap												{ }
					
					;
					

scoped_cap:			cap_scope_start parameter_list '}' | cap_scope_start '}'	{
																					sParamScope = cur_effect->getGlobalParameters();
																				}

					;


cap_scope_start:	TK_CAP '{'													{
																					cur_effect->setCapSupport((EEffectCap)$1.intval, true);
																					sParamScope = cur_effect->getScopedParameters((EEffectCap)$1.intval);
																				}

					;
					
					
effect_cap:			TK_CAP ';'													{
																					cur_effect->setCapSupport((EEffectCap)$1.intval, true);
																					sParamScope = cur_effect->getScopedParameters((EEffectCap)$1.intval);
																				}

					;
										

parameter_list:		parameter													{ }

					| parameter_list parameter									{ }
					
					;

					
parameter:			TK_PARAM ';'												{
																					sParamScope->setUsageState(
																						(EEffectParam)$1.intval,
																						true);
																				}

					;
					
%%
