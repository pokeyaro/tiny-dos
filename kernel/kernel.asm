[BITS 16]
[ORG 0x0500]

; Username input length limits
MIN_USERNAME_LEN equ 3
MAX_USERNAME_LEN equ 8

; ----------------------------
; Code section
; ----------------------------
section .text
global _start

_start:
    ; Initialize segment registers
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax

.start_input:
    ; Clear screen
    call cls

    ; Output prompt for username
    mov si, prompt_enter
    call print

    ; Input username
    mov di, username_buf
    call read_login_username

; User type check
.check_user:
    mov si, username_buf
    call is_root_user
    jz .root

.user:
    call build_prompt_from_user
    jmp shell

.root:
    call build_prompt_from_root
    jmp shell

; Enter shell main loop
shell:
    mov si, newline
    call print
    call show_prompt

; ----------------------------
; Username input function (complete validation rules)
; - First character must not be a digit
; - Only characters a-z and 0-9 allowed
; - Length must be between 3 and 8 characters
; ----------------------------
read_login_username:
    xor cx, cx                ; Character counter
    mov di, username_buf

.login_loop:
    mov ah, 0x00
    int 0x16                  ; Wait for keyboard input
    cmp al, 13                ; Check if Enter key is pressed
    je .check_username_length

    cmp cx, MAX_USERNAME_LEN
    jae .login_loop           ; If input exceeds max length, continue discarding

    ; Check if first character is a digit (invalid)
    cmp cx, 0
    jne .check_char_valid     ; Skip digit check if it's not the first character
    cmp al, '0'
    jb .check_letter_start    ; If less than '0', valid
    cmp al, '9'
    jbe .login_loop           ; If it's a digit, skip

.check_letter_start:
    ; Check if it's a lowercase letter (a-z)
    cmp al, 'a'
    jb .login_loop            ; If less than 'a', discard
    cmp al, 'z'
    jbe .accept_char          ; If between 'a' and 'z', accept

    jmp .login_loop           ; Otherwise discard

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
    int 0x10                  ; Display input character
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
    jmp _start

; Check if root or regular user
is_root_user:
    cmp byte [si], 'r'
    jne .not_root
    inc si
    cmp byte [si], 'o'
    jne .not_root
    inc si
    cmp byte [si], 'o'
    jne .not_root
    inc si
    cmp byte [si], 't'
    jne .not_root
    inc si
    cmp byte [si], 0          ; Output: ZF=1 means root, ZF=0 means user
    ret
.not_root:
    or al, 1                  ; Clear ZF flag
    ret

; General prompt construction (root/regular user)
build_prompt_from_root:
    mov si, prompt_suffix_root
    jmp build_prompt

build_prompt_from_user:
    mov si, prompt_suffix_user
    jmp build_prompt

build_prompt:                 ; Common logic for prompt construction
    push si                   ; Save suffix address
    ; Copy username
    mov si, username_buf
    mov di, prompt_buf
    call strcpy               ; String copy
    ; Append suffix (key fix: decrement di)
    dec di                    ; Move back to last character of username
    pop si                    ; Restore suffix address
    call strcat               ; String concatenation
    ret

; Output stored prompt
show_prompt:
    mov si, prompt_buf
    call print
    ret

; ----------------------------
; Clear screen subroutine
; ----------------------------
cls:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    ret

; ----------------------------
; Print string subroutine
; ----------------------------
print:
.next_char:
    lodsb
    cmp al, 0
    je .done
    mov ah, 0x0E
    int 0x10
    jmp .next_char
.done:
    ret

; ----------------------------
; String copy (DS:SI -> ES:DI)
; ----------------------------
strcpy:
    lodsb
    stosb
    test al, al
    jnz strcpy
    ret

; ----------------------------
; String concatenation (DS:SI appended to ES:DI)
; ----------------------------
strcat:
    lodsb
    stosb
    test al, al
    jnz strcat
    ret


; ----------------------------
; Data section
; ----------------------------
section .data

prompt_enter         db 'A:\> Enter username: ', 0
prompt_suffix_root   db '@localhost:~# ', 0
prompt_suffix_user   db '@localhost:~$ ', 0
welcome_msg          db 'Welcome to Tiny-DOS!', 0

username_buf         times (MAX_USERNAME_LEN + 1) db 0      ; Username input buffer
prompt_buf           times (MAX_USERNAME_LEN + 15 + 1) db 0 ; Command prompt buffer

newline              db 13, 10, 0   ; Newline character, defined separately
