	.text
	.align	2
	.global	main
	.type	main, %function
main:
	str	fp, [sp, #-4]!
	add	fp, sp, #0			@;控制堆栈指针
	sub	sp, sp, #20
	mov	r3, #0
	str	r3, [fp, #-20]		@*(fp-20) = 0	a
	mov	r3, #1
	str	r3, [fp, #-16]		@*(fp-16) = 1	b
	mov	r3, #0
	str	r3, [fp, #-8]		@*(fp-8) = 0	i
	b	.L2

.L1:
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-20]
	add	r3, r2, r3			
	str	r3, [fp, #-16]		@*(fp-16) = a + b
	ldr	r2, [fp, #-16]		
	ldr	r3, [fp, #-20]
	rsb	r3, r3, r2			
	str	r3, [fp, #-20]		@*(fp-20) = b - a
	ldr	r3, [fp, #-8]
	add	r3, r3, #1			@ i ++
	str	r3, [fp, #-8]

.L2:
	ldr	r3, [fp, #-8]
	cmp	r3, #9				@i <= 9 ?
	ble	.L1					@branch less equal
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-12]		@*(fp-12) = b
	mov	r3, #0
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}		@pop
	bx	lr
	.section	.note.GNU-stack,"",%progbits
