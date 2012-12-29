#ifndef _TOKEN_H__
#define _TOKEN_H__

struct Token
{
	union
	{
		void*	voidp;
		char*	text;
		int		intval;
	};

	Token () : voidp(0) { }

	operator char* () const { return text; }
	operator const char* () const { return text; }
	operator void* () const { return voidp; }
	operator int () const { return intval; }
};

#define YYSTYPE Token
extern YYSTYPE fx_yylval;

#endif // _TOKEN_H__