%include "io.inc"

CEXTERN fscanf
CEXTERN fprintf
CEXTERN fopen
CEXTERN fclose

section .rodata
    fmt1 db "%d ", 0
    file1 db "input.txt"
    file2 db "output.txt"
    fmt2 db "r", 0
    fmt3 db "w", 0
    
section .bss
    n resd 1
    m resd 1
    a resd 100000
    next resd 100000
    prev resd 100000
    fil1 resd 1
    fil2 resd 1
    b resd 1
    c resd 1
    
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    and esp, 0xfffffff0
    
    sub esp, 16
    mov dword[esp], file1
    mov dword[esp + 4], fmt2
    call fopen
    mov dword[fil1], eax
    
    mov dword[esp], eax
    mov dword[esp + 4], fmt1
    mov dword[esp + 8], n
    call fscanf
    
    xor ecx, ecx
.L0:
    lea eax, [a + 4 * ecx]
    inc ecx
    mov dword[eax], ecx
    
    lea eax, [a + 4 * ecx]
    dec ecx
    lea ebx, [next + 4 * ecx]
    mov dword[ebx], eax
    
    lea ebx, [prev + 4 * ecx]
    dec ecx
    lea eax, [a + 4 * ecx]
    mov dword[ebx], eax
    inc ecx
    
    inc ecx
    cmp ecx, dword[n]
    jne .L0
    dec ecx
    lea ebx, [next + 4 * ecx]
    mov dword[ebx], a
    lea ebx, [a + 4 * ecx]
    mov dword[prev], ebx
    
    mov dword[esp], fil1
    mov dword[esp + 4], fmt1
    mov dword[esp + 8], m
    call fscanf
    
    mov ecx, dword[m]
.L1:
    mov dword[esp], fil1
    mov dword[esp + 4], fmt1
    mov dword[esp + 8], b
    call fscanf
    
    mov dword[esp], fil1
    mov dword[esp + 4], fmt1
    mov dword[esp + 8], c
    call fscanf
    
    push ecx
    push dword[c]
    push dword[b]
    call F
    add esp, 8
    pop ecx
    
    dec ecx
    test ecx, ecx
    jnz .L1
    
    mov eax, dword[fil1]
    mov dword[esp], eax
    call fclose
    
    mov dword[esp], file2
    mov dword[esp + 4], fmt3
    call fopen
    mov dword[fil2], eax
    
    xor ecx, ecx
.L2:
    lea eax, [a + ecx * 4]
    mov eax, dword[eax]
    mov dword[esp], file2
    mov dword[esp + 4], fmt1
    mov dword[esp + 8], eax
    mov dword[esp + 12], ecx
    call fprintf
    mov ecx, dword[esp + 12]
    inc ecx
    cmp ecx, dword[n]
    jne .L2
    
    mov eax, dword[fil2]
    mov dword[esp], eax
    call fclose
    
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret