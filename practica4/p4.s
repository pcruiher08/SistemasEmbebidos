.data
.balign 4

prompt1:	.asciz "X = "
output1:	.asciz "The result of 6 * %d^2 + 9 * %d + 2 is =  %d \n"
format:		.asciz "%d"

x:	.int 0
a:	.int 0

.text
.global main
.extern printf
.extern scanf

main:
	push {ip,lr}

	ldr r0, =prompt1
	bl printf
	ldr r0,=format
	ldr r1,=x
	bl scanf

	ldr r4,=x
	ldr r4,[r4]

	ldr r5,=0x06
	mov r6,r4
	mul r7,r6,r6
	mul r4,r5,r7
	
	ldr r5, =0x09
	mul r7,r6,r5
	add r4,r7,r4
	ldr r6,=0x02
	add r4,r4,r6	

	ldr r5,=a
	str r4,[r5]

	ldr r0,=output1
	ldr r1,=x
	ldr r1,[r1]
	ldr r2,=x
	ldr r2,[r2]
	ldr r3,=a
	ldr r3,[r3]
	
	bl printf

	pop {ip,pc}

