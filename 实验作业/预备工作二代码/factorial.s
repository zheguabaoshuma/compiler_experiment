	.arch armv7-a
	.file	"test.c"
	.section	.rodata
@str
	.align	2
_str0:
	.ascii	"%d\000"
	.align	2
_str1:
	.ascii	"f=%d\012\000"
@factorial function	
	.text
	.align	1
	.global	factorial
	.arch armv7-a
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	factorial, %function
factorial:
	push	{r7}
	sub	sp, sp, #20         @for i, n, f
	add	r7, sp, #0          @r7=sp
	str	r0, [r7, #4]        @store n
	movs	r3, #2          @int i = 2
	str	r3, [r7, #8]        @store i
	movs	r3, #1          @int f = 1
	str	r3, [r7, #12]       @store f
	b	.WHILE_COND         @jump condition
.WHILE_LOOP:
	ldr	r3, [r7, #12]       @f
	ldr	r2, [r7, #8]        @i
	mul	r3, r2, r3          @f*=i
	str	r3, [r7, #12]       @store f
	adds	r2, r2, #1      @i+=1
	str	r2, [r7, #8]        @store i
.WHILE_COND:
	ldr	r2, [r7, #8]        @i
	ldr	r3, [r7, #4]        @n
	cmp	r2, r3              @i - n
	ble	.WHILE_LOOP         @i<=n
@ENDofLOOP
	ldr	r3, [r7, #12]       @store f
	mov	r0, r3              @return r0 = f
	adds	r7, r7, #20     @restore sp
	mov	sp, r7
	ldr	r7, [sp], #4        @pop return address
	bx	lr                  @return
@main function
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	main, %function
main:
	push	{r7, lr}
	sub	sp, sp, #16           @for n
	add	r7, sp, #0            @r7=sp
	ldr	r2, .BRIDGE           @GOT
.CHECK0:
	add	r2, pc                @r2=GOT
	ldr	r3, .BRIDGE+4         @stack_check
	ldr	r3, [r2, r3]          @r3=GOT+offset, r2=r2+r3
	ldr	r4, [r3]              
	str	r4, [r7, #12]         @stack_check push
	mov	r3,#0
	adds	r3, r7, #4        @r3=r7+4,n
	mov	r1, r3                @r1=r3
	ldr	r3, .BRIDGE+8         @"%d"
.SCANF:
	add	r3, pc
	mov	r0, r3                @"%d"
	bl	__isoc99_scanf(PLT)
	ldr	r4, [r7, #4]          @n          
	mov	r0, r4                @r0=n
	bl	factorial(PLT)
	str	r0, [r7, #8]          @f
	ldr	r1, [r7, #8]          @f as second param in prinf
	ldr	r3, .BRIDGE+12
.PRINT:
	add	r3, pc
	mov	r0, r3
	bl	printf(PLT)
	movs	r3, #0            @r3=0
	ldr	r1, .BRIDGE+16        @GOT
.CHECK:
	add	r1, pc
	ldr	r2, .BRIDGE+4         
	ldr	r2, [r1, r2]
	ldr	r1, [r2]              @stack_check
	ldr	r2, [r7, #12]
	eors	r1, r2, r1
	mov	r2, #0
	beq	.END
	bl	__stack_chk_fail(PLT)
.END:
	mov	r0, r3
	adds	r7, r7, #16       @restore stack
	mov	sp, r7
	pop	{r7, pc}

	.align	2
.BRIDGE:
	.word	_GLOBAL_OFFSET_TABLE_-(.CHECK0+4)
	.word	__stack_chk_guard(GOT)
	.word	_str0-(.SCANF+4)
	.word	_str1-(.PRINT+4)
	.word	_GLOBAL_OFFSET_TABLE_-(.CHECK+4)
	.section	.note.GNU-stack,"",%progbits
