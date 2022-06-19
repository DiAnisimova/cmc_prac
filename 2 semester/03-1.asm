%include "io.inc"

section .bss
    a resd 1
    b resd 1
    c resd 1
    d resd 1
    
section .text
divisor:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp + 8]
    mov ebx, dword[ebp + 12]
.loop:
    xor edx, edx
    div ebx
    mov eax, ebx
    mov ebx, edx
    test ebx, ebx
    jnz .loop
    mov esp, ebp
    pop ebp
    ret
global CMAIN
CMAIN:
    GET_UDEC 4, a
    GET_UDEC 4, b
    GET_UDEC 4, c
    GET_UDEC 4, d
    push dword[a]
    push dword[b]
    call divisor
    add esp, 8
    mov dword[a], eax
    push dword[c]
    push dword[d]
    call divisor
    add esp, 8
    mov dword[c], eax
    push dword[a]
    push dword[c]
    call divisor
    add esp, 8
    PRINT_UDEC 4, eax
    xor eax, eax
    ret

    
    