	.file	"function.c"
	.text
	.globl	funcao
	.type	funcao, @function
funcao:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.LFE0:
	.size	funcao, .-funcao
	.globl	main
	.type	main, @function
main:
.LFB1:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret

