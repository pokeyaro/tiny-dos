global print, print_char

; Subroutine: Prints null-terminated string via BIOS
; Input: SI = string address
; Clobbers: AL, SI (AH now handled internally by print_char)
print:
    pusha
.loop:
    lodsb               ; AL = [SI], SI++
    test al, al         ; Check for null terminator
    jz .done
    call print_char     ; Reuse character printing logic
    jmp .loop
.done:
    popa
    ret

; Subroutine: Prints single character via BIOS (INT 10h, AH=0Eh)
; Input: AL = ASCII character
; Clobbers: AH
print_char:
    mov ah, 0x0E        ; BIOS teletype output
    int 0x10            ; Video interrupt
    ret
