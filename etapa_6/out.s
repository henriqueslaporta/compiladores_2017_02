.data
.comm __temp6,4,4

lit_string0:
	.string "\n( a >= 10 ) SIM"

.comm __temp9,4,4
.comm __temp10,4,4

lit_string1:
	.string "\nAssinalndo vetor mat[0] = 33"

.comm __temp14,4,4
.comm __temp18,4,4

lit_string2:
	.string "\nIniciando WHILE 0 até 5"

.comm __temp1,4,4

lit_string3:
	.string "\n(soma a + 10) a = 12"

.comm __temp4,4,4

lit_string4:
	.string "\nFIM WHILE\n"

.comm __temp11,4,4
.comm __temp15,4,4
.comm __temp19,4,4
.comm __temp7,4,4

lit_string5:
	.string "\nRetorno da FUNC2() é igual (a)?"


lit_string6:
	.string "\nVariavel a = %d, a+1=%d, a/2=%d, a-3=%d, a*4=%d"

.comm __temp12,4,4
.comm __temp16,4,4
.comm __temp2,4,4

lit_string7:
	.string "\nSim!"

.comm __temp5,4,4

lit_string8:
	.string "\n( a <= 10 ) SIM"


lit_string9:
	.string "\n(divide a / 2) a = 10"

.comm __temp8,4,4
.comm __temp13,4,4
.comm __temp17,4,4

lit_string10:
	.string "\nRotina interna While"


lit_string11:
	.string "\nSIM mat[0] = 33\n"

.comm __temp0,4,4

lit_string12:
	.string "\n(multiplica a * 2) a = 20"

.comm __temp3,4,4

lit_string13:
	.string "\n(subtrai a - 2) a = 10"


.comm	mat,40,32

.globl	a
.align 4
.type	a, @object
.size	a, 4
a:
	.long	2

.text
.globl	func2
.type	func2, @function
func2:

pushq %rbp
movq	%rsp, %rbp

## cmd RETURN
movl	a(%rip), %eax
popq	%rbp
ret

.text
.globl	main
.type	main, @function
main:

pushq %rbp
movq	%rsp, %rbp

## PRINT ARG
movl	a(%rip), %esi

## cmd ADD
movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp0(%rip)

## PRINT ARG
movl	__temp0(%rip), %r8d

## cmd DIV

movl a(%rip), %eax
movl	$2, %ecx
cltd
idivl	%ecx
movl %eax, __temp1(%rip)

## PRINT ARG
movl	__temp1(%rip), %r9d

## cmd SUB
movl a(%rip), %edx
movl	$3, %eax
subl %eax, %edx
movl %edx, __temp2(%rip)

## PRINT ARG
movl	__temp2(%rip), %edi

## cmd MUL
movl a(%rip), %edx
movl	$4, %eax
imull %edx, %eax
movl %eax, __temp3(%rip)

## PRINT ARG
movl	__temp3(%rip), %eax

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string6, %edi
	call	printf

## cmd ADD
movl a(%rip), %edx
movl	$10, %eax
addl %edx, %eax
movl %eax, __temp4(%rip)

## cmd ASS
movl	__temp4(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$12, %eax
cmpl %eax, %edx
jne .__label0

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string3, %edi
	call	printf

.__label0:

## cmd SUB
movl a(%rip), %edx
movl	$2, %eax
subl %eax, %edx
movl %edx, __temp6(%rip)

## cmd ASS
movl	__temp6(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jne .__label1

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string13, %edi
	call	printf

.__label1:

## cmd MUL
movl a(%rip), %edx
movl	$2, %eax
imull %edx, %eax
movl %eax, __temp8(%rip)

## cmd ASS
movl	__temp8(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$20, %eax
cmpl %eax, %edx
jne .__label2

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string12, %edi
	call	printf

.__label2:

## cmd DIV

movl a(%rip), %eax
movl	$2, %ecx
cltd
idivl	%ecx
movl %eax, __temp10(%rip)

## cmd ASS
movl	__temp10(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jne .__label3

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string9, %edi
	call	printf

.__label3:

## LE
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jg .__label4

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string8, %edi
	call	printf

.__label4:

## GE
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jl .__label5

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string0, %edi
	call	printf

.__label5:

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string5, %edi
	call	printf

## call FUN
movl	$0, %eax
call func2
movl %eax, __temp14(%rip)

## EQ
movl __temp14(%rip), %edx
movl a(%rip), %eax
cmpl %eax, %edx
jne .__label6

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string7, %edi
	call	printf

.__label6:

## cmd ASS
movl	$0, a(%rip)

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string2, %edi
	call	printf

.__label7:

## LESS
movl a(%rip), %edx
movl	$5, %eax
cmpl %eax, %edx
jge .__label8

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string10, %edi
	call	printf

## cmd ADD
movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp17(%rip)

## cmd ASS
movl	__temp17(%rip), %eax
movl %eax, a(%rip)
jmp .__label7

.__label8:

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string4, %edi
	call	printf

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string1, %edi
	call	printf

## cmd VEC ASS
movl	$33, mat+0(%rip)

## cmd VECREAD
movl	mat+0(%rip), %eax
movl	%eax, __temp18(%rip)

## EQ
movl __temp18(%rip), %edx
movl	$33, %eax
cmpl %eax, %edx
jne .__label9

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string11, %edi
	call	printf

.__label9:
popq	%rbp
ret
