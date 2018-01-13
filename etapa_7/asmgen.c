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

  //string to print integers
  fprintf(fout,"\ninteger_string:\n"
                "\t.string \" %%d\"\n\n");

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
	  case TAC_VECDEC: fprintf(fout,"\n.comm	%s,%d,32\n", tac->res->text, atoi(tac->op1->text) * 4);
                    break;

      case TAC_ADD: fprintf(fout,"\n## cmd ADD\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "addl %%edx, %%eax\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_SUB: fprintf(fout,"\n## cmd SUB\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "subl %%eax, %%edx\n"
                                  "movl %%edx, %s(%%rip)\n", tac->res->text);
                    break;
      case TAC_MUL: fprintf(fout,"\n## cmd MUL\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                    else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
                    fprintf(fout, "imull %%edx, %%eax\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_DIV: fprintf(fout,"\n## cmd DIV\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"\nmovl	$%s, %%eax\n",tac->op1->text);
                    else fprintf(fout,"\nmovl %s(%%rip), %%eax\n", tac->op1->text);
                    if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%ecx\n",tac->op2->text);
                    else fprintf(fout, "movl %s(%%rip), %%ecx\n", tac->op2->text);
                    fprintf(fout, "cltd\n"
								  "idivl	%%ecx\n"
                                  "movl %%eax, %s(%%rip)\n", tac->res->text);
                    break;
	  case TAC_EQ:fprintf(fout,"\n## EQ\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jne");
				  break;
	  case TAC_LESS:fprintf(fout,"\n## LESS\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jge");
				  break;
	  case TAC_GREAT:fprintf(fout,"\n## GREAT\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jle");
				  break;
	  case TAC_LE:fprintf(fout,"\n## LE\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jg");
				  break;
      case TAC_GE:fprintf(fout,"\n## GE\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"jl");
				  break;
	  case TAC_NE:fprintf(fout,"\n## NE\n");
				  if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%edx\n",tac->op1->text);
                  else fprintf(fout,"movl %s(%%rip), %%edx\n", tac->op1->text);
                  if(tac->op2->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n",tac->op2->text);
                  else fprintf(fout, "movl %s(%%rip), %%eax\n", tac->op2->text);
				  fprintf(fout, "cmpl %%eax, %%edx\n"
								"je");
				  break;
	  case TAC_JZ: fprintf(fout, " .%s\n", tac->res->text); //Sendo utilizado apenas para escrever o label
				  break;
	  case TAC_JMP: fprintf(fout, "jmp .%s\n", tac->res->text);
				  break;
	  case TAC_LABEL: fprintf(fout, "\n.%s:\n", tac->res->text);
				  break;
	  case TAC_ASS: fprintf(fout,"\n## cmd ASS\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %s(%%rip)\n",tac->op1->text, tac->res->text);
                    else fprintf(fout,"movl	%s(%%rip), %%eax\n"
                                      "movl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
                    break;
	  case TAC_VECWRITE: fprintf(fout,"\n## cmd VEC ASS\n");
					if(tac->op1->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %s+%d(%%rip)\n",tac->op1->text, tac->res->text, atoi(tac->op2->text) * 4);
                    else fprintf(fout,"movl	%s(%%rip), %%eax\n"
                                      "movl	%%eax, %s+20(%%rip)\n", tac->op1->text, tac->res->text);
                    break;
	  case TAC_VECREAD: fprintf(fout,"\n## cmd VECREAD\n");
						fprintf(fout,"movl	%s+%d(%%rip), %%eax\n"
									 "movl	%%eax, %s(%%rip)\n", tac->op1->text, atoi(tac->op2->text) * 4, tac->res->text );
                    break;
	  case TAC_CALL: fprintf(fout,"\n## call FUN\n"
								  "movl	$0, %%eax\n"
								  "call %s\n"
								  "movl %%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
					break;
      case TAC_OUTPUT:fprintf(fout,"\n## cmd PRINT\n");
                    if(tac->res->type == SYMBOL_LIT_STRING){
                        fprintf(fout,"movl	$lit_string%d, %%edi\n"
                                	   "\tcall	printf\n", findString(tac->res->text));
                    }
                    else{
                        if(tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%esi\n", tac->res->text);
                        else fprintf(fout, "movl	%s(%%rip), %%esi\n", tac->res->text);
                        fprintf(fout, "movl $integer_string, %%edi\n\tcall printf\n");
                      }
                    break;
      case TAC_BEGINFUN: fprintf(fout,"\n.text\n"
      	                              ".globl	%s\n"
      	                              ".type	%s, @function\n"
                                      "%s:\n"
      	                              "\npushq %%rbp\n"
      	                              "movq	%%rsp, %%rbp\n", tac->res->text, tac->res->text, tac->res->text);
                    break;
      case TAC_ENDFUN:fprintf(fout,  "popq	%%rbp\n"
    	                             "ret\n");
                    break;
	  case TAC_RETURN:fprintf(fout,"\n## cmd RETURN\n");
					if(tac->res->type == SYMBOL_LIT_INT) fprintf(fout,"movl	$%s, %%eax\n", tac->res->text);
                    else fprintf(fout,"movl	%s(%%rip), %%eax\n", tac->res->text);
					break;
    }
  }

  fclose(fout);
}
