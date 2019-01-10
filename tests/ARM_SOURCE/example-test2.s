.global main
.text
	nop
main:
	bl suite
	bl main
	bl test
	b suite
	b main
	b test
	nop
suite:
	mov pc, lr
.data
	.skip 8
test:
	.word test
	.hword suite
	.byte 0x0
	.align 4
fin:
	.word 0x0
vide:
