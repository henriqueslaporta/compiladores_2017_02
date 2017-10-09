%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(char *msg);

%}


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

%token TK_IDENTIFIER 280
%token LIT_INTEGER 281
%token LIT_REAL 282
%token LIT_CHAR 285
%token LIT_STRING 286

%token TOKEN_ERROR 290

%left '+' '-'
%left '*' '/' 
%left OPERATOR_AND OPERATOR_OR '!'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE

%%
program : decl

decl : dec decl
	|	
	;

dec : vardec
	| fundec
	;

vardec : TK_IDENTIFIER ':' tipevardec '=' literal ';'
	| TK_IDENTIFIER ':' tipevardec'['LIT_INTEGER']' vectorinit ';'
	;
	
vectorinit: LIT_INTEGER vectorinit
	| LIT_REAL vectorinit
	| LIT_CHAR vectorinit
	| 
	;

tipevardec: KW_BYTE
	| KW_SHORT
	| KW_LONG
	| KW_FLOAT
	| KW_DOUBLE
	;

literal: LIT_INTEGER
	| LIT_REAL
	| LIT_CHAR
	| LIT_STRING
	;

fundec : '('tipevardec')' TK_IDENTIFIER '(' funargl ')' block
	;

funargl: TK_IDENTIFIER ':' tipevardec ',' funargl
	| TK_IDENTIFIER ':' tipevardec funargl
	|
	;

block : '{' lcmd '}'
	;

lcmd: cmd ';' lcmd
	| cmd
	| block ';' lcmd
	| block
	; 

cmd : TK_IDENTIFIER '=' exp
	| TK_IDENTIFIER'['exp']' '=' exp
	| KW_READ '>' TK_IDENTIFIER 
	| KW_RETURN exp
	| KW_PRINT eprint
	| cmdif
	| cmdwhile
	|
	;

eprint: argprint restprint
	;

restprint: ',' argprint restprint
	|
	;

argprint: exp
	| LIT_STRING
	;

exp :  exp '+' exp
	| exp '-' exp
	| exp '/' exp
	| exp '<' exp
	| exp '>' exp
	| exp '!' exp
	| exp OPERATOR_LE exp
	| exp OPERATOR_GE exp
	| exp OPERATOR_EQ exp
	| exp OPERATOR_NE exp
	| exp OPERATOR_AND exp
	| exp OPERATOR_OR exp
	| TK_IDENTIFIER '('funparaml')'
	| TK_IDENTIFIER '['exp']'
	| LIT_INTEGER
	| TK_IDENTIFIER
	| '('exp')'
	;

funparaml: funparam  ',' funparaml
	| funparam
	|
	;
	
funparam:  TK_IDENTIFIER
	| LIT_INTEGER
	| LIT_REAL
	| LIT_CHAR
	| LIT_STRING
	;



cmdif: KW_IF '('exp')' KW_THEN block
	| KW_IF '('exp')' KW_THEN cmd
	| KW_IF '('exp')' KW_THEN block KW_ELSE block
	| KW_IF '('exp')' KW_THEN block KW_ELSE cmd
	;

cmdwhile: KW_WHILE '('exp')' block
	;


%%



int yyerrror(char *msg){
	fprintf(stderr,"Eita, erro1!!@\n");
	exit(3);
}
