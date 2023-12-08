	.arch armv7-a
	.file	"test.c"
	.text
	.section	.rodata
	.align	2
_str0:
	.ascii	"%d%d%d%d%d\012\000"
	.text
	.align	1
	.global	main
	.arch armv7-a
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	main, %function
main:
	push	{r7, lr}
	sub	sp, sp, #32
	add	r7, sp, #8
	movs	r3, #2
	str	r3, [r7, #4]
	movs	r3, #3
	str	r3, [r7, #8]
	movs	r3, #4
	str	r3, [r7, #12]
	movs	r3, #5
	str	r3, [r7, #16]
	movs	r3, #6
	str	r3, [r7, #20]
	ldr	r3, [r7, #20]
	str	r3, [sp, #4]
	ldr	r3, [r7, #16]
	str	r3, [sp]
	ldr	r3, [r7, #12]
	ldr	r2, [r7, #8]
	ldr	r1, [r7, #4]
	ldr	r0, BRIDGE
PRINT:
	add	r0, pc
	bl	printf(PLT)
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #24
	mov	sp, r7
	pop	{r7, pc}


BRIDGE:
	.word	_str0-(PRINT+4)
	.section	.note.GNU-stack,"",%progbits
