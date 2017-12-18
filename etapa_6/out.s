.data

lit_string0:
	.string "Hello World padrao"

.comm __temp0,4,4

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
	.long	0

.text
.globl	main
.type	main, @function
main:

pushq %rbp
movq	%rsp, %rbp

movl	$lit_string0, %edi
	call	puts

movl	$1, a(%rip)

movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp0(%rip)

movl	__temp0(%rip), %eax
movl %eax, b(%rip)

movl	$0, %eax
popq	%rbp
ret
