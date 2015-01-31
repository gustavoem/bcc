        .data
msg:
        .string "Hello World!\n"
msg_end:
        .equ len,msg_end-msg
        .string  "Outra string qualquer...."
tam:
        .byte    0x0e,65,66,67,'\n'
        .long   14
        .text
        .globl  _start
_start:
        movl $4, %eax
        movl $1, %ebx
//      movl $len, %edx
//      movl $msg, %ecx
        movl $tam, %ecx
        movl $5, %edx
//      movl $msg_end-msg, %edx
        int  $0x80
        
        movl $1, %eax
        xorl %ebx, %ebx
        int  $0x80

