%include "io.inc"

CEXTERN scanf
CEXTERN printf
CEXTERN malloc
CEXTERN free

section .rodata
    fmt1 db "%d ", 0
    fmt2 db "%d",10, 0

section .bss
    n resd 1
    m resd 1
    cur_size resd 1
    max_size resd 1
    matr resd 1
    cur_matr resd 1
    max_tr resq 1
    cur_tr resq 1
    max_m resd 1
    
section .text
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    
    sub esp, 16
    mov dword[esp], fmt1
    mov dword[esp + 4], n
    call scanf
    
    mov dword[esp], fmt1
    mov dword[esp + 4], max_m
    call scanf
    
    mov eax, dword[max_m] ;выделяем место под матрицу
    mul eax
    mov dword[max_size], eax
    shl eax, 4
    mov dword[esp], eax
    call malloc
    mov dword[matr], eax
    
    xor ecx, ecx
.L1:
    mov ebx, dword[matr] ; считываем первую матрицу
    lea ebx, [ebx + 4 * ecx]
    mov dword[esp], fmt1
    mov dword[esp + 4], ebx
    mov dword[esp + 8], ecx
    call scanf
    mov ecx, dword[esp + 8]
    xor edi, edi
    mov eax, ecx
    xor edx, edx
    div dword[max_m]
    cmp eax, edx
    cmove edi, dword[ebx]
    mov eax, edi
    cdq
    add dword[max_tr], eax
    adc dword[max_tr + 4], edx
    inc ecx
    cmp ecx, dword[max_size]
    jb .L1
    
    mov esi, 1
.L2:
    cmp esi, dword[n]
    je .end
    mov dword[cur_tr], 0
    mov dword[cur_tr + 4], 0
        
    mov dword[esp], fmt1
    mov dword[esp + 4], m
    call scanf
    
    mov eax, dword[m] ;выделяем место под матрицу
    mul eax
    mov dword[cur_size], eax
    shl eax, 4
    mov dword[esp], eax
    call malloc
    mov dword[cur_matr], eax
    
    xor ecx, ecx
.L3:
    mov ebx, dword[cur_matr] ; считываем матрицу
    lea ebx, [ebx + 4 * ecx]
    mov dword[esp], fmt1
    mov dword[esp + 4], ebx
    mov dword[esp + 8], ecx
    call scanf
    mov ecx, dword[esp + 8]
    xor edi, edi
    mov eax, ecx
    xor edx, edx
    div dword[m]
    cmp eax, edx
    cmove edi, dword[ebx]
    mov eax, edi
    cdq
    add dword[cur_tr], eax
    adc dword[cur_tr + 4], edx
    inc ecx
    cmp ecx, dword[cur_size]
    jb .L3
    
    mov eax, dword[cur_tr + 4]
    cmp eax, dword[max_tr + 4]
    jl .less
    jg .gr
    mov eax, dword[cur_tr]
    cmp eax, dword[max_tr]
    jbe .less
.gr:
    mov eax, dword[cur_tr + 4]
    mov dword[max_tr + 4], eax
    mov eax, dword[cur_tr]
    mov dword[max_tr], eax
    mov eax, dword[matr]
    mov dword[esp], eax
    call free
    mov eax, dword[cur_matr]
    mov dword[matr], eax
    mov eax, dword[m]
    mov dword[max_m], eax
    mov eax, dword[cur_size]
    mov dword[max_size], eax
    jmp .next
.less:
    mov eax, dword[cur_matr]
    mov dword[esp], eax
    call free
.next:
    inc esi
    jmp .L2
    
.end:
    xor ecx, ecx
.L4:
    mov ebx, dword[matr]
    lea ebx, [ebx + ecx * 4]
    mov ebx, dword[ebx]
    xor edx, edx
    mov eax, ecx
    div dword[max_m]
    inc edx
    cmp edx, dword[max_m]
    je .next_str
    mov dword[esp], fmt1
    jmp .this_str
.next_str:
    mov dword[esp], fmt2
.this_str:
    mov dword[esp + 4], ebx
    mov dword[esp + 8], ecx
    call printf
    mov ecx, dword[esp + 8]
    inc ecx
    cmp ecx, dword[max_size]
    jb .L4
    
    mov eax, dword[matr]
    mov dword[esp], eax
    call free
    
    mov esp, ebp
    xor eax, eax
    ret