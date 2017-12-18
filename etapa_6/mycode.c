#include <stdio.h>

/*COMO PEGAR O CODIGO ASSEMBLY:
  gcc -S -c mycode.c

  COMO RODAR O CODIGO ASSEMBLY:
  gcc mycode.s -o mycode
  ./mycode
*/
int a = 0;
int b;
int c;

int main(){
  printf("Hello World\n");
  a = 1;
  b= 1;
  c = a + b;
  printf("\n%d", c);
  return 0;
}
