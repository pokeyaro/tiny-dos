global read_cmos_datetime, format_datetime_string
global get_century, get_year, get_month, get_day
global get_hour, get_minute, get_second

; ---------------------------------------------
; 📅 RTC/CMOS DateTime Module
; Features:
;   - CMOS BCD → Binary conversion
;   - Timezone-aware formatting
;   - Thread-safe getters
; Hardware:
;   - Requires CMOS/RTC chip
;   - Supports century register (0x32)
; Safety:
;   - NMI disabled during reads
;   - Atomic time reads via update waiting
; ---------------------------------------------

; ─────────────────────────────────────────────
; Hardware Constants (CMOS/RTC)
; ─────────────────────────────────────────────
; --- I/O Port Definitions ---
%define CMOS_ADDR     0x70                     ; [OUT] Register index/command port (write-only)
%define CMOS_DATA     0x71                     ; [IN/OUT] Data transfer port (read/write)

; --- RTC Timekeeping Registers (BCD Format) ---
%define CMOS_SEC      0x00                     ; Seconds (00-59)
%define CMOS_MIN      0x02                     ; Minutes (00-59)
%define CMOS_HOUR     0x04                     ; Hours (00-23, 12/24h mode dependent)
%define CMOS_DAY      0x07                     ; Day of month (01-31)
%define CMOS_MONTH    0x08                     ; Month (01-12)
%define CMOS_YEAR     0x09                     ; Year (00-99)

; --- Extended Registers (Vendor-Specific) ---
%define CMOS_CENTURY  0x32                     ; Century (19-20 typical)
                                               ; ❗ Some chips: 0x48 (Lenovo/Dell)
%define CMOS_STATUS_A 0x0A                     ; Status Register A (update in progress flag)

; ─────────────────────────────────────────────
; CMOS Interface
; ─────────────────────────────────────────────
read_cmos_datetime:
    call wait_cmos_update                      ; Ensure atomic read

    ; Read all time fields
    ; second
    mov al, CMOS_SEC
    call read_cmos_field
    mov [datetime_sec], al

    ; minute
    mov al, CMOS_MIN
    call read_cmos_field
    mov [datetime_min], al

    ; hour
    mov al, CMOS_HOUR
    call read_cmos_field
    mov [datetime_hour], al

    ; day
    mov al, CMOS_DAY
    call read_cmos_field
    mov [datetime_day], al

    ; month
    mov al, CMOS_MONTH
    call read_cmos_field
    mov [datetime_month], al

    ; year
    mov al, CMOS_YEAR
    call read_cmos_field
    mov [datetime_year], al

    ; century
    mov al, CMOS_CENTURY
    call read_cmos_field
    mov [datetime_century], al

    ret

; ─────────────────────────────────────────────
; Wait for CMOS Update Completion
; Clobbers: AL
; ─────────────────────────────────────────────
wait_cmos_update:
    mov al, CMOS_STATUS_A
    out CMOS_ADDR, al
    in al, CMOS_DATA
    test al, 0x80                              ; Check UIP (Update In Progress)
    jnz wait_cmos_update
    ret

; ─────────────────────────────────────────────
; Read CMOS Field with NMI Disabled
; Input: AL = Register index
; Output: AL = Binary value
; ─────────────────────────────────────────────
read_cmos_field:
    cli                                        ; Critical section
    or al, 0x80                                ; Disable NMI
    out CMOS_ADDR, al
    in al, CMOS_DATA
    call bcd_to_bin
    sti
    ret

; ─────────────────────────────────────────────
; BCD → Binary
; Input: AL = BCD value (0x00-0x99)
; Output: AL = Decimal (0-99)
; ─────────────────────────────────────────────
bcd_to_bin:
    push cx
    mov cl, al
    and al, 0xF0
    shr al, 4
    mov ch, 10
    mul ch
    and cl, 0x0F
    add al, cl
    pop cx
    ret

; ─────────────────────────────────────────────
; Time Getters (Thread-safe)
; All return: AL = Value
; ─────────────────────────────────────────────
get_century:
    mov al, [datetime_century]
    ret

get_year:
    mov al, [datetime_year]
    ret

get_month:
    mov al, [datetime_month]
    ret

get_day:
    mov al, [datetime_day]
    ret

get_hour:
    mov al, [datetime_hour]
    ret

get_minute:
    mov al, [datetime_min]
    ret

get_second:
    mov al, [datetime_sec]
    ret

; ─────────────────────────────────────────────
; Time Formatting Function
; Purpose: Generates ISO-8601 formatted timestamp
; Output:
;   - Populates datetime_str buffer
;   - Format: "YYYY-MM-DD HH:MM:SS" (null-terminated)
; Features:
;   - Timezone adjustment (UTC±offset)
;   - Day overflow handling
; Design Rationale:
;   1. Stack-based Temporary Storage
;     - Isolates variables from register pollution
;     - Centralizes debug points (all vars in stack frame)
;   2. Protected Execution
;     - Avoids implicit register conflicts (AX/BX preserved)
;     - Atomic operations during time calculations
; Limitations:
;   - No month/year overflow handling (assumes <24h delta)
; ─────────────────────────────────────────────
; Technical Implementation Notes:
;   1. Stack Frame Layout:
;      BP-7 → Century
;      BP-6 → Year
;      BP-5 → Month
;      BP-4 → Day (adjusted)
;      BP-3 → Hour (timezone corrected)
;      BP-2 → Minute
;      BP-1 → Second
;
;   2. Timezone Handling:
;      Original UTC hour + OFFSET → BP-3
;      Day++ if hour ≥24
;
;   3. Formatting Sequence:
;      YYYY → MM → DD → SP → HH → MM → SS
;      Uses stosb for buffer building
; ─────────────────────────────────────────────
format_datetime_string:
    pusha
    push bp
    mov bp, sp
    sub sp, 7                                  ; Allocate temp vars

    ; Load time into stack frame
    mov al, [datetime_century]
    mov [bp - 7], al                           ; century: BP-7
    mov al, [datetime_year]
    mov [bp - 6], al                           ; year: BP-6
    mov al, [datetime_month]
    mov [bp - 5], al                           ; month: BP-5
    mov al, [datetime_day]
    mov [bp - 4], al                           ; day: BP-4
    mov al, [datetime_hour]
    mov [bp - 3], al                           ; hour: BP-3
    mov al, [datetime_min]
    mov [bp - 2], al                           ; minute: BP-2
    mov al, [datetime_sec]
    mov [bp - 1], al                           ; second: BP-1

    ; Timezone adjustment
    mov al, [bp - 3]                           ; Original hour
    ; add al, TIMEZONE_OFFSET                  ; UTC+8
    cmp al, 24
    jb .no_overflow
    sub al, 24
    inc byte [bp - 4]                          ; Increment day
.no_overflow:
    mov [bp - 3], al                           ; Store adjusted hour

    ; Generate formatted string
    mov di, datetime_str

    ; date 'YYYY-MM-DD'
    mov al, [bp - 7]                           ; Century
    call itoa_byte
    mov al, [bp - 6]                           ; Year
    call itoa_byte
    mov al, '-'
    stosb
    mov al, [bp - 5]                           ; Month
    call itoa_byte
    mov al, '-'
    stosb
    mov al, [bp - 4]                           ; Day
    call itoa_byte

    mov al, ' '                                ; ' '
    stosb

    ; time 'HH:MM:SS'
    mov al, [bp - 3]                           ; Hour
    call itoa_byte
    mov al, ':'
    stosb
    mov al, [bp - 2]                           ; Minute
    call itoa_byte
    mov al, ':'
    stosb
    mov al, [bp - 1]                           ; Second
    call itoa_byte

    xor al, al                                 ; Null terminator
    stosb

    ; Cleanup
    mov sp, bp
    pop bp
    popa
    ret

; ─────────────────────────────────────────────
; Integer to ASCII Conversion
; Input: AL = Number (0-99)
; Output: DI += 2 ASCII chars
; ─────────────────────────────────────────────
itoa_byte:
    xor ah, ah
    mov bl, 10
    div bl                                     ; AL = high, AH = low
    call itoa_digit
    stosb
    mov al, ah
    call itoa_digit
    stosb
    ret

; Convert single digit to ASCII
itoa_digit:
    add al, '0'
    ret
