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

; Help Command Related
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
cmd_help_15          db '  zodiacsay  Show random Chinese zodiac ASCII art', 13, 10, 0

; Arch Command Related
cmd_arch_1           db '    __________________', 13, 10, 0
cmd_arch_2           db '   /                  \', 13, 10, 0
cmd_arch_3           db '  |    x86 - 16-bit    |', 13, 10, 0
cmd_arch_4           db '  |      Real Mode     |   Current architecture: [x86] (aka "The Old Guard")', 13, 10, 0
cmd_arch_5           db '   \__________________/', 13, 10, 0
cmd_arch_6           db '  |    A blast from    |   A 16-bit classic, a relic from the golden days of', 13, 10, 0
cmd_arch_7           db '  |    the past, but   |   computing, and still going strong!', 13, 10, 0
cmd_arch_8           db '  |    still running!  |', 13, 10, 0
cmd_arch_9           db '   \__________________/', 13, 10, 0

; Ipaddr Command Related
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

; Build-in Commands Configuration
cmd_cls_flag         db 0                                   ; Screen status (0=dirty,1=clean)
cmd_pwd_user_path    db '/home/', 0                         ; /home/<username>
cmd_pwd_root_path    db '/root', 0                          ; /root
cmd_tty_output       db '/dev/ttyX1', 0
cmd_logout_msg       db 'Returning to login...', 0
cmd_reboot_msg       db 'Rebooting Tiny-DOS...', 0
cmd_shutdown_msg     db 'Goodbye from Tiny-DOS!', 0

; Command string template (for complete verification)
cmd_help_str         db 'help',0
cmd_question_str     db '?',0
cmd_arch_str         db 'arch',0
cmd_cls_str          db 'cls',0
cmd_date_str         db 'date',0
cmd_echo_str         db 'echo',0
cmd_ipaddr_str       db 'ip addr',0
cmd_logout_str       db 'logout',0
cmd_pwd_str          db 'pwd',0
cmd_reboot_str       db 'reboot',0
cmd_shutdown_str     db 'shutdown',0
cmd_tty_str          db 'tty',0
cmd_whoami_str       db 'whoami',0
cmd_zodiacsay_str    db 'zodiacsay',0

; Zodiacsay Command Related
cmd_zodiac_limit     db 12                                  ; Total zodiac signs

; Zodiacsay UI Elements
cmd_zodiac_msg1      db " +------------------------------------+", 13, 10, 0
cmd_zodiac_msg2      db " | ", 0
cmd_zodiac_msg3      db " +------------------------------------+", 13, 10, 0

; 子鼠 - Rat
cmd_zodiac_rat1      db "         \    _  _", 13, 10, 0
cmd_zodiac_rat2      db "          \  (o)(o)----.", 13, 10, 0
cmd_zodiac_rat3      db "              \../ (    )", 13, 10, 0
cmd_zodiac_rat4      db "              m\/m----m''`---.", 13, 10, 0

; 丑牛 - Ox
cmd_zodiac_ox1       db "         \   ^__^", 13, 10, 0
cmd_zodiac_ox2       db "          \  (oo)\_______", 13, 10, 0
cmd_zodiac_ox3       db "             (__)\       )\/\", 13, 10, 0
cmd_zodiac_ox4       db "                 ||----w |", 13, 10, 0
cmd_zodiac_ox5       db "                 ||     ||", 13, 10, 0

; 寅虎 - Tiger
cmd_zodiac_tiger1    db "         \", 13, 10, 0
cmd_zodiac_tiger2    db "          \  ('--..--`)", 13, 10, 0
cmd_zodiac_tiger3    db "             .-- )( --.", 13, 10, 0
cmd_zodiac_tiger4    db "             .-/    \-.", 13, 10, 0
cmd_zodiac_tiger5    db "            ( (  \/  ) )", 13, 10, 0
cmd_zodiac_tiger6    db "             ' '----' '", 13, 10, 0
cmd_zodiac_tiger7    db "                '__'", 13, 10, 0

; 卯兔 - Rabbit
cmd_zodiac_rabbit1   db "         \", 13, 10, 0
cmd_zodiac_rabbit2   db "          \   ((`\ ", 13, 10, 0
cmd_zodiac_rabbit3   db "            ___ \\ '--._", 13, 10, 0
cmd_zodiac_rabbit4   db "         .'`   `'    o  )", 13, 10, 0
cmd_zodiac_rabbit5   db "        /    \   '. __.'", 13, 10, 0
cmd_zodiac_rabbit6   db "       _|    /_  \ \_\_", 13, 10, 0
cmd_zodiac_rabbit7   db "      {_\______\-'\__\_\", 13, 10, 0

; 辰龙 - Dragon
cmd_zodiac_dragon1   db "         \", 13, 10, 0
cmd_zodiac_dragon2   db "     --------o        o--------", 13, 10, 0
cmd_zodiac_dragon3   db "       ----^* \   __ / *^----", 13, 10, 0
cmd_zodiac_dragon4   db "          )/|  \ /  \  |\(", 13, 10, 0
cmd_zodiac_dragon5   db "          /^| ^,V  \ \_|^\\", 13, 10, 0
cmd_zodiac_dragon6   db "                \  /(aa)", 13, 10, 0
cmd_zodiac_dragon7   db "                w,,w", 13, 10, 0
cmd_zodiac_dragon8   db "               `8||8'", 13, 10, 0
cmd_zodiac_dragon9   db "                 {(  ", 13, 10, 0
cmd_zodiac_dragon10  db "                  \\   ", 13, 10, 0
cmd_zodiac_dragon11  db "                   ))", 13, 10, 0
cmd_zodiac_dragon12  db "                  //", 13, 10, 0
cmd_zodiac_dragon13  db "                 //", 13, 10, 0
cmd_zodiac_dragon14  db "                /^\", 13, 10, 0

; 巳蛇 - Snake
cmd_zodiac_snake1    db "         \", 13, 10, 0
cmd_zodiac_snake2    db "       _    _", 13, 10, 0
cmd_zodiac_snake3    db "    ,-(|)--(|)-.", 13, 10, 0
cmd_zodiac_snake4    db "    \_   ..   _/", 13, 10, 0
cmd_zodiac_snake5    db "      \______/", 13, 10, 0
cmd_zodiac_snake6    db "        V  V                ____", 13, 10, 0
cmd_zodiac_snake7    db "        `.^^`.             /^,--`", 13, 10, 0
cmd_zodiac_snake8    db "          \^^\            (^^\", 13, 10, 0
cmd_zodiac_snake9    db "          |^^|      _,._   \^^\", 13, 10, 0
cmd_zodiac_snake10   db "          (^^\    _-'^^^^`. ^^)", 13, 10, 0
cmd_zodiac_snake11   db "          \^^`'^^_^^  `--'", 13, 10, 0
cmd_zodiac_snake12   db "           `.__.-' `_'", 13, 10, 0

; 午马 - Horse
cmd_zodiac_horse1    db "         \", 13, 10, 0
cmd_zodiac_horse2    db "          .  ,", 13, 10, 0
cmd_zodiac_horse3    db "          |\/|", 13, 10, 0
cmd_zodiac_horse4    db "          bd \'n.", 13, 10, 0
cmd_zodiac_horse5    db "         /   _,\'n.___.,--x.", 13, 10, 0
cmd_zodiac_horse6    db "        '\              Y", 13, 10, 0
cmd_zodiac_horse7    db "          ~~    \       L   7|", 13, 10, 0
cmd_zodiac_horse8    db "               H l--'~\\ (||", 13, 10, 0
cmd_zodiac_horse9    db "               H l     H |`'", 13, 10, 0
cmd_zodiac_horse10   db "               H [     H [", 13, 10, 0
cmd_zodiac_horse11   db "          ____//,]____//,]___", 13, 10, 0

; 未羊 - Sheep
cmd_zodiac_sheep1    db "         \", 13, 10, 0
cmd_zodiac_sheep2    db "          __  _", 13, 10, 0
cmd_zodiac_sheep3    db "      .-:'  `; `-.___", 13, 10, 0
cmd_zodiac_sheep4    db "     (_,              )_", 13, 10, 0
cmd_zodiac_sheep5    db "   ,'o\''(               )>", 13, 10, 0
cmd_zodiac_sheep6    db "  (__,-'              _)", 13, 10, 0
cmd_zodiac_sheep7    db "     (               )", 13, 10, 0
cmd_zodiac_sheep8    db "      `-'._.---._.--'", 13, 10, 0
cmd_zodiac_sheep9    db "         |||   |||", 13, 10, 0

; 申猴 - Monkey
cmd_zodiac_monkey1   db "         \", 13, 10, 0
cmd_zodiac_monkey2   db "            __", 13, 10, 0
cmd_zodiac_monkey3   db "       w  c(..)o   (", 13, 10, 0
cmd_zodiac_monkey4   db "        \__(-)    __)", 13, 10, 0
cmd_zodiac_monkey5   db "            /\   (", 13, 10, 0
cmd_zodiac_monkey6   db "           /(_)___)", 13, 10, 0
cmd_zodiac_monkey7   db "           w /|", 13, 10, 0
cmd_zodiac_monkey8   db "            | \\", 13, 10, 0
cmd_zodiac_monkey9   db "            m  m", 13, 10, 0

; 酉鸡 - Rooster
cmd_zodiac_rooster1  db "         \", 13, 10, 0
cmd_zodiac_rooster2  db "     ___//            _______", 13, 10, 0
cmd_zodiac_rooster3  db "    /@_ \            / / / / \ ", 13, 10, 0
cmd_zodiac_rooster4  db "    ~ O\ \_         | /_/_/ //\", 13, 10, 0
cmd_zodiac_rooster5  db "      o \  \_______/// / //_/'''", 13, 10, 0
cmd_zodiac_rooster6  db "         |  \           __/", 13, 10, 0
cmd_zodiac_rooster7  db "          \_ \__________/", 13, 10, 0
cmd_zodiac_rooster8  db "            \___    __/", 13, 10, 0
cmd_zodiac_rooster9  db "                \  /", 13, 10, 0
cmd_zodiac_rooster10 db "                || |", 13, 10, 0
cmd_zodiac_rooster11 db "                || |", 13, 10, 0
cmd_zodiac_rooster12 db "              _/_/|\_", 13, 10, 0

; 戌狗 - Dog
cmd_zodiac_dog1      db "         \", 13, 10, 0
cmd_zodiac_dog2      db "          \          _", 13, 10, 0
cmd_zodiac_dog3      db "           \         \ \", 13, 10, 0
cmd_zodiac_dog4      db "                      \ \", 13, 10, 0
cmd_zodiac_dog5      db "                    ___) )", 13, 10, 0
cmd_zodiac_dog6      db "         ____      /     \", 13, 10, 0
cmd_zodiac_dog7      db "        /   | \--._)     /", 13, 10, 0
cmd_zodiac_dog8      db "      __|uu | |   \   \_ \", 13, 10, 0
cmd_zodiac_dog9      db "     /      | | __ \  /_) \", 13, 10, 0
cmd_zodiac_dog10     db "    (_)_____|_|(____)(_____) ", 13, 10, 0

; 亥猪 - Pig
cmd_zodiac_pig1      db "         \", 13, 10, 0
cmd_zodiac_pig2      db "           ,.", 13, 10, 0
cmd_zodiac_pig3      db "          (_|,.", 13, 10, 0
cmd_zodiac_pig4      db "         ,' /, )_______   _", 13, 10, 0
cmd_zodiac_pig5      db "      __j o``-'        `.'-)'", 13, 10, 0
cmd_zodiac_pig6      db "     ('')                \'", 13, 10, 0
cmd_zodiac_pig7      db "      `-j                |", 13, 10, 0
cmd_zodiac_pig8      db "        `-._(           /", 13, 10, 0
cmd_zodiac_pig9      db "           |_\  |--^.  /", 13, 10, 0
cmd_zodiac_pig10     db "          /_]'|_| /_)_/", 13, 10, 0
cmd_zodiac_pig11     db "             /_]'  /_]' ", 13, 10, 0
