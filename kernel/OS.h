#ifndef _OS_H
#define _OS_H

typedef int size_t;
struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};
struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));
struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, char val, size_t count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
size_t strlen(const char *str);
unsigned char inb (unsigned short _port);
void outb (unsigned short _port, unsigned char _data);
int atoi(register char *string);
void handle_timer(struct regs *r);
void timer_wait(int ticks);
void timer_install(void);
char scancodeToCharacter (char scancode);
char getScancode(void);
void scroll(void);
void move_csr(void);
void cls();
void putchar(unsigned char c);
void puts(unsigned char *text);
void color(unsigned char forecolor, unsigned char backcolor);
void initdisplay(void);
int time(void);
#endif
