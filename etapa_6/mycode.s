	.file	"mycode.c"
	.comm	a,4,4
	.comm	b,4,4
	.section	.rodata
.LC0:
	.string	"Hello World"
.LC3:
	.string	"\n%f"
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
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, a(%rip)
	movss	a(%rip), %xmm1
	movss	.LC2(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, b(%rip)
	movss	b(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	$.LC3, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC1:
	.long	1065353216
	.align 4
.LC2:
	.long	1069547520
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
