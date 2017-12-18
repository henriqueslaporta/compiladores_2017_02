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
	.long	0

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

.__label0:

## GREAT
movl a(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jle .__label1

movl	$lit_string1, %edi
	call	puts

## cmd ADD
movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp1(%rip)

## cmd ASS
movl	__temp1(%rip), %eax
movl %eax, a(%rip)
jmp .__label0

.__label1:

movl	$lit_string0, %edi
	call	puts

movl	$0, %eax
popq	%rbp
ret
