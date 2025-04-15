global command_pwd

command_pwd:
    ; Privilege check
    mov si, username_buf
    call is_root_user
    jnz .access_denied

    ; Root path display
    NEWLINE
    ECHO cmd_pwd_root_path
    ret

.access_denied:
    NEWLINE
    ; User path construction
    ECHO cmd_pwd_user_path, username_buf
    ret
