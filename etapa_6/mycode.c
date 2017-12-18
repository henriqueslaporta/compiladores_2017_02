#include <stdio.h>

/*COMO PEGAR O CODIGO ASSEMBLY:
  gcc -S -c mycode.c

  COMO RODAR O CODIGO ASSEMBLY:
  gcc mycode.s -o mycode
  ./mycode
*/
int a = 55;
int b = 3;

int main(){
	if(a == b){
		b = 2;
	}
}
