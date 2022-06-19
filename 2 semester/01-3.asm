%include "io.inc"

section .bss
a resd 1
b resd 1
c resd 1
d resd 1
e resd 1
f resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, a
    GET_DEC 4, b
    GET_DEC 4, c
    GET_DEC 4, d
    GET_DEC 4, e
    GET_DEC 4, f
    mov ecx, dword[e]
    add ecx, dword[f]
    mov eax, ecx
    mul dword[a] 
    mov ebx, eax
    
    mov ecx, dword[d]
    add ecx, dword[f]
    mov eax, ecx
    mul dword[b] 
    add ebx, eax
    
    mov ecx, dword[e]
    add ecx, dword[d]
    mov eax, ecx
    mul dword[c] 
    add ebx, eax
    PRINT_DEC 4, ebx
    xor eax, eax
    ret