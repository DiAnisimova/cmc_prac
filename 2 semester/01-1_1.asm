%include "io.inc"

section .bss
    v1 resd 1
    v2 resd 1
    a1 resd 1
    a2 resd 1
    t resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, v1
    GET_DEC 4, v2
    GET_DEC 4, a1
    GET_DEC 4, a2
    GET_DEC 4, t
    mov eax, dword[t]
    imul dword[t]
    imul dword[a1]
    mov ebx, eax
    mov eax, dword[v1]
    imul dword[t]
    add eax, ebx
    PRINT_DEC 4, eax
    NEWLINE
    mov eax, dword[t]
    imul dword[t]
    imul dword[a2]
    mov ebx, eax
    mov eax, dword[v2]
    imul dword[t]
    add eax, ebx
    PRINT_DEC 4, eax
    xor eax, eax
    ret