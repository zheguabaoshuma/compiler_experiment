
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%f %f %f %f\012\000"
	.text
	.align	1
	.global	main
	.type	main, %function
main:
	push	{r7, lr}
	sub	sp, sp, #72
	add	r7, sp, #24
	mov	r2, #0
	mov	r3, #0
	movt	r3, 16400
	strd	r2, [r7]
	mov	r2, #0
	mov	r3, #1073741824
	strd	r2, [r7, #8]
	vldr.64	d6, [r7]
	vldr.64	d7, [r7, #8]
	vadd.f64	d7, d6, d7
	vstr.64	d7, [r7, #16]
	vldr.64	d6, [r7]
	vldr.64	d7, [r7, #8]
	vsub.f64	d7, d6, d7
	vstr.64	d7, [r7, #24]
	vldr.64	d6, [r7]
	vldr.64	d7, [r7, #8]
	vmul.f64	d7, d6, d7
	vstr.64	d7, [r7, #32]
	vldr.64	d5, [r7]
	vldr.64	d6, [r7, #8]
	vdiv.f64	d7, d5, d6
	vstr.64	d7, [r7, #40]
	ldrd	r2, [r7, #40]
	strd	r2, [sp, #16]
	ldrd	r2, [r7, #32]
	strd	r2, [sp, #8]
	ldrd	r2, [r7, #24]
	strd	r2, [sp]
	ldrd	r2, [r7, #16]
	ldr	r1, .L3
.LPIC0:
	add	r1, pc
	mov	r0, r1
	bl	printf(PLT)
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #48
	mov	sp, r7
	pop	{r7, pc}
.L4:
	.align	2
.L3:
	.word	.LC0-(.LPIC0+4)
	.section	.note.GNU-stack,"",%progbits
