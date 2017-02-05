.global pushall
.global popall
.global iret
.global default_isr_handler
.global default_irq_handler
.global idt_flush
.extern idtptr
.extern default_irq_c_handler

pushall:
	pusha
	pushl %ebp
	pushl %esi
	pushl %edi
	pushl %ds
	pushl %es
	ret
popall:
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
	ret
iret:
	iret
	ret

default_isr_handler:
	pusha
	pushl %ebp
	pushl %esi
	pushl %edi
	pushl %ds
	pushl %es
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
	iret
	ret
default_irq_handler:
	pusha
	pushl %ebp
	pushl %esi
	pushl %edi
	pushl %ds
	pushl %es
	call default_irq_c_handler
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
	iret
	ret

idt_flush:
	lidt idtptr
	ret
