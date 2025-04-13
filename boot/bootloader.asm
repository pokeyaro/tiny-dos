BITS 16
ORG 0x7C00

_start:
    ; print 'helloworld' as startup flag
    mov si, msg
.print:
    lodsb
    cmp al, 0
    je halt
    mov ah, 0x0E
    int 0x10
    jmp .print

halt:
    cli
    hlt

msg db 13, 10, "HELLO, WORLD!", 0

times 510 - ($ - $$) db 0
dw 0xAA55