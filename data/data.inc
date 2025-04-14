; =============================================
; 📦 String Resources & Buffers
; Memory Layout:
;   - Static strings: ROM-able (read-only)
;   - Buffers: RAM-allocated (writable)
; =============================================

; ────────────────────────────────────────────
; 📅 TIME DATA BUFFERS (Read-Write)
; ────────────────────────────────────────────
datetime_century     db 0
datetime_year        db 0
datetime_month       db 0
datetime_day         db 0
datetime_hour        db 0
datetime_min         db 0
datetime_sec         db 0
datetime_str         times 20 db 0                          ; Format: "YYYY-MM-DD HH:MM:SS" + null

; ────────────────────────────────────────────
; 📜 STATIC STRINGS (Read-Only)
; ────────────────────────────────────────────
prompt_enter         db "A:\> Enter username: ", 0
prompt_suffix_root   db "@localhost:~# ", 0
prompt_suffix_user   db "@localhost:~$ ", 0
welcome_msg          db "Welcome to Tiny-DOS!", 0
login_time_prefix    db 'Login successful on: ', 0
newline              db 13, 10, 0                           ; Newline character, defined separately

; ────────────────────────────────────────────
; 📝 INPUT BUFFERS (Read-Write)
; ────────────────────────────────────────────
username_buf         times (MAX_USERNAME_LEN + 1) db 0      ; Username input buffer
prompt_buf           times (MAX_USERNAME_LEN + 15 + 1) db 0 ; Command prompt buffer
command_buf          times (MAX_COMMAND_LEN + 1) db 0       ; Command buffer
