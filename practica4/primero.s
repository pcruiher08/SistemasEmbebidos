	.data
a:	.word	0
b:	.word	0
c:	.word	0
y:	.word	0

.text
.global main

main:
	push	{ip,lr} @ push return address + dummy register
	ldr r0, =a
	ldr r1, =0xAAAAAAAA
	str r1,[r0]

	ldr r0, =b
	ldr r1, =0xAAAAAAAA
	str r1,[r0]

	ldr r0, =b
	ldr r1, =0xAAAAAAAA
	str r1,[r0]
@first addressing mode - Indirect
	ldr r0, =y
	ldr r1, =a
	ldr r2,[r1] 
	str r2,[r0]
@second addressing mode - Indirect with second register
	ldr r0, =y
	ldr r1, =a
	ldr r3, =0x00000000
	ldr r2,[r1,r3] 
	str r2,[r0]
@second addressing mode - Indirect with Constant
	ldr r0, =y
	ldr r1, =a
	ldr r2,[r1,#0] 
	str r2,[r0] 
	pop 	{ip, pc}        
	
	