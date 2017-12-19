#include <stdio.h>

/*COMO PEGAR O CODIGO ASSEMBLY:
  gcc -S -c mycode.c

  COMO RODAR O CODIGO ASSEMBLY:
  gcc mycode.s -o mycode
  ./mycode
*/
int a[20];
int b = 3;

int func(){
	return 3;
}

int main(){
	b = func();
}
