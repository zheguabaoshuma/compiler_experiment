	.arch armv7-a
@strs
	.text
	.section	.rodata
	.align	2
_str0:
	.ascii	"op1==op2\000"
	.align	2
_str1:
	.ascii	"op1!=op2\000"
	.align	2
_str2:
	.ascii	"op1>op2\000"
	.align	2
_str3:
	.ascii	"op1<=op2\000"
	.align	2
_str4:
	.ascii	"op1>=op2\000"
	.align	2
_str5:
	.ascii	"op1<op2\000"
	.align	2
_str6:
	.ascii	"unsigned op1>=op2\000"
	.align	2
_str7:
	.ascii	"unsigned op1<op2\000"
	.align	2
_str8:
	.ascii	"and:%d\012or:%d\012not:%d\012\000"
@main
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
	sub	sp, sp, #24
	add	r7, sp, #0
	mvn	r2, #1             @r2=-2
	str	r2, [r7, #4]
	movs	r3, #3         @r3=3
	str	r3, [r7, #8]
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #8]
	cmp	r2, r3
	bne	.NOTEQ                @r2!=r3
	ldr	r3, .BRIDGE
.EQ:                    
	add	r3, pc 
	mov	r0, r3
	bl	puts(PLT)             @r2==r3
.NOTEQ:
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #8]
	cmp	r2, r3
	beq	.BT
	ldr	r3, .BRIDGE+4
.NOTEQP:                      @not eq, print
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
.BT:
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #8]
	cmp	r2, r3
	ble	.LTE                    @r2<=r3
	ldr	r3, .BRIDGE+8
.BTP:
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
	b	.LT
.LTE:
	ldr	r3, .BRIDGE+12
.LTEP:
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
.LT:
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #8]
	cmp	r2, r3
	blt	.BTE
	ldr	r3, .BRIDGE+16
.LTP:
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
	b	.ULT
.BTE:
	ldr	r3, .BRIDGE+20            @str5
.BTEP:
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
.ULT:
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #8]
	cmp	r2, r3
	bcc	.UBTE
	ldr	r3, .BRIDGE+24            @str6
.ULTP:
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
	b	.ANDORNOT
.UBTE:
	ldr	r3, .BRIDGE+28            @str7
.UBTEP:                           @unsigned bigger than equal print
	add	r3, pc
	mov	r0, r3
	bl	puts(PLT)
.ANDORNOT:
	ldr r2, [r7, #4]
	ldr r3, [r7, #4]
	AND r1, r2, r3
	str r1, [r7, #12]
	ORR r1, r2, r3
	str r1, [r7, #16]
	cmp r1, #0
	beq .EQ0
	mov r1, #1
.EQ0:
	mov r1, #0
	b 	.ANDORNOTP
.ANDORNOTP:
	str r1, [r7, #20]
	ldr	r3, [r7, #20]         @not_res
	ldr	r2, [r7, #16]         @or_res
	ldr	r1, [r7, #12]         @and_res
	ldr	r0, .BRIDGE+32
.LOGIC:
	add	r0, pc
	bl	printf(PLT)
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #24
	mov	sp, r7
	pop	{r7, pc}

	.align	2
.BRIDGE:
	.word	_str0-(.EQ+4)
	.word	_str1-(.NOTEQP+4)
	.word	_str2-(.BTP+4)
	.word	_str3-(.LTEP+4)
	.word	_str4-(.LTP+4)
	.word	_str5-(.BTEP+4)
	.word	_str6-(.ULTP+4)
	.word	_str7-(.UBTEP+4)
	.word	_str8-(.LOGIC+4)
	.section	.note.GNU-stack,"",%progbits
