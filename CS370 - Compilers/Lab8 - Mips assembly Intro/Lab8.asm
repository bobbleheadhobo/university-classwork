 
      #  this program calculates the sum of squares up to the number entered by the user
           
.data
L1: .asciiz "Please enter value: "
L3:  .asciiz "The sum from 0 to "
NL:  .asciiz "\n"
.align 2
buffer: .space 8 # we need this to read in values an then we can store them
 .text  # directive that we are in the code segment

main:	
        subu $a0, $sp, 20 # We want 4 mem locations for main SP, RA, i , s
        sw $ra, 4($a0)  # we need to store the RA in the Activation record
        sw $sp, ($a0) # store SP
        move $sp, $a0  # adjust SP

        sw $0, 8($sp)  # store 0 into memory -- counting variable 
        sw $0, 12($sp)  # store 0 into memory -- accumulating variable
        
        
	#Prints the prompt2 string
	li $v0, 4
	la $a0, L1
	syscall 

	#reads one integer from user and saves in t0
	li $v0, 5
	
	#addu $t0, $sp, 8   #$t0 is the memory location for our variable
	syscall
	sw $v0 16($sp)
 
       
loop:
        lw $t6, 8($sp)  #   
        mul $t7, $t6, $t6  #  i * i
        lw $t8, 12($sp)   #  s
        addu $t9, $t8, $t7  #  s + i*i
        sw $t9, 12($sp)  #   s= s + i*i 
        lw $t6, 8($sp)   # i 
        addu $t0, $t6, 1  # i+1
        sw $t0, 8($sp)  #  i = i + 1
        ble $t0, $v0, loop  #   keep doing for $v0 times
        nop   # 
        
        #print the string
        la $a0, L3
        li $v0 4  
        syscall # 
        
        # print out the number
	li $v0, 1
	lw $a0, 16($sp)     # value entered  
	syscall
	
	#these 3 lines do a new line
	li $v0, 4  
	la $a0, NL
	syscall   
        
        #Prints the summation
        lw $a0, 12($sp)
        li $v0 1
        syscall
        
       
        lw $ra, 4($sp)
        lw $sp , ($sp)  # put backl Ra and SP
        
        li $v0, 10 
        syscall     #  exit for MAIN only
        
