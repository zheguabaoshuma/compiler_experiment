	.text
	.global	__aeabi_idiv
	.align	1
	.global	main
	.type	main, %function
main:
	push	{r7, lr}
	sub	sp, sp, #24		@sp压栈
	add	r7, sp, #0		@r7->sp
	movs	r3, #1		@r3 load 1
	str	r3, [r7]		@*r7->r3
	movs	r3, #2		@r3 load 2
	str	r3, [r7, #4]	@*(r7+4)->2
	ldr	r2, [r7]		@*r2->1
	ldr	r3, [r7, #4]	@*r3->2
	add	r3, r3, r2		@add
	str	r3, [r7, #8]	@store *r3
	ldr	r2, [r7]		@*r2->1
	ldr	r3, [r7, #4]	@*r3->2
	subs	r3, r2, r3	@sub
	str	r3, [r7, #12]
	ldr	r3, [r7]
	ldr	r2, [r7, #4]
	mul	r3, r2, r3		@mul
	str	r3, [r7, #16]
	ldr	r1, [r7, #4]
	ldr	r0, [r7]
	bl	__aeabi_idiv(PLT)	@arm内核不支持除法,使用gcc除法库
	mov	r3, r0
	str	r3, [r7, #20]
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #24
	mov	sp, r7			
	pop	{r7, pc}		@release stack
	.section	.note.GNU-stack,"",%progbits
