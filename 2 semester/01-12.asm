%include "io.inc"

section .bss
p resb 1
k1 resb 1
k2 resb 1

section .text
global CMAIN
CMAIN:
    GET_DEC 1, p
    mov al, byte[p]
    cbw
    mov bl, 4
    div 4
    xor eax, eax
    ret