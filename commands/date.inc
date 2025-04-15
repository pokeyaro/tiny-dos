global command_date

command_date:
    call read_cmos_datetime                    ; Reads CMOS/RTC time
    call format_datetime_string                ; Converts to "YYYY-MM-DD HH:MM:SS"
    NEWLINE
    ECHO datetime_str
    ret
