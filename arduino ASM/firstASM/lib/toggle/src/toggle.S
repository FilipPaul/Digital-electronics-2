.global toggle

toggle:
  ldi r16, 0x2 ;writinig into general purpose registorers above 15
  sts 0x24, r16
  ldi r17, 0x0 ;writinig into general purpose registorers above 15

subrutine:
  sts 0x25, r16
  nop
  nop
  sts 0x25, r17
rjmp subrutine
