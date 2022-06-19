%include "io.inc"

section .bss
a11 resd 1
a12 resd 1
a21 resd 1
a22 resd 1
b1 resd 1
b2 resd 1
M1 resd 1
M2 resd 1
M3 resd 1
M4 resd 1
M5 resd 1
M6 resd 1
x resd 1
y resd 1
det resd 1
det1 resd 1

section .text
global CMAIN
CMAIN:
    ;x_i= det_i&det ^ !det & ((a_1i & b1 | a_2i & b2) ^ (a_11 & a12 & b1 | a_21 & a_22 & b2)&(i & 1))
    ;x_i = M1 ^ M2, M2 = !det & (M3  ^ M4).                M5              M6             
    ;
    GET_UDEC 4, a11
    GET_UDEC 4, a12
    GET_UDEC 4, a21
    GET_UDEC 4, a22
    GET_UDEC 4, b1
    GET_UDEC 4, b2
    
    mov eax, dword[a11]; det
    mov ebx, dword[a22]
    and eax, ebx
    mov ebx, dword[a12]
    mov ecx, dword[a21]
    and ebx, ecx
    xor eax, ebx
    mov dword[det], eax
    
    mov eax, dword[b1]; det1 - для x
    mov ebx, dword[a22]
    and eax, ebx
    mov ebx, dword[a12]
    mov ecx, dword[b2]
    and ebx, ecx
    xor eax, ebx
    mov dword[det1], eax
    
    mov ebx, dword[det]; M1
    and eax, ebx
    mov dword[M1], eax
    
    mov eax, dword[a11]; M3
    mov ebx, dword[b1]
    and eax, ebx
    mov ebx, dword[a21]
    mov ecx, dword[b2]
    and ebx, ecx
    or eax, ebx
    mov dword[M3], eax
    
    mov eax, dword[a11]; M5
    mov ebx, dword[a12]
    and eax, ebx
    mov ebx, dword[b1]
    and eax, ebx
    mov dword[M5], eax
    
    mov eax, dword[a21]; M6
    mov ebx, dword[a22]
    and eax, ebx
    mov ebx, dword[b2]
    and eax, ebx
    mov dword[M6], eax
    
    mov ebx, dword[M5]; M4
    or eax, ebx
    mov dword[M4], eax
    
    mov ebx, dword[M3]
    xor eax, ebx
    mov ebx, dword[det]
    not ebx
    and eax, ebx
    mov dword[M2], eax
    
    mov ebx, dword[M1]
    xor eax, ebx
    mov dword[x], eax
    
    
    mov eax, dword[a11]; det1 - для y
    mov ebx, dword[b2]
    and eax, ebx
    mov ebx, dword[b1]
    mov ecx, dword[a21]
    and ebx, ecx
    xor eax, ebx
    mov dword[det1], eax
    
    mov ebx, dword[det];M1
    and eax, ebx
    mov dword[M1], eax
    
    mov eax, dword[a12]; M3
    mov ebx, dword[b1]
    and eax, ebx
    mov ebx, dword[a22]
    mov ecx, dword[b2]
    and ebx, ecx
    or eax, ebx
    mov dword[M3], eax
    
    mov ebx, dword[det];M2
    not ebx
    and eax, ebx
    mov dword[M2], eax
    
    
    mov ebx, dword[M1]
    xor eax, ebx
    mov dword[y], eax
    
    PRINT_UDEC 4, x
    NEWLINE
    PRINT_UDEC 4, y
    
    xor eax, eax
    ret