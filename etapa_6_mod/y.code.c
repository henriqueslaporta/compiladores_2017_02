/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
#include <stdio.h>
#include <stdlib.h>

#include "astree.h"
#include "hash.h"
#include "semantic.h"
#include "genco.h"

int yylex();
int yyerror(char *msg);
#line 14 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	AST* ast;
	HASH_NODE *symbol;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 44 "y.code.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

#define KW_BYTE 256
#define KW_SHORT 257
#define KW_LONG 258
#define KW_FLOAT 259
#define KW_DOUBLE 260
#define KW_IF 261
#define KW_THEN 262
#define KW_ELSE 263
#define KW_WHILE 264
#define KW_FOR 265
#define KW_READ 266
#define KW_RETURN 267
#define KW_PRINT 268
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define SYMBOL_IDENTIFIER 269
#define SYMBOL_LIT_INT 276
#define SYMBOL_LIT_REAL 277
#define SYMBOL_LIT_CHAR 278
#define SYMBOL_LIT_STRING 279
#define TOKEN_ERROR 290
#define YYERRCODE 256
#define YYTABLESIZE 663
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 314
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))

extern int YYPARSE_DECL();
typedef short YYINT;
extern YYINT yylhs[];
extern YYINT yylen[];
extern YYINT yydefred[];
extern YYINT yydgoto[];
extern YYINT yysindex[];
extern YYINT yyrindex[];
extern YYINT yygindex[];
extern YYINT yytable[];
extern YYINT yycheck[];

#if YYDEBUG
extern char *yyname[];
extern char *yyrule[];
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 203 "parser.y"

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
#line 166 "y.code.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 77 "parser.y"
	{
	/*astPrint($1,0);*/
	astPrintToFile(yystack.l_mark[0].ast, outputfile);
  	semanticSetTypes(yystack.l_mark[0].ast);
  	semanticCheckUndeclared();
  	semanticCheckUsage(yystack.l_mark[0].ast);
  	semanticCheckOperands(yystack.l_mark[0].ast);
		semanticCheckReturnType(yystack.l_mark[0].ast);
		tacPrintForward(tacInvertList(tacGenerator(yystack.l_mark[0].ast)));
	}
break;
case 2:
#line 88 "parser.y"
	{ yyval.ast = astCreate(AST_DECLARATION,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 3:
#line 89 "parser.y"
	{ yyval.ast = 0; }
break;
case 4:
#line 92 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 5:
#line 93 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 6:
#line 96 "parser.y"
	{ yyval.ast = astCreate(AST_VAR_DEC,yystack.l_mark[-5].symbol,yystack.l_mark[-3].ast,yystack.l_mark[-1].ast,0,0); }
break;
case 7:
#line 97 "parser.y"
	{ yyval.ast = astCreate(AST_VECTOR_DEC,yystack.l_mark[-7].symbol,yystack.l_mark[-5].ast,yystack.l_mark[-3].ast,yystack.l_mark[-1].ast,0); }
break;
case 8:
#line 100 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[-1].symbol,yystack.l_mark[0].ast,0,0,0); }
break;
case 9:
#line 101 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[-1].symbol,yystack.l_mark[0].ast,0,0,0); }
break;
case 10:
#line 102 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[-1].symbol,yystack.l_mark[0].ast,0,0,0); }
break;
case 11:
#line 103 "parser.y"
	{ yyval.ast = 0; }
break;
case 12:
#line 106 "parser.y"
	{ yyval.ast = astCreate(AST_KW_BYTE,0,0,0,0,0); }
break;
case 13:
#line 107 "parser.y"
	{ yyval.ast = astCreate(AST_KW_SHORT,0,0,0,0,0); }
break;
case 14:
#line 108 "parser.y"
	{ yyval.ast = astCreate(AST_KW_LONG,0,0,0,0,0); }
break;
case 15:
#line 109 "parser.y"
	{ yyval.ast = astCreate(AST_KW_FLOAT,0,0,0,0,0); }
break;
case 16:
#line 110 "parser.y"
	{ yyval.ast = astCreate(AST_KW_DOUBLE,0,0,0,0,0); }
break;
case 17:
#line 113 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 18:
#line 114 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 19:
#line 115 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 20:
#line 116 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 21:
#line 119 "parser.y"
	{ yyval.ast = astCreate(AST_FUNC_DEC,yystack.l_mark[-4].symbol,yystack.l_mark[-6].ast,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast); }
break;
case 22:
#line 122 "parser.y"
	{ yyval.ast = astCreate(AST_FUNC_ARGL,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 23:
#line 123 "parser.y"
	{ yyval.ast  = 0; }
break;
case 24:
#line 126 "parser.y"
	{ yyval.ast = astCreate(AST_FUNC_ARG,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 25:
#line 127 "parser.y"
	{ yyval.ast  = 0; }
break;
case 26:
#line 130 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0); }
break;
case 27:
#line 133 "parser.y"
	{ yyval.ast = astCreate(AST_BLOCK,0,yystack.l_mark[-1].ast,0,0,0);  }
break;
case 28:
#line 136 "parser.y"
	{ yyval.ast = astCreate(AST_CMD_LIST,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 29:
#line 137 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 30:
#line 140 "parser.y"
	{ yyval.ast = astCreate(AST_ATRIB,yystack.l_mark[-2].symbol,yystack.l_mark[0].ast,0,0,0); }
break;
case 31:
#line 141 "parser.y"
	{ yyval.ast = astCreate(AST_VEC_ATRIB,yystack.l_mark[-5].symbol,yystack.l_mark[-3].ast,yystack.l_mark[0].ast,0,0); }
break;
case 32:
#line 142 "parser.y"
	{ yyval.ast = astCreate(AST_KW_READ,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 33:
#line 143 "parser.y"
	{ yyval.ast = astCreate(AST_KW_RETURN,0,yystack.l_mark[0].ast,0,0,0); }
break;
case 34:
#line 144 "parser.y"
	{ yyval.ast = astCreate(AST_KW_PRINT,0,yystack.l_mark[0].ast,0,0,0); }
break;
case 35:
#line 145 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 36:
#line 146 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 37:
#line 147 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 38:
#line 148 "parser.y"
	{ yyval.ast = 0; }
break;
case 39:
#line 151 "parser.y"
	{ yyval.ast = astCreate(AST_ARG_PRINT,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 40:
#line 154 "parser.y"
	{ yyval.ast = astCreate(AST_ARG_PRINT,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 41:
#line 155 "parser.y"
	{ yyval.ast = 0; }
break;
case 42:
#line 158 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 43:
#line 159 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 44:
#line 162 "parser.y"
	{ yyval.ast = astCreate(AST_ADD,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 45:
#line 163 "parser.y"
	{ yyval.ast = astCreate(AST_SUB,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 46:
#line 164 "parser.y"
	{ yyval.ast = astCreate(AST_MUL,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 47:
#line 165 "parser.y"
	{ yyval.ast = astCreate(AST_DIV,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 48:
#line 166 "parser.y"
	{ yyval.ast = astCreate(AST_LESS,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 49:
#line 167 "parser.y"
	{ yyval.ast = astCreate(AST_GREAT,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 50:
#line 168 "parser.y"
	{ yyval.ast = astCreate(AST_NEG,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 51:
#line 169 "parser.y"
	{ yyval.ast = astCreate(AST_LE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 52:
#line 170 "parser.y"
	{ yyval.ast = astCreate(AST_GE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 53:
#line 171 "parser.y"
	{ yyval.ast = astCreate(AST_EQ,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 54:
#line 172 "parser.y"
	{ yyval.ast = astCreate(AST_NE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 55:
#line 173 "parser.y"
	{ yyval.ast = astCreate(AST_AND,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 56:
#line 174 "parser.y"
	{ yyval.ast = astCreate(AST_OR,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
case 57:
#line 175 "parser.y"
	{ yyval.ast = astCreate(AST_FUNC_CALL,yystack.l_mark[-3].symbol,yystack.l_mark[-1].ast,0,0,0); }
break;
case 58:
#line 176 "parser.y"
	{ yyval.ast = astCreate(AST_ARRAY_POS,yystack.l_mark[-3].symbol,yystack.l_mark[-1].ast,0,0,0); }
break;
case 59:
#line 177 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 60:
#line 178 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 61:
#line 179 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 62:
#line 180 "parser.y"
	{ yyval.ast = astCreate(AST_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0); }
break;
case 63:
#line 181 "parser.y"
	{ yyval.ast = astCreate(AST_EXP_P,0,yystack.l_mark[-1].ast,0,0,0); }
break;
case 64:
#line 184 "parser.y"
	{ yyval.ast = astCreate(AST_FUNPARAML,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 65:
#line 185 "parser.y"
	{ yyval.ast = 0; }
break;
case 66:
#line 188 "parser.y"
	{ yyval.ast = astCreate(AST_FUNPARAML,0,yystack.l_mark[-1].ast,yystack.l_mark[0].ast,0,0); }
break;
case 67:
#line 189 "parser.y"
	{ yyval.ast = 0; }
break;
case 68:
#line 194 "parser.y"
	{ yyval.ast = astCreate(AST_CMD_IF,0,yystack.l_mark[-3].ast,yystack.l_mark[0].ast,0,0); }
break;
case 69:
#line 195 "parser.y"
	{ yyval.ast = astCreate(AST_CMD_IF,0,yystack.l_mark[-5].ast,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0); }
break;
case 70:
#line 198 "parser.y"
	{ yyval.ast = astCreate(AST_CMD_WHILE,0,yystack.l_mark[-2].ast,yystack.l_mark[0].ast,0,0); }
break;
#line 657 "y.code.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
