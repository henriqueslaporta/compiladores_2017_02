%{
#include <stdio.h>
#include <stdlib.h>

#include "astree.h"
#include "hash.h"
#include "semantic.h"

int yylex();
int yyerror(char *msg);
%}

%union {
	AST* ast;
	HASH_NODE *symbol;
}

%token KW_BYTE 256
%token KW_SHORT 257
%token KW_LONG 258
%token KW_FLOAT 259
%token KW_DOUBLE 260
%token KW_IF 261
%token KW_THEN 262
%token KW_ELSE 263
%token KW_WHILE 264
%token KW_FOR 265
%token KW_READ 266
%token KW_RETURN 267
%token KW_PRINT 268

%token OPERATOR_LE 270
%token OPERATOR_GE 271
%token OPERATOR_EQ 272
%token OPERATOR_NE 273
%token OPERATOR_AND 274
%token OPERATOR_OR 275

%token<symbol> SYMBOL_IDENTIFIER
%token<symbol> SYMBOL_LIT_INT
%token<symbol> SYMBOL_LIT_REAL
%token<symbol> SYMBOL_LIT_CHAR
%token<symbol> SYMBOL_LIT_STRING

%token TOKEN_ERROR 290

%type<ast> program
%type<ast> decl
%type<ast> dec
%type<ast> exp
%type<ast> vardec
%type<ast> fundec
%type<ast> tipevardec
%type<ast> vectorinit
%type<ast> literal
%type<ast> funargl
%type<ast> funrest
%type<ast> funarg
%type<ast> block
%type<ast> lcmd
%type<ast> cmd
%type<ast> cmdif
%type<ast> cmdwhile
%type<ast> eprint
%type<ast> restprint
%type<ast> argprint
%type<ast> funparaml
%type<ast> funparamrest

%left OPERATOR_AND OPERATOR_OR '!'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'

%%
program : decl				{
	//astPrint($1,0);
	astPrintToFile($1, outputfile);
  	semanticSetTypes($1);
  	semanticCheckUndeclared();
  	semanticCheckUsage($1);
  	semanticCheckOperands($1);
  	semanticCheckVectorIndex($1);
		semanticCheckReturnType($1);
	} //chamar todas as funçoes de check aqui

decl : dec decl				{ $$ = astCreate(AST_DECLARATION,0,$1,$2,0,0); }
	|						{ $$ = 0; }
	;

dec : fundec				{ $$ = $1; }
	| vardec				{ $$ = $1; }
	;

vardec : SYMBOL_IDENTIFIER ':' tipevardec '=' literal ';'					{ $$ = astCreate(AST_VAR_DEC,$1,$3,$5,0,0); }
	| SYMBOL_IDENTIFIER ':' tipevardec'['literal']' vectorinit ';'	{ $$ = astCreate(AST_VECTOR_DEC,$1,$3,$5,$7,0); }
	;

vectorinit: SYMBOL_LIT_INT vectorinit					{ $$ = astCreate(AST_SYMBOL,$1,$2,0,0,0); }
	| SYMBOL_LIT_REAL vectorinit						{ $$ = astCreate(AST_SYMBOL,$1,$2,0,0,0); }
	| SYMBOL_LIT_CHAR vectorinit						{ $$ = astCreate(AST_SYMBOL,$1,$2,0,0,0); }
	|													{ $$ = 0; }
	;

tipevardec: KW_BYTE						{ $$ = astCreate(AST_KW_BYTE,0,0,0,0,0); }
	| KW_SHORT							{ $$ = astCreate(AST_KW_SHORT,0,0,0,0,0); }
	| KW_LONG							{ $$ = astCreate(AST_KW_LONG,0,0,0,0,0); }
	| KW_FLOAT							{ $$ = astCreate(AST_KW_FLOAT,0,0,0,0,0); }
	| KW_DOUBLE							{ $$ = astCreate(AST_KW_DOUBLE,0,0,0,0,0); }
	;

literal: SYMBOL_LIT_INT					{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_REAL					{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_CHAR					{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_STRING					{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	;

fundec : '('tipevardec')' SYMBOL_IDENTIFIER '(' funargl ')' block	{ $$ = astCreate(AST_FUNC_DEC,$4,$2,0,$6,$8); }
	;

funargl: funarg funrest					{ $$ = astCreate(AST_FUNC_ARGL,0,$1,$2,0,0); }
	|									{ $$  = 0; }
	;

funrest: ',' funarg funrest				{ $$ = astCreate(AST_FUNC_ARG,0,$2,$3,0,0); }
	|									{ $$  = 0; }
	;

funarg: SYMBOL_IDENTIFIER ':' tipevardec	{ $$ = astCreate(AST_SYMBOL,$1,$3,0,0,0); }
	;

block : '{' lcmd '}'			{ $$ = astCreate(AST_BLOCK,0,$2,0,0,0);  }
	;

lcmd: cmd ';' lcmd				{ $$ = astCreate(AST_CMD_LIST,0,$1,$3,0,0); }
	| cmd						{ $$ = $1; }
	;

cmd : SYMBOL_IDENTIFIER '=' exp				{ $$ = astCreate(AST_ATRIB,$1,$3,0,0,0); }
	| SYMBOL_IDENTIFIER'['exp']' '=' exp	{ $$ = astCreate(AST_VEC_ATRIB,$1,$3,$6,0,0); }
	| KW_READ '>' SYMBOL_IDENTIFIER			{ $$ = astCreate(AST_KW_READ,$3,0,0,0,0); }
	| KW_RETURN exp							{ $$ = astCreate(AST_KW_RETURN,0,$2,0,0,0); }
	| KW_PRINT eprint						{ $$ = astCreate(AST_KW_PRINT,0,$2,0,0,0); }
	| cmdif									{ $$ = $1; }
	| cmdwhile								{ $$ = $1; }
	| block									{ $$ = $1; }
	|										{ $$ = 0; }
	;

eprint: argprint restprint					{ $$ = astCreate(AST_ARG_PRINT,0,$1,$2,0,0); }
	;

restprint: ',' argprint restprint			{ $$ = astCreate(AST_ARG_PRINT,0,$2,$3,0,0); }
	|										{ $$ = 0; }
	;

argprint: exp								{ $$ = $1; }
	| SYMBOL_LIT_STRING						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	;

exp :  exp '+' exp							{ $$ = astCreate(AST_ADD,0,$1,$3,0,0); }
	| exp '-' exp							{ $$ = astCreate(AST_SUB,0,$1,$3,0,0); }
	| exp '*' exp							{ $$ = astCreate(AST_MUL,0,$1,$3,0,0); }
	| exp '/' exp							{ $$ = astCreate(AST_DIV,0,$1,$3,0,0); }
	| exp '<' exp							{ $$ = astCreate(AST_LESS,0,$1,$3,0,0); }
	| exp '>' exp							{ $$ = astCreate(AST_GREAT,0,$1,$3,0,0); }
	| exp '!' exp							{ $$ = astCreate(AST_NEG,0,$1,$3,0,0); }
	| exp OPERATOR_LE exp					{ $$ = astCreate(AST_LE,0,$1,$3,0,0); }
	| exp OPERATOR_GE exp					{ $$ = astCreate(AST_GE,0,$1,$3,0,0); }
	| exp OPERATOR_EQ exp					{ $$ = astCreate(AST_EQ,0,$1,$3,0,0); }
	| exp OPERATOR_NE exp					{ $$ = astCreate(AST_NE,0,$1,$3,0,0); }
	| exp OPERATOR_AND exp					{ $$ = astCreate(AST_AND,0,$1,$3,0,0); }
	| exp OPERATOR_OR exp					{ $$ = astCreate(AST_OR,0,$1,$3,0,0); }
	| SYMBOL_IDENTIFIER '('funparaml')'		{ $$ = astCreate(AST_FUNC_CALL,$1,$3,0,0,0); }
	| SYMBOL_IDENTIFIER '['exp']'			{ $$ = astCreate(AST_ARRAY_POS,$1,$3,0,0,0); }
	| SYMBOL_LIT_INT						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_REAL						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_CHAR						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_IDENTIFIER						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| '('exp')'								{ $$ = astCreate(AST_EXP_P,0,$2,0,0,0); }
	;

funparaml: exp funparamrest					{ $$ = astCreate(AST_FUNPARAML,0,$1,$2,0,0); }
	|										{ $$ = 0; }
	;

funparamrest : ',' exp funparamrest			{ $$ = astCreate(AST_FUNPARAML,0,$2,$3,0,0); }
	|										{ $$ = 0; }
	;



cmdif: KW_IF '('exp')' KW_THEN cmd				{ $$ = astCreate(AST_CMD_IF,0,$3,$6,0,0); }
	| KW_IF '('exp')' KW_THEN cmd KW_ELSE cmd	{ $$ = astCreate(AST_CMD_IF,0,$3,$6,$8,0); }
	;

cmdwhile: KW_WHILE '('exp')' cmd				{ $$ = astCreate(AST_CMD_WHILE,0,$3,$5,0,0); }
	;


%%

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
