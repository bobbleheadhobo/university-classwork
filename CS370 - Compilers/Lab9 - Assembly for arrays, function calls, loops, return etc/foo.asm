.data # start of the DATA section, strings first

_L4: .asciiz "x = "   # define a global string
_L5: .asciiz "\n"   # define a global string
_L6: .asciiz "y[5] = "   # define a global string
_L7: .asciiz "first result: "   # define a global string
_L8: .asciiz "\n"   # define a global string
_L9: .asciiz "second result: "   # define a global string
_L0: .asciiz "\nLeft: "   # define a global string
_L1: .asciiz "\n"   # define a global string
_L2: .asciiz "Right: "   # define a global string
_L3: .asciiz "\n"   # define a global string
_NL: .asciiz "\n"# New line
.align 2 # start all of global variables aligned

result1: .space 4       # define a global variable
result2: .space 4       # define a global variable

.text

.globl main

add:	                         #Start of Function
		subu $t0 $sp 20          #set up $t0 to be the new spot for SP
		sw $ra ($t0)             #Store the return address
		sw $sp 4($t0)            #Store the old stack pointer
		move $sp $t0             #set the stack pointer to the new value

		li $v0, 4                #set up write string
		la $a0, _L0              #fetch the string
		syscall                  #print the string

		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		li $v0 1                 #set up the write number
		syscall                  #print the write statment

		li $v0, 4                #set up write string
		la $a0, _L1              #fetch the string
		syscall                  #print the string

		li $v0, 4                #set up write string
		la $a0, _L2              #fetch the string
		syscall                  #print the string

		li $a0 12                #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		li $v0 1                 #set up the write number
		syscall                  #print the write statment

		li $v0, 4                #set up write string
		la $a0, _L3              #fetch the string
		syscall                  #print the string

		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		sw $a0, 16($sp)          #Store left hand side in memory at sp + offset
		li $a0 12                #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		move $a1, $a0            #move right hand side to a1
		lw $a0 16($sp)           #fetch left hand side from memory
		add $a0, $a0, $a1        #add numbers and store in a0
		lw $ra ($sp)             #reset the return address
		lw $sp 4($sp)            #reset stack pointer

		jr $ra                   #jump back to function

		li $v0 0                 #return NULL
		lw $ra ($sp)             #reset the return address
		lw $sp 4($sp)            #reset stack pointer

		jr $ra                   #jump back to function

main:	                         #Start of Function
		subu $t0 $sp 100         #set up $t0 to be the new spot for SP
		sw $ra ($t0)             #Store the return address
		sw $sp 4($t0)            #Store the old stack pointer
		move $sp $t0             #set the stack pointer to the new value

		li $a0 10                #load a number for expression
		sw $a0, 52($sp)          #store right hand side in memory
		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a1, 52($sp)          #get right hand side and put it in a1
		sw $a1, ($a0)            #assign value

		li $v0, 4                #set up write string
		la $a0, _L4              #fetch the string
		syscall                  #print the string

		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		li $v0 1                 #set up the write number
		syscall                  #print the write statment

		li $v0, 4                #set up write string
		la $a0, _L5              #fetch the string
		syscall                  #print the string

		li $a0 20                #load a number for expression
		sw $a0, 56($sp)          #store right hand side in memory
		li $a0 5                 #load a number for expression
		sll $t1, $a0 2           #multiply expression by 4
		li $a0 12                #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var
		add $a0, $a0, $t1        #direct memory address of array index

		lw $a1, 56($sp)          #get right hand side and put it in a1
		sw $a1, ($a0)            #assign value

		li $v0, 4                #set up write string
		la $a0, _L6              #fetch the string
		syscall                  #print the string

		li $a0 5                 #load a number for expression
		sll $t1, $a0 2           #multiply expression by 4
		li $a0 12                #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var
		add $a0, $a0, $t1        #direct memory address of array index

		lw $a0 ($a0)             #load from memory location
		li $v0 1                 #set up the write number
		syscall                  #print the write statment

		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		sw $a0, 64($sp)          #store arguments in memory
		li $a0 5                 #load a number for expression
		sll $t1, $a0 2           #multiply expression by 4
		li $a0 12                #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var
		add $a0, $a0, $t1        #direct memory address of array index

		lw $a0 ($a0)             #load from memory location
		sw $a0, 60($sp)          #store arguments in memory
		subu $t2 $sp 20          #carve out memory for the function
		lw $t0, 64($sp)          #load argument from memory
		sw $t0, 8($t2)           #store arguments inside the function
		lw $t0, 60($sp)          #load argument from memory
		sw $t0, 12($t2)          #store arguments inside the function
		jal add                  #jump to function
		sw $a0, 68($sp)          #store right hand side in memory
		la $a0 result1           #load global variable address in EMIT_Ident

		lw $a1, 68($sp)          #get right hand side and put it in a1
		sw $a1, ($a0)            #assign value

		li $v0, 4                #set up write string
		la $a0, _L7              #fetch the string
		syscall                  #print the string

		la $a0 result1           #load global variable address in EMIT_Ident

		lw $a0 ($a0)             #load from memory location
		li $v0 1                 #set up the write number
		syscall                  #print the write statment

		li $v0, 4                #set up write string
		la $a0, _L8              #fetch the string
		syscall                  #print the string

		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		sw $a0, 76($sp)          #store arguments in memory
		li $a0 5                 #load a number for expression
		sll $t1, $a0 2           #multiply expression by 4
		li $a0 12                #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var
		add $a0, $a0, $t1        #direct memory address of array index

		lw $a0 ($a0)             #load from memory location
		sw $a0, 72($sp)          #store arguments in memory
		subu $t2 $sp 20          #carve out memory for the function
		lw $t0, 76($sp)          #load argument from memory
		sw $t0, 8($t2)           #store arguments inside the function
		lw $t0, 72($sp)          #load argument from memory
		sw $t0, 12($t2)          #store arguments inside the function
		jal add                  #jump to function
		sw $a0, 92($sp)          #store arguments in memory
		la $a0 result1           #load global variable address in EMIT_Ident

		lw $a0 ($a0)             #load from memory location
		sw $a0, 84($sp)          #store arguments in memory
		li $a0 8                 #get the local var offset
		add $a0, $a0, $sp        #direct memory address of var

		lw $a0 ($a0)             #load from memory location
		sw $a0, 80($sp)          #store arguments in memory
		subu $t2 $sp 20          #carve out memory for the function
		lw $t0, 84($sp)          #load argument from memory
		sw $t0, 8($t2)           #store arguments inside the function
		lw $t0, 80($sp)          #load argument from memory
		sw $t0, 12($t2)          #store arguments inside the function
		jal add                  #jump to function
		sw $a0, 88($sp)          #store arguments in memory
		subu $t2 $sp 20          #carve out memory for the function
		lw $t0, 92($sp)          #load argument from memory
		sw $t0, 8($t2)           #store arguments inside the function
		lw $t0, 88($sp)          #load argument from memory
		sw $t0, 12($t2)          #store arguments inside the function
		jal add                  #jump to function
		sw $a0, 96($sp)          #store right hand side in memory
		la $a0 result2           #load global variable address in EMIT_Ident

		lw $a1, 96($sp)          #get right hand side and put it in a1
		sw $a1, ($a0)            #assign value

		li $v0, 4                #set up write string
		la $a0, _L9              #fetch the string
		syscall                  #print the string

		la $a0 result2           #load global variable address in EMIT_Ident

		lw $a0 ($a0)             #load from memory location
		li $v0 1                 #set up the write number
		syscall                  #print the write statment

		li $v0 0                 #return NULL
		lw $ra ($sp)             #reset the return address
		lw $sp 4($sp)            #reset stack pointer

		li $v0, 10               #set up end of main function
		syscall                  #end main function
