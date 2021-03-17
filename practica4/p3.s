.data
.balign 4

prompt1:	.asciz "Give me the first operand: \n"
prompt2:	.asciz "Give me the operation to be performed (+,-,*,/): \n"
prompt3:	.asciz "Give the second operand: \n"
prompt4:	.asciz "Give me the third operand: \n"
output1:	.asciz "The result of %d %c %d "
output2:	.asciz "%c %d = %d \n"
format:		.asciz "%d"
format2:	.asciz "%c"

a:	.int 0
b:	.int 0
c:	.int 0
d:	.int 0
op:	.int 0

.text
.global main
.extern main
.extern printf
.extern scanf

sum1:
	push {ip,lr}
	
	add r1,r5,r6
	add r1,r1,r7

	pop {ip,pc}
sub2:
	push {ip,lr}

	sub r1,r5,r6
	sub r1,r1,r7
	
	pop {ip,pc}

mul3:
	push {ip,lr}

	mul r1,r5,r6
	mov r10,r1
	mul r1,r10,r7

	pop {ip,pc}

div4:
	push {ip,lr}

	sdiv r1, r5, r6
	sdiv r1,r1,r7
	
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

@getNum3

	ldr r0, =prompt4
	bl printf

	ldr r0,=format
	ldr r1,=c
	bl scanf
	
	ldr r7, =c
	ldr r7,[r7]

@operation

	cmp r8, #43
	bleq sum1
	cmp r8, #45
	bleq sub2
	cmp r8, #42
	bleq mul3
	cmp r8, #47
	bleq div4

	ldr r2, =d
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
	ldr r1, =op
	ldr r1,[r1]
	ldr r2, =c
	ldr r2,[r2]
	ldr r3,=d
	ldr r3,[r3]
	bl printf
	
	pop {ip,pc}

