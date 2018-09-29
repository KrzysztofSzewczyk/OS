
#include "OS.h"

void reboot(void) {
    char good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
}

void kmain(void) {
	initdisplay();
	puts("Working!\n");
}
