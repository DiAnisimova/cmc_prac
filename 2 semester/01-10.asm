%include "io.inc"

section .bss
month resw 1
day resw 1

section .text
global CMAIN
CMAIN:
    GET_DEC 2, month
    GET_DEC 2, day
    sub word[month], 1
    mov ax, word[month];
    shr ax, 1; в ax - количество месяцев, состоящих из 42 дней - k1
    mov bx, word[month]
    sub bx, ax
    mov cx, 42
    mul cx; ax = k1 * 42
    add word[day], ax
    mov ax, bx; в ax - количество месяцев, состоящих из 41 дня - k2
    mov cx, 41
    mul cx; ax = k2 * 41
    add word[day], ax
    PRINT_DEC 2, day
    xor eax, eax
    ret