global handle_command

; ---------------------------------------------
; COMMAND DISPATCHER
; Purpose: Route shell commands to appropriate handlers
; Features:
;   - Supports 10+ built-in commands
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
    jne .check_cmd_arch
    inc si
    cmp byte [si], 0
    jne .check_cmd_arch
    call command_help
    ret

; 'arch' command
.check_cmd_arch:
    mov si, command_buf
    cmp byte [si], 'a'
    jne .check_cmd_cls
    inc si
    cmp byte [si], 'r'
    jne .check_cmd_cls
    inc si
    cmp byte [si], 'c'
    jne .check_cmd_cls
    inc si
    cmp byte [si], 'h'
    jne .check_cmd_cls
    inc si
    cmp byte [si], 0
    jne .check_cmd_cls
    call command_arch
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
    jne .check_cmd_echo
    inc si
    cmp byte [si], 'a'
    jne .check_cmd_echo
    inc si
    cmp byte [si], 't'
    jne .check_cmd_echo
    inc si
    cmp byte [si], 'e'
    jne .check_cmd_echo
    inc si
    cmp byte [si], 0
    jne .check_cmd_echo
    call command_date
    ret

; 'echo' command
.check_cmd_echo:
    mov si, command_buf
    cmp byte [si], 'e'
    jne .check_cmd_ipaddr
    inc si
    cmp byte [si], 'c'
    jne .check_cmd_ipaddr
    inc si
    cmp byte [si], 'h'
    jne .check_cmd_ipaddr
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_ipaddr
    inc si
    cmp byte [si], ' '                         ; Space is required!
    jne .check_cmd_ipaddr
    inc si
    cmp byte [si], '"'                         ; Must be double quotes!
    jne .check_cmd_ipaddr
    inc si
    call command_echo
    ret

; 'ipaddr' command
.check_cmd_ipaddr:
    mov si, command_buf
    cmp byte [si], 'i'
    jne .check_cmd_logout
    inc si
    cmp byte [si], 'p'
    jne .check_cmd_logout
    inc si
    cmp byte [si], ' '                         ; Space is required!
    jne .check_cmd_logout
    inc si
    cmp byte [si], 'a'
    jne .check_cmd_logout
    inc si
    cmp byte [si], 'd'
    jne .check_cmd_logout
    inc si
    cmp byte [si], 'd'
    jne .check_cmd_logout
    inc si
    cmp byte [si], 'r'
    jne .check_cmd_logout
    inc si
    call command_ipaddr
    ret

; 'logout' command
.check_cmd_logout:
    mov si, command_buf
    cmp byte [si], 'l'
    jne .check_cmd_pwd
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_pwd
    inc si
    cmp byte [si], 'g'
    jne .check_cmd_pwd
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_pwd
    inc si
    cmp byte [si], 'u'
    jne .check_cmd_pwd
    inc si
    cmp byte [si], 't'
    jne .check_cmd_pwd
    inc si
    cmp byte [si], 0
    jne .check_cmd_pwd
    call command_logout
    ret

; 'pwd' command
.check_cmd_pwd:
    mov si, command_buf
    cmp byte [si], 'p'
    jne .check_cmd_reboot
    inc si
    cmp byte [si], 'w'
    jne .check_cmd_reboot
    inc si
    cmp byte [si], 'd'
    inc si
    cmp byte [si], 0
    jne .check_cmd_reboot
    call command_pwd
    ret

; 'reboot' command
.check_cmd_reboot:
    mov si, command_buf
    cmp byte [si], 'r'
    jne .check_cmd_shutdown
    inc si
    cmp byte [si], 'e'
    jne .check_cmd_shutdown
    inc si
    cmp byte [si], 'b'
    jne .check_cmd_shutdown
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_shutdown
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_shutdown
    inc si
    cmp byte [si], 't'
    jne .check_cmd_shutdown
    inc si
    cmp byte [si], 0
    jne .check_cmd_shutdown
    call command_reboot
    ret

; 'shutdown' command
.check_cmd_shutdown:
    mov si, command_buf
    cmp byte [si], 's'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 'h'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 'u'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 't'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 'd'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 'w'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 'n'
    jne .check_cmd_tty
    inc si
    cmp byte [si], 0
    jne .check_cmd_tty
    call command_shutdown
    ret

; 'tty' command
.check_cmd_tty:
    mov si, command_buf
    cmp byte [si], 't'
    jne .check_cmd_whoami
    inc si
    cmp byte [si], 't'
    jne .check_cmd_whoami
    inc si
    cmp byte [si], 'y'
    jne .check_cmd_whoami
    inc si
    cmp byte [si], 0
    jne .check_cmd_whoami
    call command_tty
    ret

; 'whoami' command
.check_cmd_whoami:
    mov si, command_buf
    cmp byte [si], 'w'
    jne .check_cmd_zodiacsay
    inc si
    cmp byte [si], 'h'
    jne .check_cmd_zodiacsay
    inc si
    cmp byte [si], 'o'
    jne .check_cmd_zodiacsay
    inc si
    cmp byte [si], 'a'
    jne .check_cmd_zodiacsay
    inc si
    cmp byte [si], 'm'
    jne .check_cmd_zodiacsay
    inc si
    cmp byte [si], 'i'
    jne .check_cmd_zodiacsay
    inc si
    cmp byte [si], 0
    jne .check_cmd_zodiacsay
    call command_whoami
    ret

; 'zodiacsay' command
.check_cmd_zodiacsay:
    mov si, command_buf
    cmp byte [si], 'z'
    jne .unknown
    inc si
    cmp byte [si], 'o'
    jne .unknown
    inc si
    cmp byte [si], 'd'
    jne .unknown
    inc si
    cmp byte [si], 'i'
    jne .unknown
    inc si
    cmp byte [si], 'a'
    jne .unknown
    inc si
    cmp byte [si], 'c'
    jne .unknown
    inc si
    cmp byte [si], 's'
    jne .unknown
    inc si
    cmp byte [si], 'a'
    jne .unknown
    inc si
    cmp byte [si], 'y'
    jne .unknown
    inc si
    cmp byte [si], ' '
    jne .unknown
    inc si
    cmp byte [si], '"'
    jne .unknown
    inc si
    call command_zodiacsay
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
