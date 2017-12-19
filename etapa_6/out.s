.data

.comm	mat,40,32

.text
.globl	main
.type	main, @function
main:

pushq %rbp
movq	%rsp, %rbp

## cmd VEC ASS
movl	$1, mat+40(%rip)

movl	$0, %eax
popq	%rbp
ret
