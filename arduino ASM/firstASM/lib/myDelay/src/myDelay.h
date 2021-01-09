#include <stdio.h>         // AVR device-specific IO definitions
#include <stdlib.h>        // C library. Needed for conversion function
#ifdef __ASSEMBLER__

.global myDelay

#endif

#ifndef __ASSEMBLER__

extern "C" void mysDelay(uint8_t us);

#endif