
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

#endif