.data
.comm __temp6,4,4

lit_string0:
	.string "Assinalndo vetor mat[0] = 33"

.comm __temp9,4,4
.comm __temp10,4,4

lit_string1:
	.string "FIM WHILE\n"

.comm __temp14,4,4

lit_string2:
	.string "\nIniciando WHILE 0 até 5"


lit_string3:
	.string "Variavel a = 2"


lit_string4:
	.string "( a <= 10 ) SIM"

.comm __temp1,4,4

lit_string5:
	.string "(subtrai a - 2) a = 10"


lit_string6:
	.string "(soma a + 10) a = 12"


lit_string7:
	.string "(multiplica a * 2) a = 20"

.comm __temp4,4,4

lit_string8:
	.string "SIM mat[0] = 33"

.comm __temp11,4,4
.comm __temp15,4,4
.comm __temp7,4,4

lit_string9:
	.string "( a >= 10 ) SIM"


lit_string10:
	.string "\nRetorno da FUNC2() é igual (a)?"


lit_string11:
	.string "(divide a / 2) a = 10"

.comm __temp12,4,4
.comm __temp16,4,4
.comm __temp2,4,4
.comm __temp5,4,4

lit_string12:
	.string "Rotina interna While"

.comm __temp8,4,4

lit_string13:
	.string "Sim!"

.comm __temp13,4,4
.comm __temp0,4,4
.comm __temp3,4,4

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

## EQ
movl a(%rip), %edx
movl	$2, %eax
cmpl %eax, %edx
jne .__label0

## cmd PRINT
movl	$lit_string3, %edi
	call	puts

.__label0:

## cmd ADD
movl a(%rip), %edx
movl	$10, %eax
addl %edx, %eax
movl %eax, __temp1(%rip)

## cmd ASS
movl	__temp1(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$12, %eax
cmpl %eax, %edx
jne .__label1

## cmd PRINT
movl	$lit_string6, %edi
	call	puts

.__label1:

## cmd SUB
movl a(%rip), %edx
movl	$2, %eax
subl %eax, %edx
movl %edx, __temp3(%rip)

## cmd ASS
movl	__temp3(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jne .__label2

## cmd PRINT
movl	$lit_string5, %edi
	call	puts

.__label2:

## cmd MUL
movl a(%rip), %edx
movl	$2, %eax
imull %edx, %eax
movl %eax, __temp5(%rip)

## cmd ASS
movl	__temp5(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$20, %eax
cmpl %eax, %edx
jne .__label3

## cmd PRINT
movl	$lit_string7, %edi
	call	puts

.__label3:

## cmd DIV

movl a(%rip), %eax
movl	$2, %ecx
cltd
idivl	%ecx
movl %eax, __temp7(%rip)

## cmd ASS
movl	__temp7(%rip), %eax
movl %eax, a(%rip)

## EQ
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jne .__label4

## cmd PRINT
movl	$lit_string11, %edi
	call	puts

.__label4:

## LE
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jg .__label5

## cmd PRINT
movl	$lit_string4, %edi
	call	puts

.__label5:

## GE
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jl .__label6

## cmd PRINT
movl	$lit_string9, %edi
	call	puts

.__label6:

## cmd PRINT
movl	$lit_string10, %edi
	call	puts

## call FUN
movl	$0, %eax
call func2
movl %eax, __temp11(%rip)

## EQ
movl __temp11(%rip), %edx
movl a(%rip), %eax
cmpl %eax, %edx
jne .__label7

## cmd PRINT
movl	$lit_string13, %edi
	call	puts

.__label7:

## cmd ASS
movl	$0, a(%rip)

## cmd PRINT
movl	$lit_string2, %edi
	call	puts

.__label8:

## LESS
movl a(%rip), %edx
movl	$5, %eax
cmpl %eax, %edx
jge .__label9

## cmd PRINT
movl	$lit_string12, %edi
	call	puts

## cmd ADD
movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp14(%rip)

## cmd ASS
movl	__temp14(%rip), %eax
movl %eax, a(%rip)
jmp .__label8

.__label9:

## cmd PRINT
movl	$lit_string1, %edi
	call	puts

## cmd PRINT
movl	$lit_string0, %edi
	call	puts

## cmd VEC ASS
movl	$33, mat+0(%rip)

## cmd VECREAD
movl	mat+0(%rip), %eax
movl	%eax, __temp15(%rip)

## EQ
movl __temp15(%rip), %edx
movl	$33, %eax
cmpl %eax, %edx
jne .__label10

## cmd PRINT
movl	$lit_string8, %edi
	call	puts

.__label10:
popq	%rbp
ret
