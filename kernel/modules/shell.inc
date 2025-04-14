global read_command

; ---------------------------------------------
; Shell input function
; Read command input, store in command_buf
; - Maximum length: 30 characters
; - Supports backspace
; - Ends when Enter key is pressed
; ---------------------------------------------
read_command:
    xor cx, cx
    mov di, command_buf

.command_loop:
    ; Wait for keyboard input
    mov ah, 0x00
    int 0x16

    ; Check Enter key (Enter = 13)
    cmp al, 13
    je .command_done

    ; Check Backspace key (Backspace = 8)
    cmp al, 8
    jne .check_printable

    cmp cx, 0
    je .command_loop                           ; If buffer is empty, ignore backspace

    ; Delete last character
    dec di
    dec cx
    mov ah, 0x0E
    mov al, 8
    int 0x10                                   ; Output backspace
    mov al, ' '
    int 0x10                                   ; Overwrite character
    mov al, 8
    int 0x10                                   ; Move cursor back
    jmp .command_loop

.check_printable:
    ; Limit to maximum length
    cmp cx, MAX_COMMAND_LEN
    jae .command_loop

    ; Echo character
    mov ah, 0x0E
    int 0x10

    ; Store character
    stosb
    inc cx
    jmp .command_loop

.command_done:
    ; Add null terminator
    mov al, 0
    stosb
    ret
