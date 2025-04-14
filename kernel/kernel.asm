%include "include/global.inc"
%include "include/macros.inc"

; =============================================
; Kernel Entry Point (v1.3)
; Architecture: x86 Real Mode
; Memory Map:
;   CS:IP = 0x1000:0x0000 (Linear 0x10000)
;   Segment Registers:
;     CS = DS = ES  ; Code/Data segments unified
;     SS:SP = 0x9000:0xFFFE (64KB stack)
; =============================================
[BITS 16]
[ORG KERNEL_ADDR]

; ─────────────────────────────────────────────
; Code Section
; ─────────────────────────────────────────────

section .text
align ALIGNMENT

global _start
_start:
    ; System Initialization
    INIT_SYSTEM KERNEL_BASE, KERNEL_STACK      ; DS=0x1000, SS=0x9000

    ; Main Kernel Execution
    jmp _main                                  ; Transfer control to kernel core

    ; Safety Net: Halt if main returns (should never happen)
    cli
    hlt
    jmp $

; --- Primary entry points ---
%include "kernel/main.inc"

; --- Functional Modules ---
%include "kernel/modules/login.inc"
%include "kernel/modules/auth.inc"
%include "kernel/modules/prompt.inc"
%include "kernel/modules/shell.inc"

; --- Utility Subroutines Library ---
%include "libs/clear.inc"
%include "libs/halt.inc"
%include "libs/print.inc"
%include "libs/string.inc"

; ─────────────────────────────────────────────
; Data Section
; ─────────────────────────────────────────────

section .data
align ALIGNMENT

; --- Predefined Constants ---
%include "data/data.inc"                       ; System constants and initialized variables
