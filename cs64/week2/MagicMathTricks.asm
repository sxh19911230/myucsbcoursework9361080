# xSpim Demo Program
# 
#   CPE 315
#   fall 2001
#
# By: Dan Stearns
# Date:  
# Modifications: 
#	4/10/03 knico Tabbed code
#	4/10/03 knico Modified to use s registers instead of t registers
#           
#
# declare global so programmer can see actual addresses.

#  Data Area - allocate and initialize variables
.data

	# TODO: complete the global variable declarations / inits here
	# I have given you the strings, but you need to associate
	# them with variable names

q1:
	.asciiz "What are the first 3 digits of your phone number? "
q2:
	.asciiz "\nAdd it to itself\n"
q3:
	.asciiz "\nMultiply by 40\n"
q4:
	.asciiz "\nAdd 250\n"
q5:
	.asciiz "\nDivide by 5\n"
q6:
	.asciiz "\nSubtract 10\n"
q7:
	.asciiz "\nDivide by 4\n"
q8:
	.asciiz "\nSubtract 10\n"
q9:
	.asciiz "\nDivide by 4\n"

#Text Area (i.e. instructions)
.text

main:

	# TODO fill in your code here
	# Display q1;
	ori $v0, $0, 4
	la $a0, q1
	syscall

	# Read last 3 digits phone number;
	ori $v0, $0, 5
	syscall

	#Assign 3 digit to $s0
	or $s0, $0, $v0

	#Display it
	ori $v0, $0, 1
	or $a0, $0, $s0
	syscall

	#Display q2;
	ori $v0, $0, 4
        la $a0, q2
        syscall

	#Add it to itself and Display;
	sll $s0, $s0, 1

	ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

	#Display q3;
	ori $v0, $0, 4
        la $a0, q3
        syscall

	#Multiply by 40 and Display;
	sll $s0, $s0, 3
	or $t0, $s0, $0
	sll $s0, $s0, 2
	add $s0, $s0, $t0

	ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

        #Display q4;
        ori $v0, $0, 4
        la $a0, q4
        syscall

	#Add 250 and Display;
	addi $s0, $s0, 250

	ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

        #Display q5;
        ori $v0, $0, 4
        la $a0, q5
        syscall

	#Divide by 5 and Display;
	ori $t0, $0, 5
	div $s0, $t0
        mflo $s0

        ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

        #Display q6;
        ori $v0, $0, 4
        la $a0, q6
        syscall

	#Subtract 10 and Display
	ori $t0, $0, 10
	sub $s0, $s0, $t0

	ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

	#Display q7;
        ori $v0, $0, 4
        la $a0, q7
        syscall

	#Divide by 4 and Display;
        srl $s0, $s0, 2

        ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

	#Display q8;
        ori $v0, $0, 4
        la $a0, q8
        syscall

        #Subtract 10 and Display
        ori $t0, $0, 10
        sub $s0, $s0, $t0

        ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

	#Display q9;
        ori $v0, $0, 4
        la $a0, q9
        syscall

        #Divide by 4 and Display;
        srl $s0, $s0, 2

        ori $v0, $0, 1
        or $a0, $0, $s0
        syscall

	# Exit
	ori     $v0, $0, 10
	syscall
