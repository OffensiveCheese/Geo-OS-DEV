.global pushall
.global popall
.global iret
.global default_isr_handler
.global default_irq_handler
.global default_kb_handler
.global idt_flush
.extern idtptr
.extern default_irq_c_handler

pushall:
	pusha
	pushl %ds
	pushl %es
	ret
popall:
	popl %es
	popl %ds
	popa
	ret
iret:
	iret
	ret

default_isr_handler:
	pusha
	pushl %ds
	pushl %es
	popl %es
	popl %ds
	popa
	iret
	ret
default_irq_handler:
	pusha
	pushl %ds
	pushl %es
	call default_irq_c_handler
	popl %es
	popl %ds
	popa
	iret
	ret
default_kb_handler:
	pusha
	pushl %ds
	pushl %es
	call default_kb_c_handler
	popl %ds
	popl %es
	popa
	iret
	ret

idt_flush:
	lidt idtptr
	ret
