	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.section .rodata
	.global a
	.align 4
	.size a, 4
a:
	.word 10
	.text
	.global main
	.type main , %function
main:
	push {r9, r10, fp, lr}
	mov fp, sp
	sub sp, sp, #0
.L2:
	ldr r10, addr_a0
	ldr r9, [r10]
	mov r0, r9
	add sp, sp, #0
	pop {r9, r10, fp, lr}
	bx lr

addr_a0:
	.word a
