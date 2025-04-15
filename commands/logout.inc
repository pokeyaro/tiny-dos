global command_logout

command_logout:
    NEWLINE 2
    ECHO cmd_logout_msg
    NEWLINE
    pop ax                                     ; Clean up the return address pushed by call
    jmp _main                                  ; Return to the login interface
