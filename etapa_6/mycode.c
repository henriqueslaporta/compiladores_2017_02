#include <stdio.h>

/*COMO PEGAR O CODIGO ASSEMBLY:
  gcc -S -c mycode.c

  COMO RODAR O CODIGO ASSEMBLY:
  gcc mycode.s -o mycode
  ./mycode
*/
int a = 0;
int b = 0;

int main(){
  printf("Hello World\n");
  a = 1;
  b = a + 1;
}
