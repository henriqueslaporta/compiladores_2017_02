#include <stdio.h>
#include <stdlib.h>

#include "astree.h"
#include "hash.h"
#include "y.tab.h"

extern FILE *yyin;
extern int getLineNumber();
extern void hashPrint();

int main (int argc, char **argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "Missing file name.\nCall ./etapa1 {file_name} {outputfile_name}\n");
		exit(1);
	}
	yyin=fopen(argv[1],"r");
	if (!(yyin))
	{
		fprintf(stderr, "Cannot open file %s. \n", argv[1]);
	}
	

	if (!(outputfile = fopen(argv[2],"w")))
	{
		fprintf(stderr, "Cannot open Outputfile %s. \n", argv[2]);
	}
	
	yyparse();
	
	fclose(outputfile);

	//printf("\nNumero de linhas do arquivo: %d\n", getLineNumber()-1);
	//hashPrint();

	fprintf(stderr,"Programa pertence a linguagem. \n");
 	exit(0);
} // END_MAIN
