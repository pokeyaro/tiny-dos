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
    cmp byte [cmd_cls_flag], 1                 ; 'cls' command logic will trigger the condition
    je .skip_newline

    NEWLINE

.skip_newline:
    mov byte [cmd_cls_flag], 0                 ; Reset to 0 (skip only once)
    call show_prompt                           ; ✅ Display the prompt again
    call read_command                          ; ⌨️ Wait for user input
    call handle_command                        ; ❓  Identify the available commands
    jmp shell
    ret
