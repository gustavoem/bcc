# Torres de Hanoi
	
	## Segmento de dados
	.data

# msg é a string impressa para indicar cada movimento
# esta string será editada "in loco".
# Como exemplo, para indicar um movimento de 1 para 3
# a string será "1 -> 3\n"
msg:				# Início da mensagem
from_pin:	.byte	1	# primeiro pino
	.ascii	" -> "
to_pin:	        .byte	1, 10   # segundo pino, \n
	.equ len, . - msg

	## Segmento de código
	.text

# parte recursiva:
#  rhanoi(n,source,dest)
#   move n discos de source para dest
rhanoi:	
	
# algumas constantes, que indicam a posição dos parâmetros e
# variáveis na pilha
	.equ	n,	 8 
	.equ	source,	12 
	.equ	dst,	16 
	.equ	other,	-4 


	## Montagem do frame
	pushl	%ebp		# frame anterior
	movl    %esp, %ebp	# novo frame
	subl	$4,   %esp	# um inteiro local

	movl    n(%ebp),%eax
	cmpl	$0, %eax
	jle	pronto

	cmpl    $1, %eax
	je	transfere              

	## descobre o pino que sobrou (other = 6 - source - dest)
	movl    $6,%eax
	subl    source(%ebp),%eax
	subl	dst(%ebp),   %eax
	movl	%eax, other(%ebp)

	movl	n(%ebp), %eax
	decl    %eax		# eax = n-1
	push	%eax

	## chama recursivamente (n-1 discos de source para other)
	pushl   other(%ebp)
	pushl   source(%ebp)

	pushl   %eax		# vamos usar n-1 novamente mais tarde
	
	call    rhanoi
	addl	$12,%esp

	## 1 disco de source para dest
	pushl   dst(%ebp)
	pushl   source(%ebp)
	pushl   $1
	call    rhanoi
	addl	$12,%esp

	## n-1 discos de other para dest
	pop	%eax		# n-1 em %eax

	pushl   dst(%ebp)
	pushl   other(%ebp)
	pushl   %eax
	call    rhanoi
	addl	$12,%esp

	jmp     pronto

	## imprime a mensagem
transfere:
	pushl    dst(%ebp)
	pushl    source(%ebp)
	call     putmsg

pronto:
	## desmonta o frame e retorna
	movl	 %ebp, %esp
	popl     %ebp
	ret


.globl	_start
_start:
	# move 6 discos de 1 para 2
	pushl	$2
	pushl	$1
	pushl	$6

	call    rhanoi
	addl	$12,%esp

        movl    $1,%eax         # system call number (sys_exit) 
        xorl    %ebx,%ebx       # first syscall argument: exit code
        int     $0x80           # call kernel


	## constantes para indexar os argumentos
	.equ     src,   8
	.equ     dest, 12

putmsg:
	## montagem do frame
	pushl	%ebp
	movl    %esp, %ebp

	## edição da string msg (mexe diretamente nos bytes
	## de interesse)
	movl	src(%ebp), %eax
	addb    $'0', %al
	movb    %al, (from_pin)
	movl	dest(%ebp), %eax
	addb    $'0', %al
	mov	%al, to_pin

	## imprime
        movl    $4,%eax         # (sys_write)
        movl    $1,%ebx         # (stdout)
        movl    $msg,%ecx       # (msg)
        movl    $len,%edx       # (tamanho)
        int     $0x80           # call kernel

	movl	%ebp, %esp
	popl	%ebp     
	ret

