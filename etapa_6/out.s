.data
.comm __temp1,4,4
.comm __temp0,4,4

lit_string0:
	.string "dentro"


.comm	mat,40,32

.globl	a
.align 4
.type	a, @object
.size	a, 4
a:
	.long	3

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

## call FUN
movl	$0, %eax
call func2
movl %eax, __temp0(%rip)

## EQ
movl __temp0(%rip), %edx
movl	$3, %eax
cmpl %eax, %edx
jne .__label0

## cmd PRINT
movl	$lit_string0, %edi
	call	puts

.__label0:
popq	%rbp
ret
