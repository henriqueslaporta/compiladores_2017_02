	.data
	.globl	a

	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4

	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.zero	4


.LC0:
	.string	"Hello World"

	.text
	.globl	main
	.type	main, @function
main:

	pushq	%rbp
	movq	%rsp, %rbp


	movl	$.LC0, %edi
	call	puts

	movl	$1, a(%rip)
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, b(%rip)

	movl	$0, %eax
	popq	%rbp
	ret
