.data
.balign 


prompt1:	.asciz "Give me the first operand: \n"
prompt2:	.asciz "Give me the second operand: \n"
output:		.asciz "The result of %d + %d = %d\n"
format:		.asciz "%d"

a:	.int 0
b:	.int 0
c: 	.int 0

.text
.global main
.extern printf
.extern scanf


main:
	push {ip,lr}
	ldr r0, =prompt1
	bl printf
	
	ldr r0, =format
	ldr r1, =a
	bl scanf
	
	ldr r5, =a
	ldr r5, [r5]
	

	ldr r0, =prompt2
	bl printf
	
	ldr r0, =format
	ldr r1, =b
	bl scanf

	ldr r6,=b
	ldr r6,[r6]

	add r1, r5, r6
	ldr r2, =c
	str r1,[r2]


	ldr r0, =output
	ldr r1, =a
	ldr r1,[r1]
	ldr r2, =b
	ldr r2,[r2]
	ldr r3, =c
	ldr r3,[r3]
	bl printf

	pop {ip,pc}
