; =============================================
; System Constants
; =============================================

; ─────────────────────────────────────────────
; Memory Configuration
; ─────────────────────────────────────────────
ALIGNMENT        equ 2                         ; Segment alignment (power of 2)
BOOT_LOADER      equ 0x7C00                    ; BIOS loads boot sector here
KERNEL_BASE      equ 0x1000                    ; CS base address
KERNEL_LIMIT     equ 0x0000                    ; IP offset
KERNEL_ADDR      equ (KERNEL_BASE << 4 + KERNEL_LIMIT) ; Linear: 0x10000
KERNEL_STACK     equ 0x9000                    ; SS:SP initial value

; ─────────────────────────────────────────────
; Disk Operations (INT 13h)
; ─────────────────────────────────────────────
CYLINDER_NUM     equ 0                         ; Track 0
HEAD_NUM         equ 0                         ; Head 0
SECTOR_NUM       equ 2                         ; Skip boot sector
SECTORS_TO_READ  equ 20                        ; ~10KB kernel max
DISK_DRIVE_NUM   equ 0x00                      ; Floppy A:

; ─────────────────────────────────────────────
; Boot Validation
; ─────────────────────────────────────────────
BOOT_SIZE        equ 512                       ; MBR size (512B)
MAGIC_SIZE       equ 2                         ; Magic size (2B)
BOOT_SIGNATURE   equ 0xAA55                    ; Magic number

; ─────────────────────────────────────────────
; System Parameters
; ─────────────────────────────────────────────
TIMEZONE_OFFSET  equ 8                         ; UTC+8 (CST)
MIN_USERNAME_LEN equ 3                         ; Username constraints
MAX_USERNAME_LEN equ 8
MAX_COMMAND_LEN  equ 50                        ; Input buffer size
