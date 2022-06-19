%include "io.inc"

CEXTERN malloc
CEXTERN free
CEXTERN fscanf
CEXTERN fprintf
CEXTERN fopen
CEXTERN fclose

section .rodata
    file1 db "input.txt", 0
    file2 db "output.txt", 0
    fmt1 db "r", 0
    fmt2 db "w", 0
    fmt3 db "%d", 0
    fmt4 db "%d ", 0
    
section .bss
    list resd 1
    n resd 1
    input resd 1
    output resd 1
    x resd 1
    prev resd 1
            
section .text
global CMAIN
CMAIN:
    mov ebp, esp
    and esp, 0xfffffff0
    
    sub esp, 32
    mov dword[esp], file1
    mov dword[esp + 4], fmt1
    call fopen
    mov dword[input], eax
    
    xor ecx, ecx
    
.read:
    mov eax, dword[input]
    mov dword[esp], eax
    mov dword[esp + 4], fmt3
    mov dword[esp + 8], x
    mov dword[esp + 12], ecx
    mov dword[esp + 16], edx
    call fscanf
    mov edx, dword[esp + 16]
    mov ecx, dword[esp + 12]
    cmp eax, 0
    jl .after_read
    mov dword[esp], 8
    mov dword[esp + 4], ecx
    mov dword[esp + 8], edx
    call malloc 
    mov edx, dword[esp + 8]
    mov ecx, dword[esp + 4]
    test ecx, ecx
    jz .list
    mov dword[edx], eax
    jmp .not_list
.list:
    mov dword[list], eax
.not_list:
    mov esi, dword[x]
    mov dword[eax], esi
    lea edx, [eax + 4]
    inc ecx
    jmp .read
.after_read:
    mov dword[n], ecx
    
    
    xor edx, edx   
    cmp dword[n], 1
    je .after_sort
.Sort:
    xor ecx, ecx
    mov ebx, dword[list]
.sort:          ; ebx - адрес текущего элемента
    mov eax, ebx
    mov esi, dword[eax + 4];esi - адрес следующего элемента
    mov eax, dword[eax]
    mov esi, dword[esi]
    cmp eax, esi
    jle .not_change
    mov eax, ebx
    mov esi, dword[eax + 4]
    mov edi, esi
    mov edi, dword[edi + 4]
    mov dword[ebx + 4], edi
    mov dword[esi + 4], ebx
    test ecx, ecx
    je .head
    mov eax, dword[prev]
    mov dword[eax + 4], esi
    jmp .after_change
.head:
    mov dword[list], esi
.after_change:
    mov dword[prev], esi
    jmp .skip
.not_change:
    mov dword[prev], ebx
    mov ebx, dword[ebx + 4]
.skip:
    inc ecx
    mov eax,dword[n]
    sub eax, edx
    dec eax
    cmp ecx, eax
    jne .sort  
    inc edx
    mov eax, dword[n]
    dec eax
    cmp edx, eax
    jne .Sort
.after_sort:
    mov eax, dword[input]
    mov dword[esp], eax
    call fclose
    
    mov dword[esp], file2
    mov dword[esp + 4], fmt2
    call fopen
    mov dword[output], eax
    
    mov ebx, dword[list]
    xor ecx, ecx
.print:
    mov eax, dword[output]
    mov dword[esp], eax
    mov eax, dword[ebx]
    
    mov dword[esp + 4], fmt4
    mov dword[esp + 8], eax
    mov dword[esp + 12], ecx
    call fprintf
    mov ecx, dword[esp + 12]
    mov eax, ebx
    mov ebx, dword[ebx + 4]
    mov dword[esp], eax
    mov dword[esp + 4], ecx
    call free
    mov ecx, dword[esp + 4]
    inc ecx
    cmp ecx, dword[n]
    jne .print
    
    mov eax, dword[output]
    mov dword[esp], eax
    call fclose
    
    mov esp, ebp
    xor eax, eax
    ret