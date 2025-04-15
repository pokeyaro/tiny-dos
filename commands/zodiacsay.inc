global command_zodiacsay

command_zodiacsay:
    call clear

    ; Print command frame
    NEWLINE 2
    ECHO cmd_zodiac_msg1
    ECHO cmd_zodiac_msg2

    mov si, command_buf

; Locates the first space after 'zodiacsay'
.find_space:
    lodsb
    cmp al, 0
    je .done                                   ; Early exit if no args
    cmp al, ' '
    jne .find_space

; Verifies argument opening quote
.find_quote_start:
    lodsb
    cmp al, 0
    je .done
    cmp al, '"'
    jne .find_quote_start

; Prints until closing quote or null
.print_content:
    lodsb
    cmp al, 0
    je .done
    cmp al, '"'
    je .print_continue
    call print_char
    jmp .print_content

.print_continue:
    NEWLINE
    ECHO cmd_zodiac_msg3

    ; Randomly select a zodiac sign
    mov si, cmd_zodiac_limit
    call rand_mod                              ; AL = 0-11

    ; Select the zodiac sign based on the random value
    cmp al, 0
    je .zodiac_rat
    cmp al, 1
    je .zodiac_ox
    cmp al, 2
    je .zodiac_tiger
    cmp al, 3
    je .zodiac_rabbit
    cmp al, 4
    je .zodiac_dragon
    cmp al, 5
    je .zodiac_snake
    cmp al, 6
    je .zodiac_horse
    cmp al, 7
    je .zodiac_sheep
    cmp al, 8
    je .zodiac_monkey
    cmp al, 9
    je .zodiac_rooster
    cmp al, 10
    je .zodiac_dog
    cmp al, 11
    je .zodiac_pig
    jmp .done

.zodiac_rat:
    ; Print an ASCII art of a rat
    ECHO cmd_zodiac_rat1, cmd_zodiac_rat2, cmd_zodiac_rat3, \
         cmd_zodiac_rat4
    jmp .done

.zodiac_ox:
    ; Print an ASCII art of a cow
    ECHO cmd_zodiac_ox1, cmd_zodiac_ox2, cmd_zodiac_ox3, \
         cmd_zodiac_ox4, cmd_zodiac_ox5
    jmp .done

.zodiac_tiger:
    ; Print the ASCII art of a tiger
    ECHO cmd_zodiac_tiger1, cmd_zodiac_tiger2, cmd_zodiac_tiger3, \
         cmd_zodiac_tiger4, cmd_zodiac_tiger5, cmd_zodiac_tiger6, \
         cmd_zodiac_tiger7
    jmp .done

.zodiac_rabbit:
    ; Print the ASCII art of a rabbit
    ECHO cmd_zodiac_rabbit1, cmd_zodiac_rabbit2, cmd_zodiac_rabbit3, \
         cmd_zodiac_rabbit4, cmd_zodiac_rabbit5, cmd_zodiac_rabbit6, \
         cmd_zodiac_rabbit7
    jmp .done

.zodiac_dragon:
    ; Print an ASCII art of a dragon
    ECHO cmd_zodiac_dragon1, cmd_zodiac_dragon2, cmd_zodiac_dragon3, \
         cmd_zodiac_dragon4, cmd_zodiac_dragon5, cmd_zodiac_dragon6, \
         cmd_zodiac_dragon7, cmd_zodiac_dragon8, cmd_zodiac_dragon9, \
         cmd_zodiac_dragon10, cmd_zodiac_dragon11, cmd_zodiac_dragon12, \
         cmd_zodiac_dragon13, cmd_zodiac_dragon14
    jmp .done

.zodiac_snake:
    ; Print an ASCII art of a snake
    ECHO cmd_zodiac_snake1, cmd_zodiac_snake2, cmd_zodiac_snake3, \
         cmd_zodiac_snake4, cmd_zodiac_snake5, cmd_zodiac_snake6, \
         cmd_zodiac_snake7, cmd_zodiac_snake8, cmd_zodiac_snake9, \
         cmd_zodiac_snake10, cmd_zodiac_snake11, cmd_zodiac_snake12
    jmp .done

.zodiac_horse:
    ; Print an ASCII art of a horse
    ECHO cmd_zodiac_horse1, cmd_zodiac_horse2, cmd_zodiac_horse3, \
         cmd_zodiac_horse4, cmd_zodiac_horse5, cmd_zodiac_horse6, \
         cmd_zodiac_horse7, cmd_zodiac_horse8, cmd_zodiac_horse9, \
         cmd_zodiac_horse10, cmd_zodiac_horse11
    jmp .done

.zodiac_sheep:
    ; Print an ASCII art of a sheep
    ECHO cmd_zodiac_sheep1, cmd_zodiac_sheep2, cmd_zodiac_sheep3, \
         cmd_zodiac_sheep4, cmd_zodiac_sheep5, cmd_zodiac_sheep6, \
         cmd_zodiac_sheep7, cmd_zodiac_sheep8, cmd_zodiac_sheep9
    jmp .done

.zodiac_monkey:
    ; Print an ASCII art of a monkey
    ECHO cmd_zodiac_monkey1, cmd_zodiac_monkey2, cmd_zodiac_monkey3, \
         cmd_zodiac_monkey4, cmd_zodiac_monkey5, cmd_zodiac_monkey6, \
         cmd_zodiac_monkey7, cmd_zodiac_monkey8, cmd_zodiac_monkey9
    jmp .done

.zodiac_rooster:
    ; Print an ASCII art of a rooster
    ECHO cmd_zodiac_rooster1, cmd_zodiac_rooster2, cmd_zodiac_rooster3, \
         cmd_zodiac_rooster4, cmd_zodiac_rooster5, cmd_zodiac_rooster6, \
         cmd_zodiac_rooster7, cmd_zodiac_rooster8, cmd_zodiac_rooster9, \
         cmd_zodiac_rooster10, cmd_zodiac_rooster11, cmd_zodiac_rooster12
    jmp .done

.zodiac_dog:
    ; Print an ASCII art of a dog
    ECHO cmd_zodiac_dog1, cmd_zodiac_dog2, cmd_zodiac_dog3, \
         cmd_zodiac_dog4, cmd_zodiac_dog5, cmd_zodiac_dog6, \
         cmd_zodiac_dog7, cmd_zodiac_dog8, cmd_zodiac_dog9, \
         cmd_zodiac_dog10
    jmp .done

.zodiac_pig:
    ; Print an ASCII art of a pig
    ECHO cmd_zodiac_pig1, cmd_zodiac_pig2, cmd_zodiac_pig3, \
         cmd_zodiac_pig4, cmd_zodiac_pig5, cmd_zodiac_pig6, \
         cmd_zodiac_pig7, cmd_zodiac_pig8, cmd_zodiac_pig9, \
         cmd_zodiac_pig10, cmd_zodiac_pig11
    jmp .done

.done:
    NEWLINE
    ret
