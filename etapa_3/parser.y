%{
#include <stdio.h>
#include <stdlib.h>

#include "astree.h"
#include "hash.h"

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

%type<ast> exp


%left OPERATOR_AND OPERATOR_OR '!'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'

%%
program : decl

decl : dec decl
	|
	;

dec : vardec
	| fundec
	;

vardec : SYMBOL_IDENTIFIER ':' tipevardec '=' literal ';'
	| SYMBOL_IDENTIFIER ':' tipevardec'['SYMBOL_LIT_INT']' vectorinit ';'
	;

vectorinit: SYMBOL_LIT_INT vectorinit
	| SYMBOL_LIT_REAL vectorinit
	| SYMBOL_LIT_CHAR vectorinit
	|
	;

tipevardec: KW_BYTE							
	| KW_SHORT								
	| KW_LONG								
	| KW_FLOAT								
	| KW_DOUBLE								
	;

literal: SYMBOL_LIT_INT						
	| SYMBOL_LIT_REAL						
	| SYMBOL_LIT_CHAR						
	| SYMBOL_LIT_STRING					
	;

fundec : '('tipevardec')' SYMBOL_IDENTIFIER '(' funargl ')' block	
	;

funargl: funarg funrest					
	|										
	;

funrest: ',' funarg funrest					
	|									
	;

funarg: SYMBOL_IDENTIFIER ':' tipevardec
	;

block : '{' lcmd '}'			
	;

lcmd: cmd ';' lcmd						
	| cmd					
	;

cmd : SYMBOL_IDENTIFIER '=' exp
	| SYMBOL_IDENTIFIER'['exp']' '=' exp
	| KW_READ '>' SYMBOL_IDENTIFIER
	| KW_RETURN exp
	| KW_PRINT eprint
	| cmdif
	| cmdwhile
	| block
	|
	;

eprint: argprint restprint
	;

restprint: ',' argprint restprint
	|
	;

argprint: exp								{ astPrint($1,0);}
	| SYMBOL_LIT_STRING
	;

exp :  exp '+' exp							{ $$ = astCreate(AST_ADD,0,$1,$3,0,0); }
	| exp '-' exp							{ $$ = astCreate(AST_SUB,0,$1,$3,0,0); }
	| exp '*' exp							{ $$ = astCreate(AST_MUL,0,$1,$3,0,0); }
	| exp '/' exp							{ $$ = astCreate(AST_DIV,0,$1,$3,0,0); }
	| exp '<' exp							{ $$ = astCreate(AST_L,0,$1,$3,0,0); }
	| exp '>' exp							{ $$ = astCreate(AST_G,0,$1,$3,0,0); }
	| exp '!' exp							{ $$ = astCreate(AST_NEG,0,$1,$3,0,0); }
	| exp OPERATOR_LE exp					{ $$ = astCreate(AST_LE,0,$1,$3,0,0); }
	| exp OPERATOR_GE exp					{ $$ = astCreate(AST_GE,0,$1,$3,0,0); }
	| exp OPERATOR_EQ exp					{ $$ = astCreate(AST_EQ,0,$1,$3,0,0); }
	| exp OPERATOR_NE exp					{ $$ = astCreate(AST_NE,0,$1,$3,0,0); }
	| exp OPERATOR_AND exp					{ $$ = astCreate(AST_AND,0,$1,$3,0,0); }
	| exp OPERATOR_OR exp					{ $$ = astCreate(AST_OR,0,$1,$3,0,0); }
	| SYMBOL_IDENTIFIER '('funparaml')'		{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_IDENTIFIER '['exp']'			{ $$ = astCreate(AST_SYMBOL,$1,$3,0,0,0); }
	| SYMBOL_LIT_INT						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_REAL						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_LIT_CHAR						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| SYMBOL_IDENTIFIER						{ $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
	| '('exp')'								{ $$ = astCreate(AST_EXP_P,0,$2,0,0,0); }
	;

funparaml: exp funparamrest
	|
	;

funparamrest : ',' exp funparamrest
	|
	;



cmdif: KW_IF '('exp')' KW_THEN cmd				
	| KW_IF '('exp')' KW_THEN cmd KW_ELSE cmd	
	;

cmdwhile: KW_WHILE '('exp')' cmd
	;


%%

int yyerror(char *msg){
	fprintf(stderr,"[ERRO] Linha %d: %s\n",getLineNumber(), msg);
	exit(3);
}
