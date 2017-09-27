#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

extern FILE *yyin;

int main (int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Missing file name.\nCall ./etapa1 file_name\n");
		exit(1);
	}
	yyin=fopen(argv[1],"r");
	if (!(yyin))
	{
		fprintf(stderr, "Cannot open file %s. \n", argv[1]);
	}
 	int tok = 0;

	 while(isRunning())
	 {
	 	tok = yylex();
		 switch (tok)
		  {
			case KW_BYTE:
				fprintf(stderr, "\nBYTE");
				break;
			case KW_SHORT:
				fprintf(stderr, "\nSHORT");
				break;
			case KW_LONG:
				fprintf(stderr, "\nLONG");
				break;
			case KW_FLOAT:
				fprintf(stderr, "\nFLOAT");
				break;
			case KW_DOUBLE:
				fprintf(stderr, "\nDOUBLE");
				break;
			case KW_IF:
				fprintf(stderr, "\nIF");
				break;
			case KW_THEN:
				fprintf(stderr, "\nTHEN");
				break;
			case KW_ELSE:
				fprintf(stderr, "\nELSE");
				break;
			case KW_WHILE:
				fprintf(stderr, "\nWHILE");
				break;
			case KW_FOR:
				fprintf(stderr, "\nFOR");
				break;
			case KW_READ:
				fprintf(stderr, "\nREAD");
				break;
			case KW_RETURN:
				fprintf(stderr, "\nRETURN");
				break;
			case KW_PRINT:
				fprintf(stderr, "\nPRINT");
				break;
			case OPERATOR_LE:
				fprintf(stderr, "\n(LE) <=");
				break;
			case OPERATOR_GE:
				fprintf(stderr, "\n(GE) >=");
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "\n(EQ) ==");
				break;
			case OPERATOR_NE:
				fprintf(stderr, "\n(NE) !=");
				break;
			case OPERATOR_AND:
				fprintf(stderr, "\n(AND) &&");
				break;
			case OPERATOR_OR:
				fprintf(stderr, "\n(OR) ||");
				break;
			case TK_IDENTIFIER:
				printf("\nIDENTIFIER");
				break;
			case LIT_INTEGER:
				printf("\nINT");
				break;
			case LIT_REAL:
				printf("\nREAL");
				break;
			case LIT_CHAR:
				printf("\nCHAR");
				break;
			case LIT_STRING:
				printf("\nSTRING");
				break;
			case TOKEN_ERROR:
				printf("\nERRO in line %d",getLineNumber());
				break;
			case 0:
				break;
			default:
				printf("\n%c",tok);
				break;
	    		}
	 }

	   printf("\nNumero de linhas do arquivo: %d\n", getLineNumber());
	   hashPrint();
 	exit(0);
} // END_MAIN
