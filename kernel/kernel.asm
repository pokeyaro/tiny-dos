[BITS 16]
[ORG 0x0500]                    ; Kernel loads at memory address 0x0500

section .text
global _start

; --- Main Entry Point ---
_start:
    ; Clear screen (text mode 80x25)
    call cls

    ; Print welcome message
    mov si, msg
    call print

    ; Halt system (stop CPU execution)
    cli
    hlt

; --- Screen Clearing Routine ---
cls:
    mov ah, 0x00                ; BIOS video function 0x00: Set video mode
    mov al, 0x03                ; Mode 0x03: 80x25 text mode (clears screen)
    int 0x10                    ; Call BIOS video interrupt
    ret

; --- String Printing Routine ---
print:
.next_char:
    lodsb                       ; Load byte at [SI] into AL, increment SI
    cmp al, 0                   ; Check for null terminator
    je .done                    ; If null, string is complete
    mov ah, 0x0E                ; BIOS teletype function 0x0E
    int 0x10                    ; Call BIOS video interrupt
    jmp .next_char              ; Process next character
.done:
    ret

; --- Data Section ---
msg db "HELLO, WORLD!", 0       ; 'helloworld' welcome message