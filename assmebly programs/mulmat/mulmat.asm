

	.word 0x100 7	#set the matrixes
	.word 0x101 5
	.word 0x102 8
	.word 0x103 2
	.word 0x104 1
	.word 0x105 9
	.word 0x106 6
	.word 0x107 10
	.word 0x108 3
	.word 0x109 4
	.word 0x10A 8
	.word 0x10B 9
	.word 0x10C 10
	.word 0x10D 5
	.word 0x10E 6
	.word 0x10F 7	
	.word 0x110 4
	.word 0x111 1
	.word 0x112 2
	.word 0x113 3
	.word 0x114 7	
	.word 0x115 6
	.word 0x116 1
	.word 0x117 9
	.word 0x118 4
	.word 0x119 2
	.word 0x11A 10
	.word 0x11B 3
	.word 0x11C 6
	.word 0x11D 8
	.word 0x11E 5
	.word 0x11F 4
	sll $sp, $imm1, $imm2, $zero, 1, 11 #set $sp = 1 << 11 = 2048

       add $sp,	$sp,	$imm2, $zero, 0, -4	#allocate space in stack
	sw $s0, $sp, $imm2, $zero, 0, 0	#store $s0 in stack
	sw $s1, $sp, $imm2, $zero, 0, 1	#store $s1 in stack
       sw $s2, $sp, $imm2, $zero, 0, 2	#store $s2 in stack
       sw $ra, $sp, $imm2, $zero, 0, 3	#save return address
       add $s0, $imm2, $zero, $zero, 0, 256 #set $s0 to point to the head of matrix 1
       add $s1, $imm2, $zero, $zero, 0, 272 #set $s1 to point to the head of matrix 2 
       add $s2, $imm2, $zero, $zero, 0, 288 #set $s2 to point to the head of matrix solution 
       add $a0, $zero, $zero, $imm2, 0, 0 #set I row to 0
       add $a1, $zero, $zero, $imm2, 0, 0  #set j column to 0
       
        
elem:	
	blt $zero, $a1,$imm1, $imm2, 4,mul #if $a1<4 jump to mul
	add $a0, $a0,$imm2,$zero, 0,1 #$a0=$a0+1
	add $a1, $zero,$imm2,$zero, 0,0 #$a1=0 initialize column index
       beq $zero, $a0, $imm1, $imm2, 4,end #if $a0==4 jump to end
	
	
	
 mul:
	mac $t1,$a0, $imm2, $s0, 0, 4 #set pointer to i row
	add $t2, $s1, $a1, $zero, 0,0 #set j index in memory
	lw $t1, $t1, $imm2, $zero, 0, 0 #load element from matrix
	lw $t2, $t2, $imm2, $zero, 0, 0 #load element from matrix
	mac $t0, $t1, $t2, $zero, 0, 0 # $t0=$t1*$t2
	mac $t1,$a0, $imm2, $s0, 0, 4 #set pointer to i row 
	add $t2, $s1, $a1, $zero, 0,0 #set j index in memory
	lw $t1, $t1, $imm2,  $zero, 0, 1 #load element from matrix
	lw $t2, $t2, $imm2,  $zero, 0, 4 #load element from matrix
       mac $t0, $t1, $t2, $t0, 0, 0 # $t0=$t1*$t2+$t0
	mac $t1,$a0, $imm2, $s0, 0, 4 #set pointer to i row 
	add $t2, $s1, $a1, $zero, 0,0 #set j index in memory
       lw $t1, $t1, $imm2,  $zero, 0, 2 #load element from matrix
	lw $t2, $t2, $imm2,  $zero, 0, 8 #load element from matrix
       mac $t0, $t1, $t2, $t0, 0, 0 # $t0=$t1*$t2+$t0
	mac $t1,$a0, $imm2, $s0, 0, 4 #set pointer to i row 
	add $t2, $s1, $a1, $zero, 0,0 #set j index in memory
       lw $t1, $t1, $imm2,  $zero, 0, 3 #load element from matrix
	lw $t2, $t2, $imm2,  $zero, 0, 12 #load element from matrix
       mac $t0, $t1, $t2, $t0, 0, 0 # $t0=$t1*$t2+$t0
       add $v0, $t0, $zero, $zero, 0, 0 #$v0=$t0
       mac $t2, $a0, $imm2, $a1, 0, 4 #$t2=$a0*4+$a1
       sw $v0, $t2, $s2, $zero, 0, 0 #save the solution for arg i j
       add $a1, $a1, $imm2,$zero, 0,1 #$a1=$a1+1
       jal $ra, $zero, $zero, $imm2, 0, elem  #jump back to elem
      	
end:
	lw $s0, $sp, $imm2, $zero, 0, 0	#restore $s0 from the stack
	lw $s1, $sp, $imm2, $zero, 0, 1	#restore $s1 from the stack
       lw $s2, $sp, $imm2, $zero, 0, 2	#restore $s2 from the stack
       lw $ra, $sp, $imm2, $zero, 0, 3	#restore $ra from the stack
       add $sp,	$sp,	$imm2, $zero, 0, 4	#return $sp to initial value

	halt $zero, $zero, $zero, $zero, 0, 0		# halt

      
	
       
       
	
	

	
	
