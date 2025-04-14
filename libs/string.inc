global strcpy, strcat

; Subroutine: Copies null-terminated string (DS:SI -> ES:DI)
; Input: DS:SI = source string, ES:DI = destination buffer
; Clobbers: AL, SI, DI
; Notes: Requires direction flag cleared (DF=0)
strcpy:
    lodsb                   ; AL = [DS:SI], SI++
    stosb                   ; [ES:DI] = AL, DI++
    test al, al             ; Check for null terminator
    jnz strcpy              ; Continue if not end of string
    ret

; Subroutine: Concatenates null-terminated string (DS:SI after ES:DI)
; Input: DS:SI = source string, ES:DI = destination buffer (must have space)
; Clobbers: AL, SI, DI
; Notes: DI must point to end of existing string
strcat:
    lodsb                   ; AL = [DS:SI], SI++
    stosb                   ; [ES:DI] = AL, DI++
    test al, al             ; Check for null terminator
    jnz strcat              ; Continue if not end of string
    ret
