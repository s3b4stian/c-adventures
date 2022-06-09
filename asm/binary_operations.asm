.globl main

.data
S: .asciiz "0&5"
D: .word 3
B: .byte 0x27

.text

main:
    la $a0, S               # load address of first byte of the string
    lb $a1, B               # load the byte

    jal valutaOpSx          # jump to function
    nop

    move $a0, $v0           # return value as syscall argument
    li $v0, 1
    syscall

    li $v0, 10
    syscall

# $a0, string address
# $a1, byte
valutaOpSx:
    sub $sp, $sp, 12        # reserve space on stack
    sw  $ra, 0($sp)         # save return address

    li $a2, 0               # index of the string
    lw $a3, D               # length of the string

    lb $t3, ($a0)           # load the first char of the string in $t3, a number
    addi $t3, $t3, -48      # convert ascii value of a number in number

    srlv $t3, $a1, $t3      # shift right of $t3 to get the correct bit
    and $t3, 0x1            # preserve only the lsb

    subi $a3, $a3, 1        # reduce the length of the string

    jal valutaRecursive     # jump recursive
    nop

    move $v0, $t3           # prepare return value

    lw  $ra, 0($sp)         # restore stack
    add $sp, $sp, 12	

    jr $ra                  # return
    nop

# $a0, element in S
# $a1, byte
# $a2, index
# $a3, dim
valutaRecursive:
    sub $sp, $sp, 12        # preserve stack
    sw  $ra, 0($sp)

    bge $a2, $a3, return    # if the index reach the end of the string, brach to return
    nop

    addi $a2, $a2, 1        # increment the index
    addi $a0, $a0, 1        # increment the address of the string

    lb $s0, ($a0)           # load the current char, should be an operator

    addi $a2, $a2, 1        # increment the index
    addi $a0, $a0, 1        # increment the address of the string

    lb $s1, ($a0)           # load the current char, should be a number
    addi $s1, $s1, -48      # convert ascii value of a number in number

    srlv $s1, $a1, $s1      # shift right for the number in $s1
    and $s1, 0x1            # preserve only the lsb

    bne  $s0, '&', op_or    # if the operator is and
    nop

    and $t3, $t3, $s1       # perform the logical and

    j end_op
    nop

    op_or:
    bne  $s0, 'o', op_xor   # if the operator is or
    nop

    or $t3, $t3, $s1        # perform the logical or

    j end_op
    nop

    op_xor:
    bne  $s0, 'x', end_op   # if the operator is xor
    nop

    xor $t3, $t3, $s1       # perform logical xor

    end_op:

    jal valutaRecursive     # recursive call
    nop

    return:
    lw  $ra, 0($sp)         # stack restore
    add $sp, $sp, 12 

    jr $ra                  # return
    nop
