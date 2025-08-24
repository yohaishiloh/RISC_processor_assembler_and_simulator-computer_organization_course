	.word 0x100 5	#set n
	.word 0x101 3	#set k

	sll $sp, $imm1, $imm2, $zero, 1, 11 #set $sp = 1 << 11 = 2048

	add $v0, $zero, $zero, $zero, 0, 0, #initialize $v0 to 0
       add $sp,	$sp,	$imm2, $zero, 0, -4 #allocate space in stack
	sw $a0, $sp, $imm2, $zero, 0, 0	#store $a0 in stack
	sw $a1, $sp, $imm2, $zero, 0, 1	#store $a1 in stack
       sw $s0, $sp, $imm2, $zero, 0, 2	#store $s0 in stack
       sw $ra, $sp, $imm2, $zero, 0, 3	#save return address
       lw $a0, $zero, $imm2, $zero, 0, 256 #$a0=n
       lw $a1, $zero, $imm2, $zero, 0, 257 #$a1=k
       jal $ra, $zero, $zero, $imm2, 0, bin #calc $v0 = binom(n,k)
end:
       
       lw $a0, $sp, $imm2, $zero, 0, 0	#restore $a0 in stack
	lw $a1, $sp, $imm2, $zero, 0, 1	#restore $a1 in stack
       lw $s0, $sp, $imm2, $zero, 0, 2	#restore $s0 in stack
       lw $ra, $sp, $imm2, $zero, 0, 3	        #restore $ra
       add $sp,	$sp,	$imm2, $zero, 0, 4 	#restore original value
       sw $zero, $zero, $imm2, $v0, 0,258  #store binom(n,k)in  258
	halt $zero, $zero, $zero, $zero, 0, 0		# halt

bin:
	add $sp,$sp, $imm2, $zero, 0, -4   #adjust stack for 3 items
       sw $a0, $sp, $imm2, $zero, 0, 0	#store $a0 in stack
	sw $a1, $sp, $imm2, $zero, 0, 1	#store $a1 in stack
	sw $zero, $sp, $imm2, $s0, 0, 2		# save $s0
       sw $ra, $sp, $imm2, $zero, 0, 3	#save return address
       bne $zero, $a0,$zero, $imm2, 0,L1 #if k!=0 jump to L1
       add $v0, $imm2, $zero, $zero, 0, 1 # bin()=1
       beq $zero, $zero, $zero, $imm2, 0, L2		# jump to L2
	beq $zero, $zero, $zero, $imm2, 0, L3		# and return to L3

L1:
       bne $zero, $a0,$a1, $imm2, 0,L2 #if n!=k jump to L2
       add $v0, $imm2, $zero, $zero, 0,1 # bin()=1
	beq $zero, $zero, $zero, $imm2, 0, L3		# and return to L3


L2:
       sub $a0, $a0, $imm2, $zero, 0, 1  #calculate n-1
	blt $zero, $a0, $zero, $imm2, 0, L3 #if n<0 go to L3
       jal $ra, $zero, $zero,$imm2, 0, bin  #calculate $v0=binom(n-1,k)
       add $s0, $v0, $imm2, $zero, 0, 0	#$s0= bin(n-1,k)
       add $a1, $a1, $imm2, $zero, 0, -1 #k=k-1
	blt $zero, $a1, $zero, $imm2, 0, L3 #if k<0 go to L3
       jal $ra, $zero, $zero,$imm2, 0, bin  #calculate $v0=binom(n-1,k-1)
       add $v0, $v0, $s0, $zero, 0, 0 #$v0=binom(n-1,k)+binom(n-1,k-1)
L3:
	lw $a0, $sp, $imm2, $zero, 0, 0			# restore $a0
	lw $a1, $sp, $imm2, $zero, 0, 1			# restore $a1
	lw $s0, $sp, $imm2, $zero, 0, 2			# restore $s0
       lw $ra, $sp, $imm2, $zero, 0, 3			# restore $ra	
	add $sp, $sp, $imm2, $zero, 0, 4		# pop 4 items from stack
	beq $zero, $zero, $zero, $ra, 0, 0		# and return


       
       
       
       
       
       
       


	 
	
