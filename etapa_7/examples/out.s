.data
.comm __temp6,4,4
.comm __temp9,4,4

lit_string0:
	.string  "ERROR" 

.comm __temp1,4,4
.comm __temp4,4,4
.comm __temp7,4,4

lit_string1:
	.string "string"


lit_string2:
	.string "Parou no meio\n"

.comm __temp2,4,4
.comm __temp5,4,4
.comm __temp8,4,4

lit_string3:
	.string "\n"

.comm __temp0,4,4
.comm __temp3,4,4

lit_string4:
	.string "Incrementado algumas vezes fica "


integer_string:
	.string " %d"


.globl	a
.align 4
.type	a, @object
.size	a, 4
a:
	.long	0

.globl	i
.align 4
.type	i, @object
.size	i, 4
i:
	.long	0

.comm	v,40,32

.comm	mat,40,32

.globl	f
.align 4
.type	f, @object
.size	f, 4
f:
	.long	10.55

.globl	c
.align 4
.type	c, @object
.size	c, 4
c:
	.long	'x'

.globl	d
.align 4
.type	d, @object
.size	d, 4
d:
	.long	65

.text
.globl	main
.type	main, @function
main:

pushq %rbp
movq	%rsp, %rbp

## cmd ASS
movl	$10, a(%rip)

## cmd SUB
movl	$10, %edx
movl	$1, %eax
subl %eax, %edx
movl %edx, __temp0(%rip)

## cmd VECREAD
movl	v+0(%rip), %eax
movl	%eax, __temp1(%rip)

## cmd VEC ASS
movl	__temp1(%rip), %eax
movl	%eax, v+20(%rip)

## cmd PRINT
movl	$lit_string1, %edi
	call	printf

## cmd PRINT
movl	$lit_string0, %edi
	call	printf

.__label0:

## LESS
movl i(%rip), %edx
movl	$10, %eax
cmpl %eax, %edx
jge .__label1

## cmd ADD
movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp3(%rip)

## call FUN
movl	$0, %eax
call incn
movl %eax, __temp4(%rip)

## cmd ASS
movl	__temp4(%rip), %eax
movl %eax, a(%rip)

## cmd ADD
movl i(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, __temp5(%rip)

## cmd ASS
movl	__temp5(%rip), %eax
movl %eax, i(%rip)
jmp .__label0

.__label1:

## cmd PRINT
movl	$lit_string4, %edi
	call	printf

## cmd PRINT
movl	a(%rip), %esi
movl $integer_string, %edi
	call printf

## cmd PRINT
movl	$lit_string3, %edi
	call	printf

## EQ
movl a(%rip), %edx
movl	$5, %eax
cmpl %eax, %edx
jne .__label2

## cmd PRINT
movl	$lit_string2, %edi
	call	printf

## cmd PRINT
movl	$lit_string0, %edi
	call	printf

## cmd PRINT
movl	$lit_string0, %edi
	call	printf

## cmd PRINT
movl	$lit_string0, %edi
	call	printf

.__label2:

## EQ
movl a(%rip), %edx
movl	$11, %eax
cmpl %eax, %edx
jne .__label3

.__label3:

## EQ
movl a(%rip), %edx
movl	$11, %eax
cmpl %eax, %edx
jne .__label4

.__label4:
popq	%rbp
ret

.text
.globl	incn
.type	incn, @function
incn:

pushq %rbp
movq	%rsp, %rbp

## cmd ADD
movl x(%rip), %edx
movl n(%rip), %eax
addl %edx, %eax
movl %eax, __temp9(%rip)

## cmd RETURN
movl	__temp9(%rip), %eax
popq	%rbp
ret

.text
.globl	voidfunc
.type	voidfunc, @function
voidfunc:

pushq %rbp
movq	%rsp, %rbp
popq	%rbp
ret
