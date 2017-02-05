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
	writes("Can you hear me?\n", 0, 15);
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
	idtptr.limit = (uint16_t)((sizeof(struct idt_table) * 256) - 1); // Set the limit
	idtptr.base = (uint32_t)&idt; // Set the base
	memset(&idt, 0, (sizeof(idt) - 1)); // Clear the IDT space
	idt_set_gate(0, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(1, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(2, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(3, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(6, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(8, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(16, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(24, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(30, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(31, (unsigned)default_isr_handler, 0x08, 0x8E);
	idt_set_gate(32, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)default_irq_handler, 0x08, 0x8E);
	idt_flush();
}