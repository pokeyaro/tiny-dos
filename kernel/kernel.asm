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
%include "kernel/modules/command.inc"
%include "kernel/modules/datetime.inc"

; --- Command Modules ---
; Note: All depend on command.inc
%include "commands/help.inc"
%include "commands/arch.inc"
%include "commands/cls.inc"
%include "commands/date.inc"
%include "commands/echo.inc"
%include "commands/ipaddr.inc"
%include "commands/logout.inc"
%include "commands/pwd.inc"
%include "commands/reboot.inc"
%include "commands/shutdown.inc"
%include "commands/tty.inc"
%include "commands/whoami.inc"
%include "commands/zodiacsay.inc"

; --- Utility Subroutines Library ---
%include "libs/clear.inc"
%include "libs/halt.inc"
%include "libs/print.inc"
%include "libs/rand.inc"
%include "libs/string.inc"

; ─────────────────────────────────────────────
; Data Section
; ─────────────────────────────────────────────

section .data
align ALIGNMENT

; --- Predefined Constants ---
%include "data/data.inc"                       ; System constants and initialized variables
