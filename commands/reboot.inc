global command_reboot

command_reboot:
    ; Privilege check
    mov si, username_buf
    call is_root_user
    jnz .access_denied

    ; Reboot sequence initiation
    NEWLINE 2
    ECHO cmd_reboot_msg
    NEWLINE

    ; Graceful delay
    ; Purpose: Ensure message visibility
    mov cx, 0x000F                             ; CX:DX = 1,000,000μs (1s)
    mov dx, 0x4240                             ; BIOS WAIT (INT 15h/AH=86h)
    mov ah, 0x86
    int 0x15                                   ; Microsecond delay

; Hardware reset protocol
.wait_input_empty:
    in al, 0x64                                ; Read controller status
    test al, 0x02                              ; Check input buffer bit
    jnz .wait_input_empty                      ; Wait until clear

    mov al, 0xFE                               ; Pulse reset line (FEh)
    out 0x64, al                               ; Trigger hardware reset

; Failure fallback
.access_denied:
    NEWLINE 2
    ECHO permission_denied                     ; "Permission denied..."
    NEWLINE
    ret
