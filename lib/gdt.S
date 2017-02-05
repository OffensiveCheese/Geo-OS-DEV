.extern gdtp
.global lgdt

.section .text

lgdt:
	lgdt gdtp
	ljmp $0x08,$code_segm
code_segm:
	mov $0x10, %eax
	mov %eax, %ds
	mov %eax, %es
	mov %eax, %fs
	mov %eax, %gs
	mov %eax, %ss
	ret

