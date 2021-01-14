.global main

main:
ldi r16, 0b11011111 ; DDRD
sts 0x2A, r16 ;DDRD -> pin 5 input other output
ldi r17,  0b00100000; all outputs HIGH, pin 5 input pull up
sts 0x2B, r17 ; PORT D

loop:
;mov r19, r17
lds r18,0x29 ;PIN D to r18
BST r18, 5 ;--> copy 5th bit to T flag
BLD r19, 0;put T to the  reg 19 on possition 0
BRTS off ; if T flag = 

lds r18 , 0x2B
neg r19
and r19, r18
;eor r19, r18
sts 0x2B, r19
rjmp loop

off:
or r19, r18
sts 0x2B, r19
rjmp loop



