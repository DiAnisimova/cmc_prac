%include "io.inc"

CEXTERN fprintf
CEXTERN scanf
CEXTERN malloc
CEXTERN free

section .rodata
    fmt1 db "%d", 0
    fmt2 db "%d",10, 0
section .bss
    arr resd 1 ; тут будет лежать указатель на массив
    length resd 1
    
section .text
apply:
    push ebp
    mov ebp, esp
        
    xor ecx, ecx
.L:    
    mov eax, dword[esp + 8]
    lea eax, [eax + 4 * ecx]   
    mov eax, dword[eax]
    
    mov ebx, dword[esp + 20]; n
    add ebx, 4
    shl ebx, 2
    sub esp, ebx
    mov edi, esp
    and esp, 0xfffffff0
    xor esi, esi
    sub ebx, 4
    mov dword[esp + ebx], eax
    sub ebx, 4
    mov dword[esp + ebx], ecx
    
.l:
    mov edx, dword[ebp + 24 + 4*esi]
    mov dword[esp + 4 * esi], edx
    inc esi
    cmp esi, dword[ebp + 20]
    
    jne .l
    mov dword[esp + 4 * esi], eax
    
    mov eax, dword[ebp + 16]
    call eax   
    
    mov ecx, dword[esp + ebx]
    add ebx, 4
    mov eax, dword[esp + ebx] 
    add ebx, 4
    
    mov esp, edi
    add esp, ebx   
    
    inc ecx
    cmp ecx, dword[esp + 12]
    jne .L
    
    
    mov esp, ebp
    pop ebp
    ret
   
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    sub esp, 32
    
    
    mov dword[esp], fmt1
    mov dword[esp + 4], length
    call scanf
    
    mov eax, dword[length]
    shl eax, 2
    mov dword[esp], eax
    call malloc
    mov dword[arr], eax
    
    xor ecx, ecx
.scanf:
    mov dword[esp], fmt1
    mov eax, dword[arr]
    lea eax, [eax + 4 * ecx]
    mov dword[esp + 4], eax
    mov dword[esp + 8], ecx
    call scanf

    mov ecx, dword[esp + 8]
    inc ecx
    cmp ecx, dword[length]
    jne .scanf
    
    mov dword[esp + 4], ecx
    call get_stdout
    mov ecx, dword[esp + 4]
    
    mov edx, dword[arr]
    mov dword[esp], edx
    mov edx, dword[length]
    mov dword[esp + 4], edx
    mov dword[esp + 8], fprintf
    mov dword[esp + 12], 2

    mov dword[esp + 16], eax
    mov dword[esp + 20], fmt2

    call apply
    
    mov edx, dword[arr]
    mov dword[esp], edx
    call free
    
    mov esp, ebp
    xor eax, eax
    ret