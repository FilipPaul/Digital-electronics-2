#include <stdio.h>         // AVR device-specific IO definitions
#include <stdlib.h>        // C library. Needed for conversion function
#ifdef __ASSEMBLER__

.global toggle

#endif

#ifndef __ASSEMBLER__

extern "C" void toggle();

#endif