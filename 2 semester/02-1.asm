%include "io.inc"

section .bss
    n resd 1
    max1 resd 1
    max2 resd 1
    max3 resd 1
    x resd 1

section .text
global CMAIN
CMAIN:
    GET_DEC 4, n
    mov ecx, dword[n]
    GET_DEC 4, max1
    GET_DEC 4, max2
    GET_DEC 4, max3
    sub ecx, 3
    .CMP:
      mov eax, dword[max1]
      mov ebx, dword[max2]
      mov edx, dword[max3]
      cmp eax, ebx
      jl .L1
      cmp ebx, edx
      jl .L2
      cmp ecx, 0
      jne .CONT
      jmp .CONT1
      
    .L1:
      mov dword[max1], ebx
      mov dword[max2], eax
      jmp .CMP
    .L2:
      mov dword[max2], edx
      mov dword[max3], ebx
      jmp .CMP
    .L3:
      mov dword[max3], eax
      jmp .CMP
    .CONT:
      GET_DEC 4, x
      dec ecx
      mov eax, dword[x]
      cmp eax, dword[max3]
      jg .L3
      cmp ecx, 0
      jne .CONT
    .CONT1:
      PRINT_DEC 4, max1
      PRINT_CHAR ' '
      PRINT_DEC 4, max2
      PRINT_CHAR ' '
      PRINT_DEC 4, max3
    xor eax, eax
    ret