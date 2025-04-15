; =============================================
; System Macros
; =============================================

; ────────────────────────────────────────────
; Macro: INIT_SYSTEM
; Purpose: Safely initializes kernel environment
; Parameters:
;   %1 = Data segment base (non-zero, ≠0x07C0)
;   %2 = Stack segment base (≥0x1000 recommended)
; Usage:
;   INIT_SYSTEM 0x2000, 0x9000  ; DS=0x2000, SS=0x9000
; Requirements:
;   - CS must be set via far jump (e.g., jmp 0x1000:0x0000)
; Safety Checks:
;   - Compile-time validation of segment values
;   - Atomic stack setup with interrupts disabled
; ────────────────────────────────────────────
%macro INIT_SYSTEM 2
    ; Defense programming: Compile-time checks
    %if %1 == 0 || %1 == 0x07C0
        %error "Data segment conflict: Cannot use 0x0000 or 0x07C0 (BIOS area)"
    %endif
    %if %2 < 0x1000
        %warning "Low stack address (recommend ≥0x1000)"
    %endif

    cli                     ; Disable interrupts during setup

    ; Zero general-purpose registers
    xor ax, ax
    mov bx, ax
    mov cx, ax
    mov dx, ax
    mov si, ax
    mov di, ax

    ; Initialize data segments
    mov ax, %1              ; Data segment base
    mov ds, ax
    mov es, ax              ; ES for string operations

    ; Initialize stack (SS:SP)
    mov ax, %2              ; Stack segment base
    mov ss, ax
    mov sp, 0xFFFE          ; Top of stack (word-aligned)

    sti                     ; Re-enable interrupts

    ; Debug markers (optional)
    %ifdef DEBUG
        mov word [ss:0], 0xDEAD    ; Stack bottom marker
        mov word [ss:0xFFFE], 0xBEEF ; Stack top marker
    %endif
%endmacro

; ────────────────────────────────────────────
; Macro: ECHO
; Purpose: Prints multiple strings sequentially
; Syntax: ECHO str1, str2, ..., strN
; Clobbers: SI
; ────────────────────────────────────────────
%macro ECHO 1-*
    %rep %0
        mov si, %1
        call print
    %rotate 1
    %endrep
%endmacro

; ────────────────────────────────────────────
; Macro: NEWLINE
; Purpose: Prints configurable line breaks
; Parameters:
;   %1 = Number of newlines (default=1)
; Optimizations:
;   - Preserves CX via stack
;   - Uses BIOS teletype output (AH=0x0E)
; ────────────────────────────────────────────
%macro NEWLINE 0-1 1
    %if %1 < 1
        %error "Line count must be ≥1"
    %endif

    push cx
    push ax                ; Save caller's AH
    mov cx, %1
%%print_line:
    mov al, 0x0D           ; CR
    call print_char
    mov al, 0x0A           ; LF
    call print_char
    loop %%print_line
    pop ax                 ; Restore AH
    pop cx
%endmacro

; ────────────────────────────────────────────
; BIOS Utility Macros
; ────────────────────────────────────────────

%macro CLS 0                ; AH=00h, AL=03h (80x25 text)
    mov ah, 0x00
    mov al, 0x03
    int 0x10
%endmacro

%macro SET_CURSOR 2         ; AH=02h, BH=page, DH/DL=row/col
    mov ah, 0x02
    mov bh, 0x00
    mov dl, %1              ; Column
    mov dh, %2              ; Row
    int 0x10
%endmacro

%macro BREAKPOINT 0        ; Bochs/QEMU magic break
    xchg bx, bx            ; 87 DB
%endmacro
