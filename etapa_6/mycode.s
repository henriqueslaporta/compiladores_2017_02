	.file	"mycode.c"
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
	.comm	d,4,4
	.comm	e,4,4
	.comm	f,4,4
	.comm	g,4,4
	.comm	h,4,4
	.comm	i,4,4
	.comm	j,4,4
	.comm	k,4,4
	.comm	l,4,4
	.comm	m,4,4
	.comm	n,4,4
	.comm	o,4,4
	.comm	p,4,4
	.comm	q,4,4
	.comm	r,4,4
	.comm	s,4,4
	.comm	t,4,4
	.comm	w,4,4
	.comm	u,4,4
	.comm	v,4,4
	.comm	x,4,4
	.comm	y,4,4
	.comm	z,4,4
	.section	.rodata
.LC0:
	.string	"string normal"
	.align 8
.LC1:
	.string	"a = %d \nb = %d \nc = %d \nd = %d \ne = %d \nf = %d \ng = %d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, a(%rip)
	movl	$2, b(%rip)
	movl	$3, c(%rip)
	movl	$4, d(%rip)
	movl	$5, e(%rip)
	movl	$.LC0, %edi
	call	puts
	movl	g(%rip), %edi
	movl	f(%rip), %esi
	movl	e(%rip), %r9d
	movl	d(%rip), %r8d
	movl	c(%rip), %ecx
	movl	b(%rip), %edx
	movl	a(%rip), %eax
	pushq	%rdi
	pushq	%rsi
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addq	$16, %rsp
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
