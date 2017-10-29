%{
	#include "astree.h"
	#include "hash.h"
	#include "y.tab.h"

	int lineNumber = 1;
	int running = 1;

%}

%x COMMENT

%%

"byte"		{ return KW_BYTE;}
"short"		{ return KW_SHORT;}
"long"		{ return KW_LONG;}
"float"		{ return KW_FLOAT;}
"double"	{ return KW_DOUBLE;}
"if"		{ return KW_IF;}
"then"		{ return KW_THEN;}
"else"		{ return KW_ELSE;}
"while"		{ return KW_WHILE;}
"for"		{ return KW_FOR;}
"read"		{ return KW_READ;}
"return"	{ return KW_RETURN;}
"print"		{ return KW_PRINT;}

"<="		{ return OPERATOR_LE;}
">="		{ return OPERATOR_GE;}
"=="		{ return OPERATOR_EQ;}
"!="		{ return OPERATOR_NE;}
"&&"		{ return OPERATOR_AND;}
"\|\|"		{ return OPERATOR_OR;}

[a-zA-Z_]([a-zA-Z_0-9 ]*[a-zA-Z_0-9])?		{ yylval.symbol = hashInsert(yytext,SYMBOL_IDENTIFIER); return SYMBOL_IDENTIFIER;}
[0-9]+							{ yylval.symbol = hashInsert(yytext,SYMBOL_LIT_INT); return SYMBOL_LIT_INT;}
[0-9]+("."[0-9]+)				{ yylval.symbol = hashInsert(yytext,SYMBOL_LIT_REAL); return SYMBOL_LIT_REAL;}
"'"[a-zA-Z0-9]"'"				{ yylval.symbol = hashInsert(yytext,SYMBOL_LIT_CHAR); return SYMBOL_LIT_CHAR;}
\"[^\"\n]*\"					{ yylval.symbol = hashInsert(yytext,SYMBOL_LIT_STRING); return SYMBOL_LIT_STRING;}
[-,;:(){}+/<>=!&$#]				{ return yytext[0]; }
"["								{ return yytext[0]; }
"]"								{ return yytext[0]; }
"*"								{ return yytext[0]; }

"\n"						{ ++lineNumber;}
"//".*
"/*"						{BEGIN(COMMENT);}

<COMMENT>.
<COMMENT>"\n"			{ ++lineNumber; }
<COMMENT>"*/"			{BEGIN(INITIAL);}

[ \t\r]+

.				{return TOKEN_ERROR;}

%%

int getLineNumber()
{
	return lineNumber;
}

void initMe()
{
	running = 1;
	hashInit();
}
   
int isRunning()
{
	return running;
}

int yywrap(void)
{
	running = 0;
	return 1;
}
