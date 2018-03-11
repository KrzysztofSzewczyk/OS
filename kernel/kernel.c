
#include "OS.h"

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