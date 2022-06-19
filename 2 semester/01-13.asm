%include "io.inc"

section .bss
xv resb 1
xh resb 1
yv resb 1
yh resb 1
sum resb 1

section .text
global CMAIN
CMAIN:
    GET_CHAR xv
    GET_CHAR xh
    GET_CHAR yv
    GET_CHAR yv
    GET_CHAR yh
    mov al, byte[xv]
    mov bl, byte[yv]
    sub bl, al; в bl может лежать отр.число, берем модуль
    
    mov al, bl
    mov cl, bl
    shr cl, 7
    neg al
    imul cl
    add bl, al
    add bl, al
    
    mov byte[sum], bl
    mov al, byte[xh]
    mov bl, byte[yh]
    sub bl, al; в bl может лежать отр.число, берем модуль
    
    mov al, bl
    mov cl, bl
    shr cl, 7
    neg al
    imul cl
    add bl, al
    add bl, al
    
    add byte[sum], bl
    PRINT_DEC 1, sum
    xor eax, eax
    ret