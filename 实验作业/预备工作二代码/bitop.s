	.section	.rodata
	.align	2   @2^2,即4字节对齐,以.开头的是伪指令，具有编译器相关，平台无关性
.LC0:
	.ascii	"%d %d %d\012\000" @printf \012 means \n, \000 means null char 
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stmfd	sp!, {fp, lr}   @入栈，分别存储fp，lr到sp，sp-4；sp=sp-4;
	add	fp, sp, #4
	sub	sp, sp, #24
	mov	r3, #123
	str	r3, [fp, #-24]
	mov	r3, #456
	str	r3, [fp, #-20]
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-20]
	orr	r3, r2, r3  @或运算
	str	r3, [fp, #-16]
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-20]
	and	r3, r2, r3  @与运算
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-24]
	mvn	r3, r3      @取反
	str	r3, [fp, #-8]
	movw	r3, #:lower16:.LC0  @MOVW  把 16 位立即数放到寄存器的底16位
	movt	r3, #:upper16:.LC0  @MOVT  把 16 位立即数放到寄存器的高16位
    @movw和movt的作用为：r3 = (movt #:upper16:.LC0 << 16) | (movw #:lower16:.LC0)
	mov	r0, r3
    
	ldr	r1, [fp, #-16]
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-8]
	bl	printf  @默认打印r0开始的寄存器内容
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}@出栈

