# Echo em assembly de 32 bits
# -----------------------------------------------------------------------------
# A 32-bit program that displays its commandline arguments, one per line.
#
# -----------------------------------------------------------------------------

        .global main

        .text
main:
		## Protocolo de entrada na função -> frame
		pushl	%ebp
		movl	%esp, %ebp
		
		## Situação da pilha:
		##      %ebp antigo ($esp-4)
		##      end. de retorno (%ebp +4)
		## 	    argc (%ebp +8)
		## 		argv (%ebp +12)

		
		movl	12(%ebp), %eax	# primeiro argv

while:
		push	%eax			# salva o eax
		pushl	(%eax)			# *argv
        call    puts			# print it
//		pop		%eax			# limpa o argumento
		addl	$4, %esp		# outra forma
		pop		%eax			# pega o eax de volta
		
        add     $4, %eax		# próximo argumento
		
        decl    8(%ebp)			# contador
		
		cmpl	$0, 8(%ebp)
        jnz     while
		
		xorl	%eax, %eax		# código de retorno 0

		## Protocolo de saída da função
		movl 	%ebp, %esp
		popl	%ebp
        ret
format:
        .asciz  "%s\n"
		