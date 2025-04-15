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
permission_denied    db 'Permission denied (Requires root)', 0
newline              db 13, 10, 0                           ; Newline character, defined separately

; ────────────────────────────────────────────
; 📝 INPUT BUFFERS (Read-Write)
; ────────────────────────────────────────────
username_buf         times (MAX_USERNAME_LEN + 1) db 0      ; Username input buffer
prompt_buf           times (MAX_USERNAME_LEN + 15 + 1) db 0 ; Command prompt buffer
command_buf          times (MAX_COMMAND_LEN + 1) db 0       ; Command buffer

; ────────────────────────────────────────────
; 🔧 SYSTEM BUILT-IN COMMANDS (Read-Only)
; ────────────────────────────────────────────
cmd_unknown_prefix   db 'Unknown command: ', 0              ; Error template

cmd_help_1           db 'Available commands:', 13, 10, 0
cmd_help_2           db '  help       Show command reference', 13, 10, 0
cmd_help_3           db '  ?          Same as help (alias)', 13, 10, 0
cmd_help_4           db '  arch       Display CPU architecture', 13, 10, 0
cmd_help_5           db '  cls        Clear terminal screen', 13, 10, 0
cmd_help_6           db '  date       Display system datetime in ISO 8601 format', 13, 10, 0
cmd_help_7           db '  echo       Print text to the terminal', 13, 10, 0
cmd_help_8           db '  ip addr    Display network configuration', 13, 10, 0
cmd_help_9           db '  logout     Terminate user session', 13, 10, 0
cmd_help_10          db '  pwd        Display current working directory', 13, 10, 0
cmd_help_11          db '  reboot     Restart the system (root access required)', 13, 10, 0
cmd_help_12          db '  shutdown   Power off the system (root access required)', 13, 10, 0
cmd_help_13          db '  tty        Display terminal device information', 13, 10, 0
cmd_help_14          db '  whoami     Display current user', 13, 10, 0

cmd_arch_1           db '    __________________', 13, 10, 0
cmd_arch_2           db '   /                  \', 13, 10, 0
cmd_arch_3           db '  |    x86 - 16-bit    |', 13, 10, 0
cmd_arch_4           db '  |      Real Mode     |   Current architecture: [x86] (aka "The Old Guard")', 13, 10, 0
cmd_arch_5           db '   \__________________/', 13, 10, 0
cmd_arch_6           db '  |    A blast from    |   A 16-bit classic, a relic from the golden days of', 13, 10, 0
cmd_arch_7           db '  |    the past, but   |   computing, and still going strong!', 13, 10, 0
cmd_arch_8           db '  |    still running!  |', 13, 10, 0
cmd_arch_9           db '   \__________________/', 13, 10, 0

cmd_ipaddr_1         db  'NetTable v0.99 (Turbo XT++)', 13, 10, 0
cmd_ipaddr_2         db  '-----------------------------------', 13, 10, 0
cmd_ipaddr_3         db  13, 10, 'LOOPBACK  ', 0
cmd_ipaddr_4         db  'HWaddr 00-00-00-00-00-00', 13, 10, 0
cmd_ipaddr_5         db  '          IPaddr  127.0.0.1/8', 13, 10, 0
cmd_ipaddr_6         db  13, 10, 'ETH0      ', 0
cmd_ipaddr_7         db  'HWaddr 00-0C-28-64-3A-F7', 13, 10, 0
cmd_ipaddr_8         db  '          IPaddr  192.168.1.100/24', 13, 10, 0
cmd_ipaddr_9         db  '          Gateway 192.168.1.254', 13, 10, 0
cmd_ipaddr_10        db  13, 10, '[Press ANY KEY to return]', 0

cmd_cls_flag         db 0                                   ; Screen status (0=dirty,1=clean)
cmd_pwd_user_path    db '/home/', 0                         ; /home/<username>
cmd_pwd_root_path    db '/root', 0                          ; /root
cmd_tty_output       db '/dev/ttyX1', 0
cmd_logout_msg       db 'Returning to login...', 0
cmd_reboot_msg       db 'Rebooting Tiny-DOS...', 0
cmd_shutdown_msg     db 'Goodbye from Tiny-DOS!', 0
