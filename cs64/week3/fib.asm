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

	# TODO: Complete these declarations / initializations
ques:
	.asciiz "Enter the number you want the fibonacci value for:\n"
result:
	.asciiz "The nth fibonacci number is:  "


#Text Area (i.e. instructions)
.text

main:

	# TODO: Write your code here

	#initialization
	ori $t1, $0, 1
	ori $t2, $0, 1

	#question
	ori $v0, $0, 4
	la $a0, ques
	syscall

	#read number
	ori $v0, $0, 5
	syscall

	#n==1
	beq $v0, $t1, end
	ori $t3, $0, 2
loops:
	#if (c==n) goto result
	beq $v0, $t3, end
	addi $t3, $t3, 1
	or $t0, $0, $t2
	add $t2, $t1, $t2
	or $t1, $0, $t0
	j loops

end:
	#result
        ori $v0, $0, 4
        la $a0, result
        syscall

	ori $v0, $0, 1
	or $a0,  $t2, $0
	syscall
exit:

	# Exit
	ori     $v0, $0, 10
	syscall
