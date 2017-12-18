#include <stdio.h>

/*COMO PEGAR O CODIGO ASSEMBLY:
  gcc -S -c mycode.c

  COMO RODAR O CODIGO ASSEMBLY:
  gcc mycode.s -o mycode
  ./mycode
*/
int a = 0;
int b = 3;

int main(){
	while(a<10){
		a++;
	}
}
