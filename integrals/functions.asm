;%include "io.inc"

section .bss
t resq 1

section .data
c1 dq 0.5
c2 dq 3.0
c3 dq 2.5
c4 dq 9.5
c5 dq 5.0
c6 dq -1.5
c7 dq 5.0
c8 dq 10.0
c9 dq 8.0
c10 dq 2.0

section .text
global f1
f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld1
    faddp
    fld qword[c1]
    fdivrp
    fld1
    faddp
    fld qword[c2]
    fmulp
    pop ebp
    ret
    
global f2
f2:
    push ebp
    mov ebp, esp
    finit 
    fld qword[esp + 8]
    fld qword[c3]
    fmulp
    fld qword[c4]
    fsubp
    pop ebp
    ret
    
global f3
f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[c5]
    fld qword[esp + 8]
    fdivp
    pop ebp
    ret
    
global df1
df1:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld1
    faddp
    fst qword[t]
    fld qword[t]
    fmulp
    fld qword[c6]
    fdivrp
    pop ebp
    ret
    
global df2
df2:
    push ebp
    mov ebp, esp
    finit
    fld qword[c3]
    pop ebp
    ret
    
global df3
df3:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fst qword[t]
    fld qword[t]
    fmulp
    fld qword[c7]
    fdivrp
    fchs
    pop ebp
    ret
    
global f4
f4:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fldln2
    fxch
    fyl2x
    fld qword[c8]
    fmulp
    pop ebp
    ret
    
global f5
f5:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld qword[esp + 8]
    fld qword[esp + 8]
    fmulp
    fmulp
    fchs
    pop ebp
    ret
    
global f6
f6:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld qword[c9]
    faddp
    fsqrt
    fld1
    fdivrp
    fchs
    pop ebp
    ret
    
global df4
df4:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld qword[c8]
    fdivrp
    pop ebp
    ret
    
global df5
df5:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld qword[esp + 8]
    fmulp
    fld qword[c2]
    fmulp
    fchs
    pop ebp
    ret
    
global df6
df6:
    push ebp
    mov ebp, esp
    finit
    fld qword[esp + 8]
    fld qword[esp + 8]
    fld qword[esp + 8]
    fmulp
    fmulp
    fsqrt
    fld qword[c10]
    fmulp
    fld1
    fdivrp
    pop ebp
    ret

    
