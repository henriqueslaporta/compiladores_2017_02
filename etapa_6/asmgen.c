#include <stdlib.h>

void asmGenerator(char *filename, TAC* code){
  TAC *tac =code;
  FILE *out;

  if(!(fout = fopen(filename, "w")))
  {
    fprintf(stderr,"cant open output file to write asm!!!!\n");
    exit(5);
  }


  for (tac=code; tac ; tac=tac->next){
    swich(tac->type){
      case TAC_ADD; fprintf(fout,"");break;
      case TAC_ASS; fprintf(fout,"");break;
      case TAC_PRINT; fprintf(fout,"");break;
      case TAC_BEGINF; fprintf(fout,"_%s\n"
                                    "\tpushq\n"
                                    "\tmoveq\n"
                                    "\tsubq\t$16, %%rsp\n", tac->res->text);break;
      case TAC_ENDF; fprintf(fout,"\n"
                                  "\t\n"
                                  "\t\n"
                                  "\t\n");break;
    }
  }

  fclose(fout);
}
