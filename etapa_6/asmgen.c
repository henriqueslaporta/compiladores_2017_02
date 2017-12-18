#include <string.h>
#include "asmgen.h"

int findString(char *stringName){
    int i, found = 0;

    for(i = 0; i < NUMBER_OF_STRINGS; i++){
        if(strcmp(strings[i],stringName) == 0)
            return i;
    }

    return NUMBER_OF_STRINGS + 1;
}

void asmGenerator(char *filename, TAC* code){
  TAC *tac =code;
  FILE *fout;

  if(!(fout = fopen(filename, "w")))
  {
    fprintf(stderr,"cant open output file to write asm!!!!\n");
    exit(5);
  }

  //print all values in HASH TABLE
  fprintf(fout,".data\n");
  int str_count = 0;
  int i;
  HASH_NODE *n;
  for (i=0; i< HASH_SIZE; i++)
  {
     for (n=table[i]; n; n=n->next)
     {
          if(n->type == SYMBOL_TEMP_VAR)
            fprintf(fout,".comm %s,4,4\n",n->text);
          if(n->type == SYMBOL_LIT_STRING){
            fprintf(fout,"\nlit_string%d:\n"
                          "\t.string %s\n\n", str_count, n->text);
            strcpy(strings[str_count], n->text);
            str_count++;
          }
     }
  }

  //print TACs
  str_count = 0;
  for (tac=code; tac ; tac=tac->next){
    switch(tac->type){
      case TAC_VARDEC: fprintf(fout,"\n.globl	%s\n"
                                    ".align 4\n"
                                    ".type	%s, @object\n"
                                    ".size	%s, 4\n"
                                    "%s:\n"
                                    "\t.long	%s\n", tac->res->text, tac->res->text, tac->res->text, tac->res->text, tac->op1->text);
                    break;

      case TAC_ADD: if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\nmovl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"\nmovl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "addl %%edx, %%eax\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
      case TAC_ASS: if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\nmovl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"\nmovl	%s(%%rip), %%eax\n"
                                      "movl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
                    break;
      case TAC_OUTPUT:
                    fprintf(fout,"\nmovl	$lit_string%d, %%edi\n"
                              	 "\tcall	puts\n", findString(tac->res->text));
                    break;
      case TAC_BEGINFUN: fprintf(fout,"\n.text\n"
      	                              ".globl	%s\n"
      	                              ".type	%s, @function\n"
                                      "%s:\n"
      	                              "\npushq %%rbp\n"
      	                              "movq	%%rsp, %%rbp\n", tac->res->text, tac->res->text, tac->res->text);
                    break;
      case TAC_ENDFUN:fprintf(fout,"\nmovl	$0, %%eax\n"
    	                             "popq	%%rbp\n"
    	                             "ret\n");
                    break;
    }
  }

  fclose(fout);
}
