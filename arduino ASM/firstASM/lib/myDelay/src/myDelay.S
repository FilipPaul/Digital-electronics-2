.global mysDelay

mysDelay:
mov r19, r24
ldi r18, 0x1 ;init reg 18
ldi r16, 0x2 ;register to update pin
ldi r17, 0x2 ;register to toggle


state:
sts 0x25,r16;2 write to bit 
ndelays:
dec r19 ;1
brne delay1 ;0.5
mov r19, r24; 1
EOR r16,r17;1 toggle r16
RJMP state;2 

; call this 1us n times from r24

delay1: 
    dec r18;1 --> r24 
    brne delay1;0.5 
    ldi r18, 0x1 ;1 
RJMP ndelays;2