%include "io.inc"

section .bss
    a resd 1
    b resd 1

section .text
global CMAIN
CMAIN:
    GET_UDEC 4, a
    GET_UDEC 4, b
    xor ebx, ebx
.loop:
    mov eax, dword[a]
    mov ebx, dword[b]
    xor edx, edx
    div ebx
    mov dword[a], ebx
    mov dword[b], edx
    and edx, 0xFFFFFFFF
    jnz .loop
    PRINT_DEC 4, ebx
    xor eax, eax
    ret