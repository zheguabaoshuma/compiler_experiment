.global factorial

factorial:
@ r0 is praram. 
@ r12 is stack bottom
push {r12, lr}
sub sp,sp,#8
add r12,sp,#0
str r0, [r12,#4]
ldr r3, [r12,#4]  
cmp r3, #1
bgt br1
movs r3, #1
b br2

br1:
subs r3,r3,#1
mov r0,r3
bl factorial(PLT)
mov r4,r0
ldr r3,[r12,#4]
mul r3,r3,r4

br2:
mov r0,r3
adds r12,r12,#8
mov sp,r12

pop {r12,pc}

.global main
main:
push {r12,lr}
sub sp,sp,#8
add r12,sp,#0
mov r0,#4
bl factorial(PLT)
str r0, [r12,#4]
ldr r3, [r12,#4]
mov r0,r3
adds r12, r12, #8
mov sp, r12

pop {r12,pc}
add r0,r0,#0