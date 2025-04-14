global halt

; Subroutine: Stops CPU execution with CLI/HLT
; Clobbers: None
halt:
    cli                 ; Disable interrupts
    hlt                 ; Halt processor (requires NMI or reset to wake)
    ret
