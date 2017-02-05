.global pushall
.global popall
.global iret
.global idt_flush
.extern idtptr

pushall:
	pusha
	pushl %ebp
	pushl %esi
	pushl %edi
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	ret
popall:
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
	ret
iret:
	iret
	ret

idt_flush:
	lidt idtptr
	ret