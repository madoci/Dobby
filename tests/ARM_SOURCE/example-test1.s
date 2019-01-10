.global main
.global data_global
.text
	nop
main:
	bl data_local
	bl data_global
	b data_local
	b data_global
	bl suite
	bl main
	b suite
	b main
	bl test
	b test
	nop
suite:
	mov pc, lr
.ltorg
	.word suite
	.word main
	.word data_local
	.word data_global
.data
	.skip 8
data_local:
	.word suite
	.word main
	.word data_local
	.word data_global
test:
	.hword test
	.hword suite
	.hword fin
	.align 4
data_global:
	bl data_local
	bl data_global
	b data_local
	b data_global
	bl suite
	bl main
	b suite
	b main
fin:
	.word 0x0
