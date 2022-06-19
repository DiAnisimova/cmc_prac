%include "io.inc"

section .bss
    n resd 1
    sup resd 1


section .text
global CMAIN
CMAIN:
    GET_DEC 4, n
    mov ebx, dword[n]
    mov ecx, 1; найдем число, наиболее близкое к корню из n
.loop0:
    inc ecx
    mov eax, ecx
    mul ecx
    cmp eax, ebx
    jl .loop0
    mov dword[sup], ecx
    
    xor ebx, ebx
    mov ecx, 1
.loop1:
    inc ecx
    mov eax, dword[n]
    xor edx, edx
    div ecx
    and edx, 0xFFFFFFFF
    cmovz ebx, eax
    mov eax, dword[sup]
    cmp eax, ecx
    je .fin
    test ebx, ebx
    jz .loop1
.fin:
    test ebx, ebx
    mov ecx, 1
    cmovz ebx, ecx
    PRINT_DEC 4, ebx
    xor eax, eax
    ret