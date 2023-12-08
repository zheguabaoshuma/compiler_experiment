	ldr	r2, .BRIDGE
.START:
	add	r2, pc, r2		@get arr's addr
	ldr	r3, .BRIDGE+4	
	ldr	r3, [r2, r3]
	ldr	r3, [r3]
	str	r3, [fp, #-8]
	@ init for loop expr1
	b	.COND
.LOOP_BODY:
	@...
.COND:
	cmp	@...
	ble	.LOOP_BODY
	bl .CHECK_STACK
.CHECK_STACK:
	@...
	eors	r1, r2, r1
	beq	.END
	bl	__stack_chk_fail
.END:
	@POP STACK

.BRIDGE:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC0+8)
	.word	__stack_chk_guard(GOT)
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC1+8)
