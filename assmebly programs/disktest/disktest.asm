       sll $sp, $imm1, $imm2, $zero, 1, 11 #set $sp = 1 << 4 = 16
       add $sp,	$sp,	$imm2, $zero, 0, -4	#allocate space in stack
       sw $s0, $sp, $imm2, $zero, 0, 0	#store $s0 in stack
       sw $a0, $sp, $imm2, $zero, 0, 1	#store $a0 in stack
       sw $s1, $sp, $imm2, $zero, 0, 2	#store $s1 in stack
       sw $a1, $sp, $imm2, $zero, 0, 3	#store $a1 in stack
       add $s0, $zero, $zero, $imm2, 0, 256 #set place in memory for diskbuffer
       add $a0, $zero, $zero, $imm2, 0, 7 #set the current readen sector  index
       add $a1, $zero, $zero, $imm2, 0, 8 #set the current written sector  index

       out $zero, $imm2, $zero, $s0, 0,16 #set the diskbuffer location 
       out $zero, $imm2, $zero, $a0, 0,15 #set sector to be readen
       add $t0, $zero, $zero, $imm2, 0, 1 #set command to $t0
       out $zero, $imm2, $zero, $t0, 0, 14 #order the disk to read sector
       
L1:
	in $s1, $imm2, $zero, $zero, 0, 17 #disk status in $s1
       beq $zero, $s1, $imm1, $imm2, 1, L1 #loop while disk is busy
   	beq $zero, $a1, $imm1, $imm2, 0, END #after last written go to END
       bne $zero, $a0, $imm1, $imm2, 7, READ #command only after first reading
	add $a0, $a0, $imm2, $zero, 0, -1 #a0=a0-1 only after first reading
       beq $zero, $zero, $zero, $imm2, 0, WRITE #go to write sector 7 in 8
       
       
READ:
	add $t0, $a0, $zero, $imm2, 0, 1 #$t0 is the last written sector
	bne $zero, $t0, $a1, $imm2, 0, WRITE #read or write in this loop
       out $zero, $imm2, $zero, $a0, 0,15 #set sector to be readen
       add $t1, $zero, $zero, $imm2, 0, 1 #set command to $t1
       out $zero, $imm2, $zero, $t1, 0, 14 #order the disk to read sector
	add $a0, $a0, $imm2, $zero, 0, -1 #a0=a0-1
       beq $zero, $zero, $zero, $imm2, 0, L1 #go to L1
	

WRITE:
       out $zero, $imm2, $zero, $a1, 0,15 #set sector to be written
       add $t2, $zero, $zero, $imm2, 0, 2 #set command to $t2
       out $zero, $imm2, $zero, $t2, 0, 14 #order the disk to write sector
	add $a1, $a1, $imm2, $zero, 0, -1 #a1=a1-1
       beq $zero, $zero, $zero, $imm2, 0,L1 #go to L1

END:
	lw $s0, $sp, $imm2, $zero, 0, 0	#restore $s0 
       lw $a0, $sp, $imm2, $zero, 0, 1	#restore $a0 
       lw $s1, $sp, $imm2, $zero, 0, 2	#restore $s1 
       lw $a1, $sp, $imm2, $zero, 0, 3	#restore $a1 
       add $sp,	$sp,	$imm2, $zero, 0, 4	#restore $sp
       out $zero, $zero, $imm1, $imm2, 4,0 #turning off after reading
       halt $zero, $zero, $zero, $zero, 0, 0		# halt
       
       
       
       

       
       
       
       
       
       
       
	
 
       
       
       
       
       
       

