%include "io.inc"

section .bss
x1 resd 1
x2 resd 1
x3 resd 1
y1 resd 1
y2 resd 1
y3 resd 1
s2 resd 1
section .text
global CMAIN
CMAIN:
    GET_DEC 4, x1
    GET_DEC 4, y1
    GET_DEC 4, x2
    GET_DEC 4, y2
    GET_DEC 4, x3
    GET_DEC 4, y3
    mov eax, dword[x1]
    sub eax, dword[x3]
    mov ebx, dword[y2]
    sub ebx, dword[y3]
    imul ebx; в eax - кусок площади (возможно, отрицательный)
    mov dword[s2], eax
    mov eax, dword[x2]
    sub eax, dword[x3]
    mov ebx, dword[y1]
    sub ebx, dword[y3]
    imul ebx; в eax - кусок площади (возможно, отрицательный)
    sub dword[s2], eax; в s2 может лежать отр.число
    mov eax, dword[s2]
    mov ecx, eax
    mov ebx, eax; ecx - чистовик,в ebx кладем старший бит куска, в eax инвертируем площадь
    shr ebx, 31
    neg eax
    imul ebx
    add ecx, eax
    add ecx, eax
    mov eax, ecx
    mov ecx, 2
    cdq
    idiv ecx
    PRINT_DEC 4, eax
    PRINT_CHAR '.'
    mov ecx, edx; в edx может лежать отр.число
    mov ebx, edx
    mov eax, ecx; ecx - чистовик,в ebx кладем старший бит куска, в eax инвертируем площадь
    shr ebx, 31
    neg eax
    imul ebx
    add ecx, eax
    add ecx, eax
    mov eax, ecx
    mov ecx, 5
    mul ecx
    PRINT_DEC 1, al
    xor eax, eax
    ret