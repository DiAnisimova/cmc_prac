%include "io.inc"

CEXTERN scanf
CEXTERN printf
section .bss
    num resd 1
section .rodata
    fmt1 db "%u", 0
    fmt2 db '0x%08X', 10, 0
    fmt3 db "%b", 0
section .text
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 16
.L:
    mov dword[esp], fmt1
    mov dword[esp + 4], num
    call scanf
    cmp eax, 0
    js .end
    mov dword[esp], fmt2
    mov eax, dword[num]
    mov dword[esp + 4], eax
    call printf
    jmp .L
.end:
    mov esp, ebp
    xor eax, eax
    ret