[BITS 16]                       ; Generate 16-bit code
[ORG 0x7C00]                    ; Bootloader loads at memory address 0x7C00

KERNEL_ADDR equ 0x0500          ; Memory address where kernel will be loaded

section .text
global _start

; --- Main Entry Point ---
_start:
    ; Read disk using CHS mode
    mov ch, 0                   ; Cylinder/Track number = 0
    mov dh, 0                   ; Head number = 0
    mov cl, 2                   ; Sector number = 2 (sectors are 1-based)
    mov al, 20                  ; Number of sectors to read (20*512 = 10KB)
    mov bx, KERNEL_ADDR         ; ES:BX = Destination buffer (0x0000:0x0500 = 0x0500 linear)
    mov ah, 0x02                ; BIOS function 0x02: Read disk sectors
    mov dl, 0x00                ; Drive number (0x00 = first floppy drive)

    ; Invoke BIOS disk I/O interrupt
    int 0x13                    ; Call BIOS interrupt 13h for disk services

   ; After loading, jump to kernel entry point
    jmp 0x0000:KERNEL_ADDR      ; Far jump to kernel code (CS=0x0000, IP=0x0500)

; --- Boot Signature Padding ---
times 510 - ($ - $$) db 0       ; Pad remainder of boot sector with zeros
dw 0xAA55                       ; Boot signature (magic number at end of sector)