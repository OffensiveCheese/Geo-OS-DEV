#include "sys.h"

struct gdt_table {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_medium;
	uint8_t access;
	uint8_t flags;
	uint8_t base_high;
} __attribute__ ((packed));

struct gdtr {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct gdt_table gdt[5];
struct gdtr gdtp;

extern void lgdt(void);

void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].base_low = ((base >> 0) & 0xFFFF);
	gdt[num].base_medium = ((base >> 16) & 0xFF);
	gdt[num].access = (access & 0xFF);
	gdt[num].flags = (((limit >> 16) & 0x0F) | (flags & 0xF0));
	gdt[num].base_high = ((base >> 24) & 0xFF);
}


void gdt_load(void) {
	gdtp.limit = (sizeof(struct gdt_table) * 5) - 1;
	gdtp.base = (uint32_t)&gdt;
	gdt_set_entry(0, 0, 0, 0, 0); // Null descriptor.
	gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code Segment.
	gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data Segment.
	gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Usermode Code Segment.
	gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Usermode Data Segment.
	lgdt();
}

uint16_t size_of_gdt_minus_one = sizeof(gdt) - 1;