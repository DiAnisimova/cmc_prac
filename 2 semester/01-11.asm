%include "io.inc"

section .bss
    h_odd resb 1
    h_even resb 1
    v_odd resb 1
    v_even resb 1
    h resb 1
    v resb 1
    sum resb 1

section .text
global CMAIN
CMAIN:
    GET_CHAR v
    GET_CHAR h
    mov al, byte[v]
    sub al, 'A'
    mov bl, 7
    sub bl, al
    mov al, bl
    mov bl, 2
    xor ah, ah
    div bl
    mov byte[v_even], al
    add al, ah
    mov byte[v_odd], al
    
    mov al, byte[h]
    sub al, '1'
    mov bl, 7
    sub bl, al
    mov al, bl
    mov bl, 2
    xor ah, ah
    div bl
    mov byte[h_even], al
    add al, ah
    mov byte[h_odd], al
    
    mov al, byte[v_even]
    mov bl, byte[h_odd]
    mul bl
    mov byte[sum], al
    
    mov al, byte[h_even]
    mov bl, byte[v_odd]
    mul bl
    add byte[sum], al
    PRINT_DEC 1, sum
    xor eax, eax
    ret