global command_shutdown

command_shutdown:
    ; Privilege check
    mov si, username_buf
    call is_root_user
    jnz .access_denied

    ; Shutdown sequence initiation
    NEWLINE 2
    ECHO cmd_shutdown_msg
    NEWLINE

    ; Graceful delay
    ; Purpose: Ensure message visibility
    mov cx, 0x000F                             ; CX:DX = 1,000,000μs (1s)
    mov dx, 0x4240                             ; BIOS WAIT (INT 15h/AH=86h)
    mov ah, 0x86
    int 0x15                                   ; Microsecond delay

    ; Execute shutdown
    ; APM 1.0+ BIOS shutdown protocol
    mov ax, 0x5307                             ; Function number: set power state
    mov bx, 0x0001                             ; Device ID: all devices
    mov cx, 0x0003                             ; Status code: shutdown
    int 0x15                                   ; Call BIOS interrupt
    ret

; Failure fallback
.access_denied:
    NEWLINE 2
    ECHO permission_denied                     ; "Permission denied..."
    NEWLINE
    ret
