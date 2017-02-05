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
popall:
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
iret:
	iret

default_isr_handler:
	jmp pushall
	jmp popall
	jmp iret
	ret
default_irq_handler:
	jmp pushall
	call default_irq_c_handler
	jmp popall
	jmp iret
	ret

idt_flush:
	lidt idtptr
	ret
