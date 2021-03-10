	.arch armv6
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"tercero.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Give me the first operand: \000"
	.align	2
.LC1:
	.ascii	"%d\000"
	.align	2
.LC2:
	.ascii	"Give me the operation to be performed (+, -, *, /):"
	.ascii	" \000"
	.align	2
.LC3:
	.ascii	" %c\000"
	.align	2
.LC4:
	.ascii	"Give me the second operand: \000"
	.global	__aeabi_idiv
	.align	2
.LC5:
	.ascii	"The result of %d %c %d is : %d\012\000"
	.text
	.align	2
	.global	main
	.arch armv6
	.syntax unified
	.arm
	.fpu vfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	mov	r3, #32
	strb	r3, [fp, #-17]
	ldr	r0, .L7
	bl	puts
	sub	r3, fp, #12
	mov	r1, r3
	ldr	r0, .L7+4
	bl	__isoc99_scanf
	ldr	r0, .L7+8
	bl	puts
	sub	r3, fp, #17
	mov	r1, r3
	ldr	r0, .L7+12
	bl	__isoc99_scanf
	ldr	r0, .L7+16
	bl	puts
	sub	r3, fp, #16
	mov	r1, r3
	ldr	r0, .L7+4
	bl	__isoc99_scanf
	ldrb	r3, [fp, #-17]
	cmp	r3, #43
	bne	.L2
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-16]
	add	r3, r2, r3
	str	r3, [fp, #-8]
.L2:
	ldrb	r3, [fp, #-17]
	cmp	r3, #45
	bne	.L3
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-16]
	sub	r3, r2, r3
	str	r3, [fp, #-8]
.L3:
	ldrb	r3, [fp, #-17]
	cmp	r3, #42
	bne	.L4
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-16]
	mul	r3, r2, r3
	str	r3, [fp, #-8]
.L4:
	ldrb	r3, [fp, #-17]
	cmp	r3, #47
	bne	.L5
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-16]
	mov	r1, r2
	mov	r0, r3
	bl	__aeabi_idiv
	mov	r3, r0
	str	r3, [fp, #-8]
.L5:
	ldr	r1, [fp, #-12]
	ldrb	r3, [fp, #-17]
	mov	r0, r3
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-8]
	str	r3, [sp]
	mov	r3, r2
	mov	r2, r0
	ldr	r0, .L7+20
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
.L8:
	.align	2
.L7:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.size	main, .-main
	.ident	"GCC: (Raspbian 8.3.0-6+rpi1) 8.3.0"
	.section	.note.GNU-stack,"",%progbits
