
/*  A Bison parser, made from materialparser\\materialdescparser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse mat_yyparse
#define yylex mat_yylex
#define yyerror mat_yyerror
#define yylval mat_yylval
#define yychar mat_yychar
#define yydebug mat_yydebug
#define yynerrs mat_yynerrs
#define	TK_MATERIAL	258
#define	TK_EFFECT	259
#define	TK_INDEX	260
#define	TK_FLOAT2	261
#define	TK_FLOAT3	262
#define	TK_FLOAT4	263
#define	TK_PARAM	264
#define	TK_STRING	265
#define	TK_INTEGER	266
#define	TK_FLOAT	267

#line 1 "materialparser\\materialdescparser.y"


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


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		60
#define	YYFLAG		-32768
#define	YYNTBASE	22

#define YYTRANSLATE(x) ((unsigned)(x) <= 267 ? yytranslate[x] : 38)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
    21,     2,     2,    20,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    16,     2,
    15,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    17,     2,    18,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    13,     2,    14,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     8,    10,    13,    18,    19,    28,    30,    32,
    34,    35,    36,    37,    38,    53,    54,    55,    56,    68,
    69,    70,    79
};

static const short yyrhs[] = {    -1,
     3,    10,    23,    13,    24,    14,     0,    25,     0,    24,
    25,     0,    27,    15,    28,    16,     0,     0,     4,    17,
    12,    26,    18,    15,    28,    16,     0,     9,     0,    11,
     0,    10,     0,     0,     0,     0,     0,     8,    19,    12,
    29,    20,    12,    30,    20,    12,    31,    20,    12,    32,
    21,     0,     0,     0,     0,     7,    19,    12,    33,    20,
    12,    34,    20,    12,    35,    21,     0,     0,     0,     6,
    19,    12,    36,    20,    12,    37,    21,     0,    12,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    47,    52,    55,    57,    60,    94,    99,   108,   116,   122,
   127,   129,   130,   131,   132,   134,   136,   137,   138,   140,
   142,   143,   145
};

static const char * const yytname[] = {   "$","error","$undefined.","TK_MATERIAL",
"TK_EFFECT","TK_INDEX","TK_FLOAT2","TK_FLOAT3","TK_FLOAT4","TK_PARAM","TK_STRING",
"TK_INTEGER","TK_FLOAT","'{'","'}'","'='","';'","'['","']'","'('","','","')'",
"material","@1","declaration_list","declaration","@2","parameter","value","@3",
"@4","@5","@6","@7","@8","@9","@10","@11",""
};
#endif

static const short yyr1[] = {     0,
    23,    22,    24,    24,    25,    26,    25,    27,    28,    28,
    29,    30,    31,    32,    28,    33,    34,    35,    28,    36,
    37,    28,    28
};

static const short yyr2[] = {     0,
     0,     6,     1,     2,     4,     0,     8,     1,     1,     1,
     0,     0,     0,     0,    14,     0,     0,     0,    11,     0,
     0,     8,     1
};

static const short yydefact[] = {     0,
     0,     1,     0,     0,     0,     8,     0,     3,     0,     0,
     2,     4,     0,     6,     0,     0,     0,    10,     9,    23,
     0,     0,     0,     0,     0,     5,     0,    20,    16,    11,
     0,     0,     0,     0,     0,     0,     0,     0,     7,    21,
    17,    12,     0,     0,     0,    22,     0,     0,    18,    13,
     0,     0,    19,     0,    14,     0,    15,     0,     0,     0
};

static const short yydefgoto[] = {    58,
     3,     7,     8,    22,     9,    21,    34,    45,    52,    56,
    33,    44,    51,    32,    43
};

static const short yypact[] = {    -1,
    -7,-32768,    -9,    -3,    -2,-32768,    -4,-32768,     2,     4,
-32768,-32768,     1,-32768,    -5,     0,     3,-32768,-32768,-32768,
     5,     6,     8,    11,    13,-32768,    12,-32768,-32768,-32768,
     1,     9,    10,    14,    15,    16,    20,    21,-32768,-32768,
-32768,-32768,    17,    19,    22,-32768,    23,    24,-32768,-32768,
    25,    27,-32768,    28,-32768,    29,-32768,    18,    26,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,    30,-32768,-32768,    31,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		62


static const short yytable[] = {     5,
     5,     1,     2,     4,     6,     6,    15,    16,    17,    11,
    18,    19,    20,    23,    10,    14,    13,    59,    24,    28,
    26,    25,    29,    27,    30,    60,    31,    40,    36,    37,
    39,    41,    42,    38,    49,    50,    12,    46,    47,    55,
     0,    48,     0,     0,     0,    53,    54,     0,     0,    57,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    35
};

static const short yycheck[] = {     4,
     4,     3,    10,    13,     9,     9,     6,     7,     8,    14,
    10,    11,    12,    19,    17,    12,    15,     0,    19,    12,
    16,    19,    12,    18,    12,     0,    15,    12,    20,    20,
    16,    12,    12,    20,    12,    12,     7,    21,    20,    12,
    -1,    20,    -1,    -1,    -1,    21,    20,    -1,    -1,    21,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    31
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef _WIN32
#include <malloc.h>
#endif
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

void yyerror(char *);

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 47 "materialparser\\materialdescparser.y"
{
																					strncpy_s(s_str, 256, &mat_yytext[1], strlen(&mat_yytext[1]) - 1);
																					mat_callback->OnMaterialName(s_str);
																				;
    break;}
case 2:
#line 52 "materialparser\\materialdescparser.y"
{ ;
    break;}
case 3:
#line 55 "materialparser\\materialdescparser.y"
{ ;
    break;}
case 4:
#line 57 "materialparser\\materialdescparser.y"
{ ;
    break;}
case 5:
#line 60 "materialparser\\materialdescparser.y"
{
																					// Append value
																					switch(yyvsp[-1])
																					{
																						case TK_FLOAT: s_color[1] = 0.0f; /*fallthrough*/
																						case TK_FLOAT2: s_color[2] = 0.0f; /*fallthrough*/
																						case TK_FLOAT3: s_color[3] = 1.0f;
																					}
																					
																					// Set value
																					if(yyvsp[-3] > FXP_START_FLOAT_TYPES && yyvsp[-3] < FXP_END_FLOAT_TYPES)
																					{
																						if(yyvsp[-1] != TK_FLOAT)
																							mat_yyerror("bad value type");
																						mat_callback->OnFloatBinding((EEffectParam)yyvsp[-3], s_color[0]);
																					}
																					
																					if(yyvsp[-3] > FXP_START_TEXTURE_TYPES && yyvsp[-3] < FXP_END_TEXTURE_TYPES)
																					{
																						if(yyvsp[-1] != TK_STRING)
																							mat_yyerror("bad value type");
																						mat_callback->OnTextureBinding((EEffectParam)yyvsp[-3], s_str);
																					}
																					
																					if(yyvsp[-3] > FXP_START_COLOR_TYPES && yyvsp[-3] < FXP_END_COLOR_TYPES)
																					{
																						if(yyvsp[-1] != TK_FLOAT3 && yyvsp[-1] != TK_FLOAT4)
																							mat_yyerror("bad value type");
																						VML::Vector4 v(s_color[0], s_color[1], s_color[2], s_color[3]);
																						mat_callback->OnColorBinding((EEffectParam)yyvsp[-3], v);
																					}
																				;
    break;}
case 6:
#line 94 "materialparser\\materialdescparser.y"
{
																					s_index = atoi(mat_yytext);
																					if(errno) mat_yyerror("bad stage value");
																				;
    break;}
case 7:
#line 99 "materialparser\\materialdescparser.y"
{
																					if(yyvsp[-1] != TK_STRING)
																							mat_yyerror("bad value type");
																							
																					mat_callback->OnEffectDefinition(s_index, s_str);
																				;
    break;}
case 8:
#line 108 "materialparser\\materialdescparser.y"
{
																					yyval = EEffectParam_FromString(mat_yytext);
																					if(yyval == (EEffectParam)-1)
																						mat_yyerror("bad parameter name");
																				;
    break;}
case 9:
#line 116 "materialparser\\materialdescparser.y"
{
																					int val = hexToInt(&mat_yytext[2]);
																					intToFloat4(val);
																					yyval = TK_FLOAT4 /* converted */;
																				;
    break;}
case 10:
#line 122 "materialparser\\materialdescparser.y"
{
																					strncpy_s(s_str, 256, &mat_yytext[1], strlen(&mat_yytext[1]) - 1);
																					yyval = TK_STRING;
																				;
    break;}
case 11:
#line 128 "materialparser\\materialdescparser.y"
{ s_color[0] = (float)atof(mat_yytext); ;
    break;}
case 12:
#line 129 "materialparser\\materialdescparser.y"
{ s_color[1] = (float)atof(mat_yytext); ;
    break;}
case 13:
#line 130 "materialparser\\materialdescparser.y"
{ s_color[2] = (float)atof(mat_yytext); ;
    break;}
case 14:
#line 131 "materialparser\\materialdescparser.y"
{ s_color[3] = (float)atof(mat_yytext); ;
    break;}
case 15:
#line 132 "materialparser\\materialdescparser.y"
{ yyval = TK_FLOAT4; ;
    break;}
case 16:
#line 135 "materialparser\\materialdescparser.y"
{ s_color[0] = (float)atof(mat_yytext); ;
    break;}
case 17:
#line 136 "materialparser\\materialdescparser.y"
{ s_color[1] = (float)atof(mat_yytext); ;
    break;}
case 18:
#line 137 "materialparser\\materialdescparser.y"
{ s_color[2] = (float)atof(mat_yytext); ;
    break;}
case 19:
#line 138 "materialparser\\materialdescparser.y"
{ yyval = TK_FLOAT3; ;
    break;}
case 20:
#line 141 "materialparser\\materialdescparser.y"
{ s_color[0] = (float)atof(mat_yytext); ;
    break;}
case 21:
#line 142 "materialparser\\materialdescparser.y"
{ s_color[1] = (float)atof(mat_yytext); ;
    break;}
case 22:
#line 143 "materialparser\\materialdescparser.y"
{ yyval = TK_FLOAT2; ;
    break;}
case 23:
#line 145 "materialparser\\materialdescparser.y"
{ s_color[0] = (float)atof(mat_yytext); yyval = TK_FLOAT; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 147 "materialparser\\materialdescparser.y"


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