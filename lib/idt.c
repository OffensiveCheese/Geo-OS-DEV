#include "sys.h"


struct idt_table {
	uint16_t base_low;
	uint16_t selector;
	uint8_t unused;
	uint8_t flags;
	uint16_t base_high;
} __attribute__ ((packed));

struct idt_table idt[256];

int default_isr_handler(void) {
	__asm__ volatile ("pusha; pushl %ebp; pushl %esi; pushl %edi; pushl %ds; pushl %es; pushl %fs; pushl %gs ");
	writes("isr\n", 0, 15);
	__asm__ volatile ("popl %gs; popl %fs; popl %es; popl %ds; popl %edi; popl %esi; popl %ebp; popa");
	__asm__ volatile ("iret");
	return 0;
}

int default_irq_handler(void) {
	__asm__ volatile ("pusha; pushl %ebp; pushl %esi; pushl %edi; pushl %ds; pushl %es; pushl %fs; pushl %gs ");
	writes("irq\n", 0, 15);
	__asm__ volatile ("outb %0, %1" : : "a"((uint8_t)0x20), "Nd"((uint16_t)0x20) );
	__asm__ volatile ("popl %gs; popl %fs; popl %es; popl %ds; popl %edi; popl %esi; popl %ebp; popa");
	__asm__ volatile ("iret");
	return 0;
}


void lidt(uintptr_t base, size_t limit) {
	__asm__ __volatile__ ("subl $6, %%esp\n\t"
				"movw %w0, 0(%%esp)\n\t"
				"movl %1, 2(%%esp)\n\t"
				"lidt (%%esp)\n\t"
				"addl $6, %%esp" : : "rN"(limit), "r"(base) );
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
	idt[num].base_low = (base >> 0) & 0xFFFF;
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].selector = selector;
	idt[num].unused = 0;
	idt[num].flags = flags;
}

void idt_start(void) {
	memset(&idt, 0, sizeof(idt));
	for (size_t i = 0; i < 32; i++) {
		idt_set_gate(i, (unsigned)default_isr_handler, 0x08, 0x8E);
	}
	for (size_t i = 32; i < 48; i++) {
		idt_set_gate(i, (unsigned)default_irq_handler, 0x08, 0x8E);
	}
	lidt((uintptr_t)idt, ((sizeof(idt)) - 1));
}