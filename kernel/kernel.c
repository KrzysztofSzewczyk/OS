#define true 1
#define false 0
#include "OS.h"
 
#if defined(__linux__)
#error "Zainstaluj ten crosscompiler..."
#endif
 
#if !defined(__i386__)
#error "Tylko x86!"
#endif

/*Funkcje z LIBC. Kopiowklejka*/

void *memcpy(void *dest, const void *src, size_t count) {
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count) {
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count) {
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str) {
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outb (unsigned short _port, unsigned char _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
void scroll(void) {
    unsigned blank, temp;
    blank = 0x20 | (attrib << 8);
    if(csr_y >= 25) {
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

void move_csr(void) {
    unsigned temp;
    temp = csr_y * 80 + csr_x;
    outb(0x3D4, 14);
    outb(0x3D5, temp >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, temp);
}

void cls() {
    unsigned blank;
    int i;
    blank = 0x20 | (attrib << 8);
    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putchar(unsigned char c) {
    unsigned short *where;
    unsigned att = attrib << 8;
    if(c == 0x08) { /*backspace*/
        if(csr_x != 0) csr_x--;
    }
    else if(c == 0x09) {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if(c == '\r') { /*CR*/
        csr_x = 0;
    }
    else if(c == '\n') { /*LF*/
        csr_x = 0;
        csr_y++;
    }
    else if(c >= ' ') { /*Spacja*/
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }
    if(csr_x >= 80) { /*Kiedy koniec linii*/
        csr_x = 0;
        csr_y++;
    }
    scroll();
    move_csr();
}
void puts(unsigned char *text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        putchar(text[i]);
    }
}
void color(unsigned char forecolor, unsigned char backcolor) {
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}
void initdisplay(void) {
    textmemptr = (unsigned short *)0xB8000;
    cls();
}

void kmain(void) {
	initdisplay();
	puts("Hello, kernel World!\n");
}