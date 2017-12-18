.data
.comm __temp1,4,4

lit_string0:
	.string "fora"

.comm __temp0,4,4

lit_string1:
	.string "dentro"


.globl	a
.align 4
.type	a, @object
.size	a, 4
a:
	.long	2

.globl	b
.align 4
.type	b, @object
.size	b, 4
b:
	.long	3

.text
.globl	main
.type	main, @function
main:

pushq %rbp
movq	%rsp, %rbp

## cmd SUB
movl	$2, %edx
movl	$2, %eax
subl %eax, %edx
movl %edx, __temp0(%rip)

## cmd IF
movl __temp0(%rip), %edx
movl	$0, %eax
cmpl %eax, %edx

jne .__label0

movl	$lit_string1, %edi
	call	puts

.__label0:

movl	$lit_string0, %edi
	call	puts

movl	$0, %eax
popq	%rbp
ret
