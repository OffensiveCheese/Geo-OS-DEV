
.set ALIGN, 	1<<0 # Align loaded modules on the page boundaries.
.set MEMINFO, 	1<<1 # Provide our memory map.
.set FLAGS, 	ALIGN | MEMINFO # Make the multiboot flag field.
.set MAGIC, 	0x1BADB002 # The 'magic number' lets GRUB find the header.
.set CHECKSUM, 	-(MAGIC + FLAGS) # Prove we are multiboot.

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# We need the first 8 KiB of our kernel to be MAGIC, FLAGS and CHECKSUM, in order for GRUB to check.

.section .bss
.align 16
stack_bottom:
.skip 16384 # Bring the stack back up.
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	subl $6, %esp
	movw size_of_gdt_minus_one, %cx
	movw %cx, 0(%esp)
	movl $gdt, %ecx
	movl $ecx, 2(%esp)
	lgdt 0(%esp)
	addl $6, %esp
	push $0x08
	push $1f
	retf
	movw $0x10, %cx
	movw %cx, %ds
	movw %cx, %es
	movw %cx, %fs
	movw %cx, %gs
	movw %cx, %ss
	# Hooray! We're in our .text function! Let's call our kernel.
	# C and C++ need a stack to function, so we'll need to set up the stack.
	mov $stack_top, %esp	
	# We're done! Call our high-level kmain.
	call kmain
	# If the kernel exits itself, we should make a barrier for the CPU so we don't run into garbage.
	cli
	1: hlt
	jmp 1b
	
# Set the size of the _start symbol.

.size _start, . - _start

