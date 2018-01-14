.data
//-------------VAR_DEC sem inicializacao-----------------
.comm	a,4,4
.comm	b,4,4
//-------------------------------------------------------

//-------------VAR_DEC com inicializacao-----------------
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
.long	2
//------------------------------------------------------
.text
.globl	main
.type	main, @function

//---------------------BEGIN MAIN-----------------------
main:
	pushq	%rbp
	movq	%rsp, %rbp

//---------------------TAC_PRINT------------------------
string:
  .string	"String"
  movl	$string, %edi
	call	puts


//---------------------TAC_ASS (a = 1)------------------
  //se a->int
  movl	$1, a(%rip)

  //se a->real
  literal_1:
  	.long	1065353216
  movss	literal_1(%rip), %xmm0
  movss	%xmm0, a(%rip)


//-----------------TAC_ADD (b = a + 1))-----------------
  //para a->int
  movl	a(%rip), %eax
  addl	$1, %eax

  //se b->int
  movl	%eax, b(%rip)

  //se b->real
  pxor	%xmm0, %xmm0
	cvtsi2ss	%eax, %xmm0
	movss	%xmm0, b(%rip)

  //para a->float e b->float
  literal_1:
  	.long	1065353216
  movss	a(%rip), %xmm1
	movss	literal_1(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, b(%rip)
//------------------------------------------------------

	movl	$0, %eax
	popq	%rbp
	ret
