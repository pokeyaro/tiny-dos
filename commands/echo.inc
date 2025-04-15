global command_echo

command_echo:
    NEWLINE
    mov si, command_buf

; Locates the first space after 'echo'
.find_space:
    lodsb
    cmp al, 0
    je .done                                   ; Early exit if no args
    cmp al, ' '
    jne .find_space

; Verifies argument opening quote
.find_quote_start:
    lodsb
    cmp al, 0
    je .done
    cmp al, '"'
    jne .find_quote_start

; Prints until closing quote or null
.print_content:
    lodsb
    cmp al, 0
    je .done                                   ; Unterminated quote
    cmp al, '"'
    je .done                                   ; Stop on terminator
    call print_char
    jmp .print_content

.done:
    ret
