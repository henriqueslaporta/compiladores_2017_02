#include "asmgen.h"

void asmGenerator(char *filename, TAC* code){
  TAC *tac =code;
  FILE *fout;

  if(!(fout = fopen(filename, "w")))
  {
    fprintf(stderr,"cant open output file to write asm!!!!\n");
    exit(5);
  }

  //print all values in HASH TABLE
  int i;
  HASH_NODE *n;
  for (i=0; i< HASH_SIZE; i++)
  {
     for (n=table[i]; n; n=n->next)
     {
         if(n->type == SYMBOL_TEMP_VAR)
          fprintf(fout,".comm %s,4,4\n",n->text);
         if(n->type == SYMBOL_LIT_STRING)
          fprintf(fout,"\nlit_%s:\n"
                        "\t.string %s\n", n->text, n->text);
     }
  }

  //print TACs
  for (tac=code; tac ; tac=tac->next){
    switch(tac->type){
      case TAC_ADD: fprintf(fout,"\nmovl %s(%%rip), %%edx\n"
                                  "movl %s(%%rip), %%eax\n"
                                  "addl %%edx, %%eax\n"
                                  "movl %%eax, %s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
                    break;
      case TAC_ASS: fprintf(fout,"\nmovl	%s(%%rip), %s(%%rip)\n", tac->op1->text, tac->res->text);
                    break;
      case TAC_OUTPUT: fprintf(fout,"\nmovl	$%s, %%edi\n"
                                  	"\tcall	puts\n", tac->res->text);
                      break;
      case TAC_BEGINFUN:/* fprintf(fout,"_%s\n"
                                    "\tpushq\n"
                                    "\tmoveq\n"
                                    "\tsubq\t$16, %%rsp\n", tac->res->text)*/;break;
      case TAC_ENDFUN:/* fprintf(fout,"\n"
                                  "\t\n"
                                  "\t\n"
                                  "\t\n");*/break;
    }
  }

  fclose(fout);
}
