.data
.balign 4

prompt1:	.asciz "Give me the first operand: \n"
prompt2:	.asciz "Give me the operation to be performed (+,-,*,/): \n"
prompt3:	.asciz "Give me the second operand: \n"
output1:	.asciz "The result of %d %c %d = \n"
output2:	.asciz "%d \n"
format:		.asciz "%d"
format2:	.asciz "%c"

a:	.int 0
b:	.int 0
c:	.int 0
op:	.int 0

.text
.global main
.extern printf
.extern scanf

sum1:
	push {ip,lr}
	
	add r1,r5,r6

	pop {ip,pc}
sub2:
	push {ip,lr}

	sub r1,r5,r6
	
	pop {ip,pc}

mul3:
	push {ip,lr}

	mul r1,r5,r6

	pop {ip,pc}

div4:
	push {ip,lr}

	sdiv r1, r5, r6
	
	pop {ip,pc}
	

main:
@getNum1
	push {ip,lr}

	ldr r0, =prompt1
	bl printf
	
	ldr r0, =format
	ldr r1, =a
	bl scanf

	ldr r5, =a
	ldr r5,[r5]
	
	
@getOp
	

	ldr r0, =prompt2
	bl printf

	ldr r0, =format2
	ldr r1, =op
	bl scanf

	ldr r0, =format2
	ldr r1, =op
	bl scanf

	ldr r8, =op
	ldr r8,[r8]

	

@getNum2
	

	ldr r0, =prompt3
	bl printf

	ldr r0, =format
	ldr r1, =b
	bl scanf

	ldr r6, =b
	ldr r6,[r6]

@operation

	cmp r8, #43
	bleq sum1
	cmp r8, #45
	bleq sub2
	cmp r8, #42
	bleq mul3
	cmp r8, #47
	bleq div4

	ldr r2, =c
	str r1, [r2]

	
	ldr r0,=output1
	ldr r1, =a
	ldr r1,[r1]
	ldr r2, =op
	ldr r2,[r2]
	ldr r3, =b
	ldr r3, [r3]
	bl printf

	ldr r0, =output2
	ldr r1, =c
	ldr r1,[r1]
	bl printf
	
	pop {ip,pc}



