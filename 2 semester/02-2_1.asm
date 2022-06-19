%include "io.inc"

section .bss
    n resd 1

section .text
global CMAIN
CMAIN:
    GET_UDEC 4, n
    xor ebx, ebx
    mov eax, dword[n]
    test eax, eax
    jz .fin
.loop:
    mov ecx, 1
    and ecx, eax
    add bl, cl
    shr eax, 1
    test eax, eax
    jnz .loop
.fin:
    PRINT_DEC 1, bl   
    xor eax, eax
    ret