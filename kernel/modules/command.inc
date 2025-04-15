global handle_command

; ---------------------------------------------
; COMMAND DISPATCHER
; Purpose: Route shell commands to appropriate handlers
; Features:
;   - Supports 3 built-in commands
;   - Handles quoted arguments
;   - Provides unknown command feedback
; Design:
;   - Linear command matching (optimized for BIOS)
;   - Clear error messaging
; ---------------------------------------------
handle_command:

; ─────────────────────────────────────────────
; INPUT VALIDATION
; ─────────────────────────────────────────────
.check_empty:
    mov si, command_buf
    cmp byte [si], 0
    je .done

; ─────────────────────────────────────────────
; COMMAND MATCHING
; ─────────────────────────────────────────────
; 'help' command
.check_cmd_help:
    cmp byte [si], 'h'
    jne .check_cmd_?
    inc si
    cmp byte [si], 'e'
    jne .check_cmd_?
    inc si
    cmp byte [si], 'l'
    jne .check_cmd_?
    inc si
    cmp byte [si], 'p'
    jne .check_cmd_?
    inc si
    cmp byte [si], 0
    jne .check_cmd_?
    call command_help
    ret

; '?' command
.check_cmd_?:
    mov si, command_buf
    cmp byte [si], '?'
    jne .check_cmd_cls
    inc si
    cmp byte [si], 0
    jne .check_cmd_cls
    call command_help
    ret

; 'cls' command
.check_cmd_cls:
    mov si, command_buf
    cmp byte [si], 'c'
    jne .check_cmd_date
    inc si
    cmp byte [si], 'l'
    jne .check_cmd_date
    inc si
    cmp byte [si], 's'
    jne .check_cmd_date
    inc si
    cmp byte [si], 0
    jne .check_cmd_date
    call command_cls
    ret

; 'date' command
.check_cmd_date:
    mov si, command_buf
    cmp byte [si], 'd'
    jne .unknown
    inc si
    cmp byte [si], 'a'
    jne .unknown
    inc si
    cmp byte [si], 't'
    jne .unknown
    inc si
    cmp byte [si], 'e'
    jne .unknown
    inc si
    cmp byte [si], 0
    jne .unknown
    call command_date
    ret

; ─────────────────────────────────────────────
; ERROR HANDLING
; ─────────────────────────────────────────────
.unknown:
    NEWLINE 2
    ECHO cmd_unknown_prefix                    ; "Unknown command: "

    ; Format error message with quotes
    mov al, "'"
    call print_char                            ; Opening quote
    mov si, command_buf
    call print                                 ; User's input
    mov al, "'"
    call print_char                            ; Closing quote
    NEWLINE

.done:
    ret