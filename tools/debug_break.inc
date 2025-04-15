; debug_break.inc - Debugging Utilities

;───────────────────────────────────────────
; Function: Debug Breakpoint (xchg bx, bx)
; Purpose: Software breakpoint for debuggers
; Clobbers: BX (swaps BX with itself)
; Notes:
;   - Opcode 0x87DB acts as magic breakpoint in Bochs/QEMU
;   - No effect on hardware (BX remains unchanged)
;───────────────────────────────────────────
debug_break:
    xchg bx, bx    ; Magic breakpoint (87 DB)
    ret
