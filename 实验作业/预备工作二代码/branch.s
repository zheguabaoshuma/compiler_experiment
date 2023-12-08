	.arch armv7-a
	.text
	.section	.rodata
	.align	2
_str0:
	.ascii	"k=%d\012\000"
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
	sub	sp, sp, #16
	add	r7, sp, #0
	movs	r3, #0
	str	r3, [r7, #4]
	b	.WHILE1_COND
.WHILE1_LOOP:
	adds	r3, r3, #1
.WHILE1_COND:                     @i<10
	cmp	r3, #10
	str r3, [r7, #4]
	ble	.WHILE1_LOOP
	movs	r3, #0                @while1 end
	str	r3, [r7, #8]
.WHILE2_LOOP:
	adds	r3, r3, #1
	cmp	r3, #20
	str r3, [r7, #8]
	ble	.WHILE2_LOOP
	ldr	r2, [r7, #4]         @i
	ldr	r3, [r7, #8]         @j
	cmp	r2, r3
	bge	.Ibigger      
	movs	r3, #20
	str	r3, [r7, #12]
	b	.Jbigger
.Ibigger:
	movs	r3, #10
	str	r3, [r7, #12]
.Jbigger:
	ldr	r1, [r7, #12]
	ldr	r3, BRIDGE
PRINT:
	add	r3, pc
	mov	r0, r3
	bl	printf(PLT)
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #16
	mov	sp, r7
	pop	{r7, pc}
BRIDGE:
	.word	_str0-(PRINT+4)
	.section	.note.GNU-stack,"",%progbits
