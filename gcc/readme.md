# stdio on samd51

There are a lot of ways of communicating over serial on a small microcontroller. Newlib and Nano are viable options but they can use quite a bit memory. I found the printf-stdarg.c from FreeRTOS by Georges Menie to work well and use that. It is in the FreeRTOS www.freertos.org Labs download.
You use stdio.h from gcc and compile with printf-stdarg.c. The only dependency is the call to print a character. 

Nice idea but gcc sometimes helps out by turning a argumentless printf into a puts. You end up with a lot of unresolved references. There are some interesting hooks to resolve this. 

1) Add a macro define of __CUSTOM_FILE_IO__ to gcc compile options. (-D__CUSTOM_FILE_IO__) 
This will cause gcc to pull in sys/custom_file.h rather than it's usual large FILE descriptor. I've added a simple sys/custom_file.h in the gcc folder for this. It also needs the -isystem ${INITMAKER}/gcc in order to for stdio.h to find the file. 

2) This uses link wrap command to substitute code for putc, getc, fgets, fputs, and putchar for linking. The link options should add:

`-Wl,-wrap=puts -Wl,-wrap=putc -Wl,-wrap=getc -Wl,-wrap=fgets -Wl,-wrap=fputs -Wl,-wrap=putchar`

The link wrap functions are found in the usart.c in samd5x directory and must be compiled with the project. They provide simple blocking functions for both UART and for SWO. 

The source that use puts, putc, getc, fgets, fputs, putchar and printf must `#include <stdio.h>` and `#include "usart.h"`. Also it is recommended to assign the variables stdin, stdout, and stderr to the FILE pointers: COM0-COM5 or SWO0-SWO7 before they are used. There are 6 predefined FILE descriptors for SERCOM0 to SERCOM5 defined as COM0 through COM5. There is also 8 predefined FILE descriptors for single wire output channels 0 through 7 defined as SWO0 to SWO7.

This is a small simple mechanism. It does not support file IO and is single threaded blocking routines. Mostly I have this for test programs and debugging.