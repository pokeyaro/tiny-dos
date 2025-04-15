global rand_mod

; 🎲 RAND_MOD - Bounded Random Number Generator
;  Purpose: Generate uniform random number in [0, N-1]
;    - Input: DS:SI → N (byte)
;    - Output: AL
;    - Clobbers: AH, CL
;    - Preserves: BX, DI, SI, ES
rand_mod:
    push dx
    push cx

    ; Get clock ticks (random seed source)
    mov ah, 0x00
    int 0x1A        ; CX:DX = system timer ticks

    ; Load divisor N (cmd_zodiac_limit value)
    lodsb           ; AL = [SI] = 12 (modulus)
    mov cl, al      ; CL = divisor (12 zodiac animals)
    mov al, dl      ; AL = random seed (DL = LSB of ticks)

    ; Calculate DL % CL (modulo operation)
    xor ah, ah      ; AH = 0
    div cl          ; AL = AX / CL, AH = AX % CL

    ; Return remainder (0 ≤ AH < 12)
    mov al, ah      ; AL = random number (0-11)

    pop cx
    pop dx

    ret
