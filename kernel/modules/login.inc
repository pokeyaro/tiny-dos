global read_login_username

; ---------------------------------------------
; Username input function (complete validation rules)
; - First character must not be a digit
; - Only characters a-z and 0-9 allowed
; - Length must be between 3 and 8 characters
; ---------------------------------------------
read_login_username:
    xor cx, cx                                 ; Character counter
    mov di, username_buf

.login_loop:
    mov ah, 0x00
    int 0x16                                   ; Wait for keyboard input
    cmp al, 13                                 ; Check if Enter key is pressed
    je .check_username_length

    cmp cx, MAX_USERNAME_LEN
    jae .login_loop                            ; If input exceeds max length, continue discarding

    ; Check if first character is a digit (invalid)
    cmp cx, 0
    jne .check_char_valid                      ; Skip digit check if it's not the first character
    cmp al, '0'
    jb .check_letter_start                     ; If less than '0', valid
    cmp al, '9'
    jbe .login_loop                            ; If it's a digit, skip

.check_letter_start:
    ; Check if it's a lowercase letter (a-z)
    cmp al, 'a'
    jb .login_loop                             ; If less than 'a', discard
    cmp al, 'z'
    jbe .accept_char                           ; If between 'a' and 'z', accept

    jmp .login_loop                            ; Otherwise discard

.check_char_valid:
    ; Only lowercase letters (a-z) and digits (0-9) are allowed
    cmp al, 'a'
    jb .check_digit
    cmp al, 'z'
    jbe .accept_char

.check_digit:
    ; Digits 0-9
    cmp al, '0'
    jb .login_loop
    cmp al, '9'
    jbe .accept_char

    jmp .login_loop

.accept_char:
    stosb
    mov ah, 0x0E
    int 0x10                                   ; Display input character
    inc cx
    jmp .login_loop

.check_username_length:
    cmp cx, MIN_USERNAME_LEN
    jb .retry_login
    cmp cx, MAX_USERNAME_LEN + 1
    ja .retry_login

    ; If length is valid, append null terminator
    mov al, 0
    stosb

    mov si, newline
    call print
    mov si, newline
    call print

    mov si, welcome_msg
    call print
    mov si, newline
    call print

    ret

.retry_login:
    jmp _main
