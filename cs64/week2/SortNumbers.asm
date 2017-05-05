# xSpim SortedNumbers.asm program
# 
#

#  Data Area - allocate and initialize variables
.data

	# TODO: Complete these declarations / initializations
q1:
	.asciiz "Enter the next number:\n"
sm:
	.asciiz "Smallest:  "
mi:
	.asciiz "\nMiddle:  "
bi:
	.asciiz "\nBiggest:  "


#Text Area (i.e. instructions)
.text

main:

	# TODO: Write your code here

	# Display q1;
	ori $v0, $0, 4
	la $a0, q1
	syscall

	# Read #1 and assign to $s0;
	ori $v0, $0, 5
	syscall
	or $s0, $0, $v0

	# Display q1;
        ori $v0, $0, 4
        la $a0, q1
        syscall

        # Read #2 and assign to $s1;
        ori $v0, $0, 5
        syscall
        or $s1, $0, $v0

	# Display q1;
        ori $v0, $0, 4
        la $a0, q1
        syscall

        # Read #3 and assign to $s2;
        ori $v0, $0, 5
        syscall
        or $s2, $0, $v0

	#Assignment
	la $t2, bltc
	la $t3, finish
	la $t4, result

	#if (b < c) goto bltc;
	slt $t0, $s1, $s2
	bne $t0, $0, bltc

	#if (a < c) goto finish;
	slt $t0, $s0, $s2
	bne $t0, $0, finish

	#tmp = a; a = c; c = tmp;
	or $t0, $s0, $0
	or $s0, $s2, $0
	or $s2, $t0, $0

	#goto finish
	j finish

bltc:
	#if (a < b) goto finish;
	slt $t0, $s0, $s1
        bne $t0, $0, finish

	#tmp = a; a = b; b = tmp;
        or $t0, $s0, $0
        or $s0, $s1, $0
        or $s1, $t0, $0

finish:
	#if (b < c) goto result;
	slt $t0, $s1, $s2
        bne $t0, $0, result

	#tmp = b;b = c;c = tmp;
	or $t0, $s1, $0
        or $s1, $s2, $0
        or $s2, $t0, $0

result:
	#Dissplay Smallest;
	ori $v0, $0, 4
	la $a0, sm
	syscall

	ori $v0, $0, 1
	or $a0, $0, $s0
	syscall

	#Dissplay Middle;
        ori $v0, $0, 4
        la $a0, mi
        syscall

        ori $v0, $0, 1
        or $a0, $0, $s1
        syscall

	#Dissplay Biggest;
        ori $v0, $0, 4
        la $a0, bi
        syscall

        ori $v0, $0, 1
        or $a0, $0, $s2
        syscall

	# Exit
	ori     $v0, $0, 10
	syscall
