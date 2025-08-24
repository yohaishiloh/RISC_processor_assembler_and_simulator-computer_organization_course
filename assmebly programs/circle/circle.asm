       .word 0x100 96	#set radius
       sll $sp, $imm1, $imm2, $zero, 1, 11 #set $sp = 1 << 4 = 16

	add $sp,	$sp,	$imm2, $zero, 0, -5	#allocate space in stack
	sw $s1, $sp, $imm2, $zero, 0, 0	#store $s1 in stack
	sw $s2, $sp, $imm2, $zero, 0, 1	#store $s2 in stack
	sw $s0, $sp, $imm2, $zero, 0, 2	#store $s0 in stack
	sw $a0, $sp, $imm2, $zero, 0, 3	#store $a0 in stack
	sw $a1, $sp, $imm2, $zero, 0, 4	#store $a1 in stack
	add $s1, $zero, $zero, $imm2, 0, 127 #set center of monitor x axis
	add $s2, $zero, $zero, $imm2, 0, 127 #set center of monitor y axis
	lw $s0, $imm2, $zero, $zero, 0, 256 #set $s0 to contain the radius
	mac $s0, $s0, $s0, $zero, 0, 0 #$s0=radius^2
	add $a0, $zero, $zero, $zero, 0, 0 #initialize $a0 as X index
	add $a1, $zero, $zero, $zero, 0, 0 #initialize $a1 as y index

LOOP:
	add $t0, $a0, $imm2, $zero, 0, -127 #offset x
	mac $t0, $t0, $t0, $zero, 0,0 #$t0=(x-127)^2
       add $t1, $a1, $imm2, $zero, 0, -127 #offset y
	mac $t1, $t1, $t1, $zero, 0,0 #$t1=(y-127)^2
	add $t2, $t1, $t0, $zero, 0, 0 #sum of  squared offset indexes
	blt $zero, $t2, $s0,$imm2, 0, DRAW #if (x,y)  in circle goto DRAW
	add $a1, $a1, $imm2, $zero, 0, 1  #y=y+1
       blt $zero, $a1, $imm1, $imm2, 255, LOOP #check y in frame
	add $a1, $zero, $zero, $zero, 0, 0 #y=0
	add $a0, $a0, $imm2, $zero, 0,1 #x=x+1
	blt $zero, $a0, $imm1, $imm2, 255, LOOP #check x in frame
       beq $zero, $zero, $zero, $imm2, 0, END #go to END
DRAW:
	sll $t0, $a0, $imm2, $zero, 0, 8 #$t0=x*256
	add $t1, $t0, $a1, $zero, 0,0 #calculate address
	out $zero, $imm1, $zero, $t1, 20,0 #set address in monitoraddr
       out $zero, $imm1, $zero, $imm2, 21, 255 #color of the next cell
       out $zero, $imm1, $zero, $imm2, 22,1 #write pixel to monitor
      add $a1, $a1, $imm2, $zero, 0, 1  #y=y+1
       blt $zero, $a1, $imm1, $imm2, 255, LOOP #check y in frame
	add $a1, $zero, $zero, $zero, 0, 0 #y=0
	add $a0, $a0, $imm2, $zero, 0,1 #x=x+1
	blt $zero, $a0, $imm1, $imm2, 255, LOOP #check x in frame
       beq $zero, $zero, $zero, $imm2, 0, END #go to END
END:
	lw $s1, $sp, $imm2, $zero, 0, 0	#restore $s1 from the stack
	lw $s2, $sp, $imm2, $zero, 0, 1	#restore $s2 from the stack
	lw $s0, $sp, $imm2, $zero, 0, 2	#restore $s0 from the stack
	lw $a0, $sp, $imm2, $zero, 0, 3	#restore $a0 from the stack
	lw $a1, $sp, $imm2, $zero, 0, 4	#restore $a1 from the stack
	add $sp,	$sp,	$imm2, $zero, 0, 5	#restore $sp
	halt $zero, $zero, $zero, $zero, 0, 0		# halt




       
       
       
       
	 












