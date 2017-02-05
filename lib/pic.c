#include "sys.h"

uint8_t inb(uint16_t port) {
	uint8_t returnv;
	__asm__ __volatile__ ("inb %1, %0" : "=a"(returnv) : "Nd"(port) );
	return returnv;
}

void outb(uint16_t port, uint8_t val) {
	__asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port) );
}

void iow(void) {
	__asm__ volatile ("jmp 1f\n\t"
			"1:jmp 2f\n\t"
			"2:");
}

void irq_clear_mask(unsigned char i) {
	uint16_t p;
	uint8_t v;
	if (i < 8) { p = 0x21; } else { p = 0xA1; i -= 8; }
	v = inb(p) & ~(1 << i);
	outb(p, v);
}

void pic_remap_w(int o1, int o2) {
	unsigned char a1, a2;
	a1 = inb(0x21);
	a2 = inb(0xA1);
	outb(0x20, 0x11); iow();
	outb(0xA0, 0x11); iow();
	outb(0x21, o1); iow();
	outb(0xA1, o2); iow();
	outb(0x21, 4); iow();
	outb(0xA1, 2); iow();
	outb(0x21, 0x01); iow();
	outb(0xA1, 0x01); iow();
	outb(0x21, a1); iow();
	outb(0xA1, a2); iow();
}

void pic_remap(void) {
	pic_remap_w(0x20, 0x28);
	irq_clear_mask(0x21);
	
}

