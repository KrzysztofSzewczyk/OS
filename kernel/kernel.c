#define true 1
#define false 0
#include "OS.h"
 
#if defined(__linux__)
#error "Please get crosscompiler - i686 elf tools"
#endif
 
#if !defined(__i386__)
#error "Only x86!"
#endif

void reboot(void) {
    char good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    for(;;);
}

void kmain(void) {
	initdisplay();
	puts("They see me runnin', they hatin'!\n");
}