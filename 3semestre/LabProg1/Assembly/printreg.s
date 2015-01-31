	.data
## saida
mreg:	.string "EwX:"
vreg:	.fill 8,1,' '
	.string "\n"


	.global _start

_start:
	movl	$0x1234541A, %eax	# exemplo
	movb	$'A',  (mreg+1)

	movl	%eax, %ebx
	andb	$0x0f, %al			#4 ultimos bits
	addb	$'0', %al			#converte para hexa
	cmpb	$'9', %al
	jle	Ok1
	addb	$('A'-'9'-1), %al

Ok1:
	movb	%al, (vreg+7)
	movb	%bl, %al
	shrb	$4, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok2
	addb	$('A'-'9'-1), %al

Ok2:
	movb	%al, (vreg+6)

	movb	%bh, %al
	andb	$0x0f, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok3
	addb	$('A'-'9'-1), %al

Ok3:
	movb	%al, (vreg+5)
	movb	%bh, %al
	shrb	$4, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok4
	addb	$('A'-'9'-1), %al

Ok4:
	movb	%al, (vreg+4)

	shrl	$16, %ebx
	movl	%ebx, %eax

	andb	$0x0f, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok5
	addb	$('A'-'9'-1), %al

Ok5:
	movb	%al, (vreg+3)
	movb	%bl, %al
	shrb	$4, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok6
	addb	$('A'-'9'-1), %al

Ok6:
	movb	%al, (vreg+2)
	movb	%bh, %al
	andb	$0x0f, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok7
	addb	$('A'-'9'-1), %al

Ok7:
	movb	%al, (vreg+1)
	movb	%bh, %al
	shrb	$4, %al
	addb	$'0', %al
	cmpb	$'9', %al
	jle	Ok8
	addb	$('A'-'9'-1), %al

Ok8:
	movb	%al, vreg
	mov     $4,%eax
    mov     $1,%ebx
	mov     $mreg,%ecx
	mov     $14,%edx
	int     $0x80

    mov     $1,%eax
	xor     %ebx,%ebx
    int     $0x80



