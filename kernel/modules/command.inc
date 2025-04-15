global handle_command

; ---------------------------------------------
; COMMAND DISPATCHER
; Purpose: High-efficiency command routing for x86 real-mode systems
; Features:
;   - Supports 10+ built-in commands
;   - Handles quoted arguments
;   - Provides unknown command feedback
; Design:
;   - Jump-table for common commands (O(1) lookup)
;   - Linear scan for special cases (echo etc.)
;   - Compatibility:
;     * 8086+ (16-bit real mode)
;     * Optional 386+ optimizations (EAX)
; ---------------------------------------------
handle_command:

; ─────────────────────────────────────────────
; Input validation
; ─────────────────────────────────────────────
.empty_char:
    mov si, command_buf
    cmp byte [si], 0
    je .done

; ─────────────────────────────────────────────
; Multi-character command processing
; ─────────────────────────────────────────────
.single_char:
    cmp byte [si+1], 0                         ; Check if single-character command
    jne .multi_char
    cmp byte [si], '?'                         ; Special case for '?' mark
    je .cmd_question
    jmp .unknown                               ; Other single-char commands are invalid

; ─────────────────────────────────────────────
; Multi-character command processing
; ─────────────────────────────────────────────
.multi_char:
    ; Calculate 2-character hash (convert to uppercase)
    mov bx, [si]
    and bx, 0xDFDF

    ; Jump table matching (most commands)
    cmp bx, 'H' + ('E'<<8)                     ; `help`
    je .cmd_help
    cmp bx, 'A' + ('R'<<8)                     ; `arch`
    je .cmd_arch
    cmp bx, 'C' + ('L'<<8)                     ; `cls`
    je .cmd_cls
    cmp bx, 'D' + ('A'<<8)                     ; `date`
    je .cmd_date
    cmp bx, 'I' + ('P'<<8)                     ; `ip addr`
    je .cmd_ipaddr
    cmp bx, 'L' + ('O'<<8)                     ; `logout`
    je .cmd_logout
    cmp bx, 'P' + ('W'<<8)                     ; `pwd`
    je .cmd_pwd
    cmp bx, 'R' + ('E'<<8)                     ; `reboot`
    je .cmd_reboot
    cmp bx, 'S' + ('H'<<8)                     ; `shutdown`
    je .cmd_shutdown
    cmp bx, 'T' + ('T'<<8)                     ; `tty`
    je .cmd_tty
    cmp bx, 'W' + ('H'<<8)                     ; `whoami`
    je .cmd_whoami

    ; Special linear matching (echo and zodiacsay)
    cmp bx, 'E' + ('C'<<8)                     ; `echo "string"`
    je .check_echo
    cmp bx, 'Z' + ('O'<<8)                     ; `zodiacsay "string"`
    je .check_zodiacsay

    jmp .unknown

; ─────────────────────────────────────────────
; Parameterized command matching
; ─────────────────────────────────────────────
; 'echo' command
.check_echo:
    ; Use 32-bit registers (requires 386+ CPU)
    db 66h               ; Operand size prefix
    mov eax, [si]        ; Safely read 4 bytes
    db 66h
    and eax, 0xDFDFDFDF  ; 32-bit uppercase conversion (fixed mask)
    db 66h
    cmp eax, 'ECHO'
    jne .unknown
    call command_echo
    ret

; 'zodiacsay' command
.check_zodiacsay:
   ; Character-by-character check (16-bit mode)
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
    call command_zodiacsay
    ret

; ─────────────────────────────────────────────
; Built-in command handlers
; ─────────────────────────────────────────────
; 'help' command
.cmd_help:
    mov di, cmd_help_str
    call validate_full_cmd
    jc .unknown
    call command_help
    ret

; '?' command
.cmd_question:
    call command_help
    ret

; 'arch' command
.cmd_arch:
    mov di, cmd_arch_str
    call validate_full_cmd
    jc .unknown
    call command_arch
    ret

; 'cls' command
.cmd_cls:
    mov di, cmd_cls_str
    call validate_full_cmd
    jc .unknown
    call command_cls
    ret

; 'date' command
.cmd_date:
    mov di, cmd_date_str
    call validate_full_cmd
    jc .unknown
    call command_date
    ret

; 'ip addr' command
.cmd_ipaddr:
    mov di, cmd_ipaddr_str
    call validate_full_cmd
    jc .unknown
    call command_ipaddr
    ret

; 'logout' command
.cmd_logout:
    mov di, cmd_logout_str
    call validate_full_cmd
    jc .unknown
    call command_logout
    ret

; 'pwd' command
.cmd_pwd:
    mov di, cmd_pwd_str
    call validate_full_cmd
    jc .unknown
    call command_pwd
    ret

; 'reboot' command
.cmd_reboot:
    mov di, cmd_reboot_str
    call validate_full_cmd
    jc .unknown
    call command_reboot
    ret

; 'shutdown' command
.cmd_shutdown:
    mov di, cmd_shutdown_str
    call validate_full_cmd
    jc .unknown
    call command_shutdown
    ret

; 'tty' command
.cmd_tty:
    mov di, cmd_tty_str
    call validate_full_cmd
    jc .unknown
    call command_tty
    ret

; 'whoami' command
.cmd_whoami:
    mov di, cmd_whoami_str
    call validate_full_cmd
    jc .unknown
    call command_whoami
    ret

; ─────────────────────────────────────────────
; Error Handling
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

; ─────────────────────────────────────────────
; Subroutines
; Input: DI = command template address, SI = user input
; Output: CF=0 if match successful
; ─────────────────────────────────────────────
validate_full_cmd:
    push si
    push di
.compare_loop:
    mov al, [di]
    or al, al
    jz .check_end
    cmp al, [si]
    jne .mismatch
    inc di
    inc si
    jmp .compare_loop
.check_end:
    cmp byte [si], 0
    je .match
.mismatch:
    stc
    jmp .done
.match:
    clc
.done:
    pop di
    pop si
    ret
