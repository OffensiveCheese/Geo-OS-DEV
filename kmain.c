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
	writes("Test\n", 0, 15);
	gdt_load();
}