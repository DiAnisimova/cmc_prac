%include "io.inc"

CEXTERN fopen
CEXTERN fscanf
CEXTERN fprintf
CEXTERN fclose
CEXTERN qsort

section .rodata
    file1 db "input.txt", 0
    file2 db "output.txt", 0
    fmt1 db "r", 0
    fmt2 db "w", 0
    fmt3 db "%d", 0
    fmt4 db "%d ", 0

section .bss
    n resd 1002

section .text
comp:
    push ebp
    mov ebp, esp
    push ebx
    mov eax, dword[ebp + 8]
    mov eax, dword[eax]
    mov ebx, dword[ebp + 12]
    mov ebx, dword[ebx]
    cmp eax, ebx
    jl .l
    jg .g
    xor eax, eax
    jmp .e
.l:
    mov eax, -1
    jmp .e
.g:
    mov eax, 1
.e:
    pop ebx
    pop ebp
    ret
    
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    
    sub esp, 32
    mov dword[esp], file1
    mov dword[esp + 4], fmt1
    call fopen    ; eax - "input.txt"

    
    xor ecx, ecx
.L1:
    mov dword[esp], eax
    mov dword[esp + 4], fmt3
    lea ebx, [n + 4 * ecx]
    mov dword[esp + 8], ebx
    mov dword[esp + 12], ecx
    call fscanf
    mov ecx, dword[esp + 12]
    cmp eax, 0
    js .aftL1
    mov eax, dword[esp]
    inc ecx  ;ecx - количество элементов массива
    jmp .L1
.aftL1:    
    mov eax, dword[esp]
    mov dword[esp], n
    mov dword[esp + 4], ecx
    mov dword[esp + 8], 4
    mov dword[esp + 12], comp
    mov dword[esp + 16], ecx
    mov dword[esp + 20], eax
    call qsort
    mov ecx, dword[esp + 16]
    mov eax, dword[esp + 20]
    
    mov dword[esp], eax
    mov dword[esp + 4], ecx
    call fclose
    mov ecx, dword[esp + 4]
    
    mov dword[esp], file2
    mov dword[esp + 4], fmt2
    mov dword[esp + 8], ecx
    call fopen    ; eax - "output.txt"
    mov ecx, dword[esp + 8]
    
    mov edx, ecx
    xor ecx, ecx
.L2:
    mov dword[esp], eax
    mov dword[esp + 4], fmt4
    lea ebx, [n + 4 * ecx]
    mov ebx, dword[ebx]
    mov dword[esp + 8], ebx
    mov dword[esp + 12], ecx
    mov dword[esp + 16], edx
    call fprintf
    mov edx, dword[esp + 16]
    mov ecx, dword[esp + 12]
    mov eax, dword[esp]
    inc ecx
    cmp ecx, edx
    jb .L2
    
    mov dword[esp], eax
    call fclose

    mov esp, ebp
    
    xor eax, eax
    ret