#include "sys.h"

extern void pushall(void);
extern void popall(void);
extern void iret(void);

struct idt_table {
	uint16_t base_low;
	uint16_t selector;
	uint8_t unused;
	uint8_t flags;
	uint16_t base_high;
} __attribute__ ((packed));

struct idtr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct idt_table idt[256];
struct idtr idtptr;

int default_irq_c_handler(void) {
	__asm__ volatile ("outb %0, %1" : : "a"((uint8_t)0x20), "Nd"((uint16_t)0x20) );
	return 0;
}

extern int default_isr_handler(void);
extern int default_irq_handler(void);


void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
	idt[num].base_low = (base >> 0) & 0xFFFF;
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].selector = selector;
	idt[num].unused = 0;
	idt[num].flags = flags;
}

extern void idt_flush(void);

void idt_start(void) {
	idtptr.limit = (sizeof(struct idt_table) * 256) - 1;
	idtptr.base = (uint32_t)&idt;
	memset(&idt, 0, (sizeof(idt) - 1));
	for (size_t i = 0; i < 32; i++) {
		idt_set_gate(i, (unsigned)default_isr_handler, 0x08, 0x8E);
	}
	for (size_t i = 32; i < 48; i++) {
		idt_set_gate(i, (unsigned)default_irq_handler, 0x08, 0x8E);
	}
	
}