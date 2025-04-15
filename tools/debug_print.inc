; debug_print.inc - Debugging Utilities
; BIOS-Compatible Debug Functions
section .text

;───────────────────────────────────────────
; Function: Prints null-terminated string
; Input: DS:SI = string address
; Clobbers: AL, AH, SI
; Requires: BIOS int 0x10 (AH=0x0E)
;───────────────────────────────────────────
print_string:
    pusha
.print_loop:
    lodsb               ; Load next char
    test al, al
    jz .print_done
    mov ah, 0x0E        ; BIOS teletype output
    int 0x10
    jmp .print_loop
.print_done:
    popa
    ret

;───────────────────────────────────────────
; Function: Calculates string length
; Input: DS:SI = string address
; Output: CX = length (excluding null)
; Clobbers: AL, SI, CX
;───────────────────────────────────────────
strlen:
    xor cx, cx
.strlen_loop:
    lodsb
    test al, al
    jz .strlen_done
    inc cx
    jmp .strlen_loop
.strlen_done:
    ret

;───────────────────────────────────────────
; Function: Prints AX as 4-digit hex
; Input: AX = value to print
; Clobbers: AX, CX, DX
;───────────────────────────────────────────
print_hex:
    pusha
    mov cx, 4           ; Process 4 nibbles
.hex_loop:
    rol ax, 4           ; Rotate next nibble into LSB
    mov dl, al
    and dl, 0x0F        ; Isolate nibble
    add dl, '0'
    cmp dl, '9'
    jbe .print
    add dl, 7           ; Adjust for A-F
.print:
    mov ah, 0x0E
    int 0x10
    loop .hex_loop
    popa
    ret

;───────────────────────────────────────────
; Function: Debug prints string with metadata
; Input: DS:SI = string address
; Format: "Length: 0xXXXX, Content: <string>"
;───────────────────────────────────────────
debug_print:
    push si
    call strlen         ; CX = length

    ; Print length header
    push si
    mov si, msg_debug_len
    call print_string
    mov ax, cx
    call print_hex

    ; Print content header
    mov si, msg_debug_content
    call print_string
    pop si              ; Original string
    call print_string

    pop si
    ret

section .data
    msg_debug_len     db "Length: 0x", 0
    msg_debug_content db ", Content: ", 0
