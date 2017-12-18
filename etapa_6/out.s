
lit_"Hello World padrao":
	.string "Hello World padrao"
.comm __temp0,4,4

movl	$"Hello World padrao", %edi
	call	puts

movl	1(%rip), a(%rip)

movl a(%rip), %edx
movl 1(%rip), %eax
addl %edx, %eax
movl %eax, __temp0(%rip)

movl	__temp0(%rip), b(%rip)
