global build_prompt_from_root
global build_prompt_from_user
global show_prompt

; General prompt construction (root/regular user)
build_prompt_from_root:
    mov si, prompt_suffix_root
    jmp build_prompt

build_prompt_from_user:
    mov si, prompt_suffix_user
    jmp build_prompt

build_prompt:                                  ; Common logic for prompt construction
    push si                                    ; Save suffix address
    ; Copy username
    mov si, username_buf
    mov di, prompt_buf
    call strcpy                                ; String copy
    ; Append suffix (key fix: decrement di)
    dec di                                     ; Move back to last character of username
    pop si                                     ; Restore suffix address
    call strcat                                ; String concatenation
    ret

; Output stored prompt
show_prompt:
    mov si, prompt_buf
    call print
    ret
