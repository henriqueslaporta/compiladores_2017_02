	.file	"mycode.c"
	.comm	a,80,32
	.globl	b
	.data
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	3
	.text
	.globl	func
	.type	func, @function
func:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, b(%rip)
	movl	-8(%rbp), %eax
	movl	%eax, b(%rip)
	movl	-12(%rbp), %eax
	movl	%eax, b(%rip)
	movl	-16(%rbp), %eax
	movl	%eax, b(%rip)
	movl	-20(%rbp), %eax
	movl	%eax, b(%rip)
	movl	-24(%rbp), %eax
	movl	%eax, b(%rip)
	movl	16(%rbp), %eax
	movl	%eax, b(%rip)
	movl	24(%rbp), %eax
	movl	%eax, b(%rip)
	movl	$3, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	func, .-func
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	$4
	pushq	$3
	movl	$2, %r9d
	movl	$3, %r8d
	movl	$4, %ecx
	movl	$3, %edx
	movl	$2, %esi
	movl	$3, %edi
	call	func
	addq	$16, %rsp
	movl	%eax, b(%rip)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
