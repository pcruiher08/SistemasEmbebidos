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
	.file	"quinto.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Give me the x: \000"
	.align	2
.LC1:
	.ascii	"%d\000"
	.align	2
.LC2:
	.ascii	"The result of 6*%d^2+9*%d+2 is : %d\012\000"
	.text
	.align	2
	.global	main
	.arch armv6
	.syntax unified
	.arm
	.fpu vfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	ldr	r0, .L3
	bl	puts
	sub	r3, fp, #8
	mov	r1, r3
	ldr	r0, .L3+4
	bl	__isoc99_scanf
	ldr	r1, [fp, #-8]
	ldr	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-8]
	mul	r2, r2, r3
	mov	r3, r2
	lsl	r3, r3, #1
	add	r3, r3, r2
	lsl	r3, r3, #1
	mov	ip, r3
	ldr	r2, [fp, #-8]
	mov	r3, r2
	lsl	r3, r3, #3
	add	r3, r3, r2
	add	r3, ip, r3
	add	r3, r3, #2
	mov	r2, r0
	ldr	r0, .L3+8
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
.L4:
	.align	2
.L3:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.size	main, .-main
	.ident	"GCC: (Raspbian 8.3.0-6+rpi1) 8.3.0"
	.section	.note.GNU-stack,"",%progbits
