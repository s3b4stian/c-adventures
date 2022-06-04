
.globl main
.data

phrase: .asciiz "33 30ini entrao1 @ 3nto "
ph_len: .word 24

.text

main:
    li $s0, 0               # load the index of first char of the string
    lb $s1, ph_len          # load the index of last char of the string

    subi $s1, $s1, 1        # su one, 0 to n-1

    jal group		
    nop

    li $v0, 10              # select the required syscall loading value in $v0 exit
    syscall

group:
    subi $sp, $sp, 12       # preserve space in stack
    sw $ra, 0($sp)          # preserve return address
    # only to example, preserve is useless
    # to see how indexes coming closer
    sw $s0, 4($sp)          # preserve start index
    sw $s1, 8($sp)          # preserve end index

    bge $s0, $s1, return    # if first index meet last index
    nop
    
    lb $a0, phrase($s0)		# load the char in phrase at $s0 index
    jal is_alpha            # check if the char is alpha
    nop
    
    beqz $v0, swap          # if is alpha, 1 in $v0 else swap the char, 0 in $v0
    nop
    
    addi $s0, $s0, 1        # if is alpha, increment the start index
    jal group               # recursive call
    nop

    swap:
        lb $t0, phrase($s0)	# first char
        lb $t1, phrase($s1)	# last char
        sb $t0, phrase($s1)	# lo sostituisco col primo
        sb $t1, phrase($s0)	# sostituisco il secondo al I�

        subi $s1, $s1, 1    # decrement the end index

        jal group           # recursive call
        nop

    return:
        lw $ra 0($sp)       # restore stack
        addi $sp, $sp, 12   # free space in stack

        jr $ra              # return
        nop

# $a0, first argument, the char to check
is_alpha:
    sge $t0, $a0, 'a'       # check for >= a
    sle $t1, $a0, 'z'       # check for <= z
    
    sge $t2, $a0, 'A'       # check for >= A
    sle $t3, $a0, 'Z'       # check for <= Z

    and $t0, $t0, $t1       # true if lowercashe char
    and $t1, $t2, $t3       # true if uppercase char

    or $v0, $t0, $t1        # lowercase or uppercase, $v0 return value

    jr $ra                  # return
    nop
