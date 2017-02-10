#include <stdbool.h>
#include <stddef.h> 
#include <stdint.h>


#if defined(__linux__) // We do not want a non-cross-compiler-compiler...
#error "You are not using a cross-compiler."
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler."
#endif 

#include "lib/sys.h"

void kmain(void) {
	terminal_init();
	gdt_load();
	idt_start();
	pic_remap();
	__asm__ __volatile__ ("sti");
	__asm__ __volatile__ ("int $0x10");
	zero_string(command);
	writes(">", 0, 15);
	for(;;);
}