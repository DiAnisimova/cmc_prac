%include "io.inc"

section .bss
    n resd 1
    x resd 1
    y resd 1
    s_num resd 1
    s_den resd 1
    
section .text
divisor:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp + 8]
    mov ebx, dword[ebp + 12]
.loop:
    xor edx, edx
    div ebx
    mov eax, ebx
    mov ebx, edx
    test ebx, ebx
    jnz .loop
    mov esp, ebp
    pop ebp
    ret
global CMAIN
CMAIN:
    GET_UDEC 4, n
    mov ecx,dword[n]
    dec ecx
    GET_UDEC 4, s_num
    GET_UDEC 4, s_den
    test ecx, ecx
    jz .end
.Loop:
    GET_UDEC 4, x
    GET_UDEC 4, y
    mov eax, dword[s_den]; новый знаменатель
    mov ebx, dword[y]
    mul ebx
    mov edi, eax
    
    mov eax, dword[s_num]; новый числитель
    mov ebx, dword[y]
    mul ebx
    mov esi, eax
    mov eax, dword[x]
    mov ebx, dword[s_den]
    mul ebx
    add eax, esi
    
    mov dword[s_num], eax
    mov dword[s_den], edi
    push eax
    push edi
    call divisor
    add esp, 8
    mov ebx, eax
    mov eax, dword[s_num]
    xor edx, edx
    div ebx
    mov dword[s_num], eax
    mov eax, dword[s_den]
    xor edx, edx
    div ebx
    mov dword[s_den], eax
    dec ecx
    test ecx, ecx
    jnz .Loop
.end:
    PRINT_UDEC 4, s_num
    PRINT_CHAR ' '
    PRINT_UDEC 4, s_den
    xor eax, eax
    ret