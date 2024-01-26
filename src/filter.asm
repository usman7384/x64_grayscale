;   rdi  => height argument
;   rsi  => width argument
;   rdx  => rgb_Array argument
global rgb_to_greyscale

section .data
r DD 0.299
g DD 0.587
b DD 0.114

section .text
rgb_to_greyscale:
    ; Function prologue
    push rbp
    mov rbp, rsp

    ; Save registers that will be used inside the loop
    push rbx
    push r8
    push r9

;   ====================            ====================
    mov rax, rdx    ; rgb_Array argument (rax instead of rdx) => moving third argument to rax
    xor rcx, rcx    ; set counter to zero

    movss xmm0, dword [r]   ; xmm0: r
    movss xmm1, dword [g]   ; xmm1: g
    movss xmm2, dword [b]   ; xmm2: b
;   ====================            ====================

    mov r8, rdi
    imul r8, rsi    ; save total pixels to r8 for comparison

loop:
    cmp rcx, r8
    jl process_pixel
    
    jmp exit  ; If rcx >= totalPixels, exit the loop

process_pixel:
    xor r9, r9
    mov r9, rcx
    imul r9, 3      ; current offset

    movzx r10, byte [rax + r9]        ; Red value
    movzx r11, byte [rax + r9 + 1]    ; Green value
    movzx r12, byte [rax + r9 + 2]    ; Blue value

    ; Convert RGB values to floating-point
    cvtsi2ss xmm3, r10  
    cvtsi2ss xmm4, r11  
    cvtsi2ss xmm5, r12  

    ; Applying the conversion formula
    mulss xmm3, xmm0   
    mulss xmm4, xmm1   
    mulss xmm5, xmm2   

    addss xmm3, xmm4   
    addss xmm3, xmm5   

    cvttss2si r13, xmm3 ; r13: Grayscale value as an integer

    mov byte [rax + r9], r13b
    mov byte [rax + r9 + 1], r13b
    mov byte [rax + r9 + 2], r13b

    inc rcx
    jmp loop

exit:
    ; Function epilog
    pop r9
    pop r8
    pop rbx

    pop rbp
    ret

