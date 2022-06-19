%include "io.inc"

section .text
F:
    push ebp
    mov ebp, esp
    sub esp, 4
    GET_DEC 4, eax
    mov dword[esp], eax
    test eax, eax
    jz .end
    call F
    mov ecx, dword[esp]
    PRINT_DEC 4, ecx
    NEWLINE
.end:
    mov esp, ebp
    pop ebp
    ret
global CMAIN
CMAIN:
    call F
    xor eax, eax
    ret