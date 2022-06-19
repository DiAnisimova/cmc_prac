%include "io.inc"

section .bss
    n resd 1
    k resd 1
    sum resd 1

section .text
F: 
    push ebp
    mov ebp, esp
    mov eax, dword[ebp + 8]
    mov ebx, dword[k]
    xor ecx, ecx
.loop:
    xor edx, edx
    div ebx
    add ecx, edx
    test eax, eax
    jnz .loop
    mov eax, ecx
    mov esp, ebp
    pop ebp
    ret
    
global CMAIN
CMAIN:
    GET_UDEC 4, n
    GET_UDEC 4, k
    mov eax, dword[n]
    add dword[sum], eax
.L:    
    push eax
    call F
    add esp, 4
    add dword[sum], eax
    cmp eax, dword[n]
    je .end
    mov dword[n], eax
    jmp .L
.end:
    PRINT_UDEC 4, sum
    xor eax, eax
    ret