%include "io.inc"

section .bss
    k resd 1
    n resd 1
    a resd 1

section .text 
F:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi
    mov eax, dword[ebp+8] ;x_l
    mov esi, dword[ebp+12]; x_l+1
    
    mov ebx, dword[k]
    xor ecx, ecx
.loop1:
    inc ecx
    xor edx, edx
    div ebx
    test eax, eax
    jnz .loop1
    mov eax,1
.loop2:
    mul ebx
    dec ecx
    test ecx, ecx
    jnz .loop2
    mul esi
    add eax, dword[ebp+8]; новый x
    mov ecx, 2011
    xor edx, edx
    div ecx
    mov eax, edx

    pop edi
    pop esi
    pop ebx
    pop ebp
    ret
    
global CMAIN
CMAIN:
    GET_UDEC 4, k
    GET_UDEC 4, n
    GET_UDEC 4, a
    mov eax, dword[a]
    mov ebx, 2011
    xor edx, edx
    div ebx
    mov eax, edx; x0
    cmp dword[n], 0
    je .end
    xor  ecx, ecx
.L:
    test ecx, ecx
    cmovz edx, eax
    push ecx
    push eax
    push edx
    call F
    pop edx
    pop edx
    pop ecx
    inc ecx
    cmp ecx,dword[n]
    jne .L
.end:
    PRINT_UDEC 4, eax
    xor eax, eax
    ret