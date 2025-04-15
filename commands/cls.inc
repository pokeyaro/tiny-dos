global command_cls

command_cls:
    call clear
    mov byte [cmd_cls_flag], 1                 ; Set post-execution flag
    ret
