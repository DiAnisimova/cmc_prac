%include "io.inc"

section .bss
    sum resd 1

section .text
F:
    push ebp
    mov ebp, esp
    push ebx
    xor ebx, ebx
    mov eax, dword[ebp + 8]
    xor edx, edx 
    div ecx
    mov ecx, 1
    cmp edx, 1
    cmove ebx, ecx
    mov ecx, 3
    add dword[sum], ebx
    test eax, eax
    jz .end
    push ecx
    push edx
    push eax
    call F
    pop eax
    pop edx
    pop ecx
.end:
    pop ebx
    mov esp, ebp
    pop ebp
    ret    
    
global CMAIN
CMAIN:
    mov ecx, 3
    GET_UDEC 4, eax
    push ecx
    push edx
    push eax
    call F
    pop eax
    pop edx
    pop ecx
    PRINT_UDEC 4, sum
    xor eax, eax
    ret