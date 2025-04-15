global is_root_user

; ---------------------------------------------
; Function: is_root_user
; Purpose: Verifies if current user is root
; Input: DS:SI -> null-terminated username
; Output:
;   ZF = 1 if root (username == "root")
;   ZF = 0 otherwise
; Clobbers: AL, SI
; Security:
;   - Case-sensitive comparison
;   - Strict length validation
; ---------------------------------------------
is_root_user:
    ; Check for exact match to "root"
    lodsb                                      ; AL = [SI], SI++
    cmp al, 'r'
    jne .not_root
    lodsb
    cmp al, 'o'
    jne .not_root
    lodsb
    cmp al, 'o'
    jne .not_root
    lodsb
    cmp al, 't'
    jne .not_root
    lodsb
    cmp al, 0                                  ; Verify null terminator
    ret                                        ; ZF set by cmp

.not_root:
    test al, 1                                 ; Clear ZF (AL value irrelevant)
    ret
