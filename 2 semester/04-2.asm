%include "io.inc"

CEXTERN scanf
CEXTERN strncmp
CEXTERN printf
CEXTERN strlen

section .rodata
    fmt db "%1000s", 0
    s12 db "1 2", 0
    s21 db "2 1", 0
    s0 db "0", 0

section .bss
    str1 resb 1001
    str2 resb 1001

section .text
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 32
    mov dword[esp], fmt
    mov dword[esp + 4], str1
    call scanf
    mov dword[esp + 4], str2
    call scanf
    
    mov dword[esp], str1
    call strlen
    mov edx, eax      ; edx - длина первой строки
    mov dword[esp + 4], edx
    mov dword[esp], str2
    call strlen
    mov esi, eax      ; esi - длина второй строки
    mov edx, dword[esp + 4]
    cmp edx, esi
    jge .L21
    sub esi, edx
    xor ecx, ecx
.l12:   
    mov dword[esp + 8], edx  ;ищем первую строку во второй
    mov dword[esp], str1 
    mov ebx, str2
    add ebx, ecx
    mov dword[esp + 4], ebx
    mov dword[esp + 12], ecx
    mov dword[esp + 16], edx
    call strncmp
    mov edx, dword[esp + 16]
    mov ecx, dword[esp + 12]
    test eax, eax
    jz .first_in_second
    inc ecx
    cmp ecx, esi
    jle .l12
    jmp .no
.L21:    
    sub edx, esi     ;ищем вторую строку в первой
    xor ecx, ecx
.l21: 
    mov dword[esp + 8], esi
    mov dword[esp], str2
    mov ebx, str1
    add ebx, ecx
    mov dword[esp + 4], ebx
    mov dword[esp + 12], ecx
    mov dword[esp + 16], edx
    call strncmp
    mov edx, dword[esp + 16]
    mov ecx, dword[esp + 12]
    test eax, eax
    jz .second_in_first
    inc ecx
    cmp ecx, edx
    jle .l21
    jmp .no
.no:    
    mov dword[esp], s0
    call printf
    jmp .end
    
.first_in_second:
    mov dword[esp], s12
    call printf
    jmp .end
.second_in_first:
    mov dword[esp], s21
    call printf
.end:
    mov esp, ebp
    xor eax, eax
    ret