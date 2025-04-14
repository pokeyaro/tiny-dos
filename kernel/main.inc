global _main

_main:
.start_input:
    ; Clear screen
    CLS

    ; Output prompt for username
    ECHO prompt_enter

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

; ---------------------------------------------
; Enter shell main loop
; ---------------------------------------------
shell:
    NEWLINE
    call show_prompt                           ; ✅ Display the prompt again
    call read_command                          ; ⌨️ Wait for user input
    jmp shell
    ret
