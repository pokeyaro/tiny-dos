%include "include/global.inc"

; =============================================
; Bootloader
; Architecture: x86 Real Mode
; Memory Map:
;   Loads kernel at: 0x10000 (0x1000:0x0000)
;   Stack: 0x9000:0xFFFE
; =============================================
[BITS 16]
[ORG BOOT_LOADER]

section .text
align ALIGNMENT

; --- Main Entry Point ---
global _start
_start:
    ; Load Kernel
    mov ax, KERNEL_BASE                       ; Destination segment
    mov es, ax
    mov bx, KERNEL_LIMIT                      ; BX = KERNEL_LIMIT (0x0000)

    ; Configure Disk Read (CHS mode)
    mov ch, CYLINDER_NUM                      ; Cylinder/Track number
    mov dh, HEAD_NUM                          ; Head number
    mov cl, SECTOR_NUM                        ; Sector number
    mov al, SECTORS_TO_READ                   ; Number of sectors to read
    mov dl, DISK_DRIVE_NUM                    ; Drive number (0x00 = first floppy drive)
    mov ah, 0x02                              ; INT 13h function 0x02: Read disk sectors

    ; Execute Read
    int 0x13                                  ; Invoke BIOS disk I/O interrupt
    jc .disk_error                            ; Fallthrough on success

    ; Handoff to Kernel
    jmp KERNEL_BASE:KERNEL_LIMIT              ; Far jump to kernel address

; --- Error Handler ---
.disk_error:
    mov ax, (0x0E << 8) | '?'                 ; AH=0x0E (BIOS teletype output), AL='?' (error symbol)
    int 0x10
    hlt

; --- Boot Signature Padding ---
times BOOT_SIZE - MAGIC_SIZE - ($ - $$) db 0  ; Pad remainder of boot sector with zeros
dw BOOT_SIGNATURE                             ; Boot signature (magic number at end of sector)
