#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "y.tab.h"

extern FILE *yyin;
extern int getLineNumber();
extern void hashPrint();

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
	
	yyparse();

	//printf("\nNumero de linhas do arquivo: %d\n", getLineNumber()-1);
	//hashPrint();

	fprintf(stderr,"Programa pertence a linguagem. \n");
 	exit(0);
} // END_MAIN
