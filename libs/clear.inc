global clear

; Subroutine: Clears screen via BIOS video mode reset (INT 10h, AH=00h)
; Input: None
; Clobbers: AX
clear:
    mov ah, 0x00        ; Set video mode function
    mov al, 0x03        ; 80x25 text mode (16-color)
    int 0x10            ; Video BIOS interrupt
    ret
