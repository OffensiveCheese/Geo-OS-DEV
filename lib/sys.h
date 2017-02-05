
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef SYS_H
#define SYS_H


extern size_t strlen(const char* str);
extern void update_videoptr(void);
extern void newline(void);
extern void backspace(void);
extern void restrictions_tty(void);
extern void writec(char c, uint8_t bc, uint8_t fc);
extern void writes(const char* c, uint8_t bc, uint8_t fc);
extern void terminal_cls(void);
extern void terminal_init();
extern void lgdt(void);
extern void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
extern void gdt_load(void);
extern void* memset(void* ptr, int val, size_t size);
extern void pushall(void);
extern void popall(void);
extern void iret(void);
extern int default_irq_c_handler(void);
extern int default_isr_handler(void);
extern int default_irq_handler(void);
extern void lidt(uintptr_t base, size_t limit);
extern void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);
extern void idt_flush(void);
extern void idt_start(void);
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t val);
extern void iow(void);
extern void irq_clear_mask(unsigned char i);
extern void pic_remap_w(int o1, int o2);
extern void pic_remap(void);
#endif