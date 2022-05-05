# MISP assembly, run it on MARS emulator
.globl main
.data
    matrix: .word 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15     # matrix with 400 elements
    m_side: .word 4                                         # matrix side, 20x20 = 400
.text
main:

    la $t0, matrix      # pointer to the next element of the matrix as array
    la $t7, matrix
    lw $t1, m_side      # side of the matrix
    li $t2, 0           # initial sum

    # calculate the address of 
    # the last elemente in matrix
    mul $t3, $t1, $t1   # m_size * m_size
    sll $t3, $t3, 2     # multiply m_size * m_size * 4 as 4 bytes
    add $t3, $t3, $t0   # final address

    for:
        bge $t0, $t3, end_for
        nop

        lw $t4, ($t0)

        add $t0, $t0, $t1       # x = x + 1, addess + 4 bytes

        add $t2, $t4, $t2       # sum the current value of the matrix

        # print the value in position
        move $a0, $t4           # move number to $a0 as argument for syscall
        li $v0, 1               # select the required syscall loading value in $v0 print int
        syscall

        li $a0, ' '             # load immediate a space to $a0 for syscall
        li $v0, 11              # select the required syscall loading value in $v0 print char
        syscall
        # end print the value in position

        # print the \n char every 4 elements
        sub $t6, $t0, $t7       # final addess - initial address
        srl $t6, $t6, 2         # divide the address, shifting to right by 2
        div $t6, $t1		# divide using the size of the matrix

        mfhi $t5		# put on $t5 the reminder of the division

        if_end_row:
            bnez $t5, end_if
            nop

            li $a0, '\n'                # load immediate a space to $a0 for syscall
            li $v0, 11                  # select the required syscall loading value in $v0 print char
            syscall

        end_if:
        # end print

        j for
        nop

    end_for:

    move $a0, $t2       # move number to $a0 as argument for syscall
    li $v0, 1           # select the required syscall loading value in $v0 print int
    syscall
    
    li $v0, 10          # select the required syscall loading value in $v0 exit
    syscall

