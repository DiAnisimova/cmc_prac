%include "io.inc"

CEXTERN scanf
CEXTERN printf
CEXTERN memset
CEXTERN strncmp

section .rodata
    fmt1 db "%d",0
    fmt2 db "%10s", 0
    
section .bss
    s resd 5500
    n resd 1
section .text
F:
    push ebp
    mov ebp, esp
    mov eax, dword[esp + 8]
    mov ecx, dword[esp + 12]
    test ecx, ecx
    jz .l1
    xor edx, edx
    push edi
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 32
.l:
    mov dword[esp], eax
    lea edi, [s + 8 * edx]
    lea edi, [edi + 2 * edx]
    lea edi, [edi + edx]
    mov dword[esp + 4], edi
    mov dword[esp + 8], 11
    mov dword[esp + 12], eax
    mov dword[esp + 16], ecx
    mov dword[esp + 20], edx
    call strncmp
    test eax, eax
    jz .l0
    mov edx, dword[esp + 20]
    mov ecx, dword[esp + 16]
    mov eax, dword[esp + 12]
    inc edx
    cmp edx, ecx
    jne .l
    mov esp, ebp
    pop ebp
    pop edi
.l1:
    mov eax, 1
    jmp .ex
.l0:
    mov eax, 0
    mov esp, ebp
    pop ebp
    pop edi
.ex:
    mov esp, ebp
    pop ebp
    ret
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    
    sub esp, 16
    mov dword[esp], fmt1
    mov dword[esp + 4], n
    call scanf
    
    xor ecx, ecx
    xor esi, esi
.L:
    mov dword[esp], fmt2
    mov eax, 11
    mul ecx
    add eax, s
    mov dword[esp + 4], eax
    mov dword[esp + 8],ecx
    call scanf
    mov eax, dword[esp + 4]
    mov ecx, dword[esp + 8]
    mov dword[esp], eax
    mov dword[esp + 4], ecx
    call F
    mov ecx, dword[esp + 4]
    add ecx, eax
    test eax, eax
    jnz .not
    mov eax, dword[esp]
    mov dword[esp], eax
    mov dword[esp + 4], 0
    mov dword[esp + 8], 11
    mov dword[esp + 12], ecx
    call memset
    mov ecx, dword[esp + 12]
.not:
    inc esi
    cmp esi, dword[n]
    jne .L
    mov dword[esp + 4], ecx
    mov dword[esp], fmt1
    call printf
    
    mov esp, ebp
    xor eax, eax
    ret