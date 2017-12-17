#include <stdio.h>

/*COMO PEGAR O CODIGO ASSEMBLY:
  gcc -S -c mycode.c

  COMO RODAR O CODIGO ASSEMBLY:
  gcc mycode.s -o mycode
  ./mycode
*/
float a;
float b;

int main(){
  printf("Hello World");
  a = 1;
  b = a + 1.5;
  printf("\n%f", b);
  return 0;
}
