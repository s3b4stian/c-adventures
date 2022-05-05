# MISP assembly, run it on MARS emulator
.globl main
.data
    matrix: .word 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15     # matrix with 400 elements
    m_side: .word 4                                         # matrix side, 20x20 = 400
.text
main:

    li $t0, 0           # x, column
    li $t1, 0           # y, row
    li $t2, 0           # initial sum
    lw $t3, m_side      # side of the matrix

    for_row:
        bge $t1, $t3, end_for_row
        nop
        for_column:
            bge $t0, $t3, next_row 
            nop

            mul $t4, $t1, $t3       # multiply y * m_side, row for m_side
            add $t4, $t4, $t0       # add to y * m_side + x, column

            sll $t4, $t4, 2         # shift the address

            lw $t4, matrix($t4)     # load the value at position of the matrix

            add $t2, $t4, $t2       # add the position of the matrix 
        
            addi $t0, $t0, 1        # x = x + 1, next column in row

            # print the value in position
            move $a0, $t4           # move number to $a0 as argument for syscall
            li $v0, 1               # select the required syscall loading value in $v0 print int
            syscall

            li $a0, ' '             # load immediate a space to $a0 for syscall
            li $v0, 11              # select the required syscall loading value in $v0 print char
            syscall
            # end print the value in position

            j for_column
            nop

    next_row:
        li $t0, 0                   # reset the x, the column
        addi $t1, $t1, 1            # add 1 to the y, the row

        # print the new line char for next row
        li $a0, '\n'                # load immediate a space to $a0 for syscall
        li $v0, 11                  # select the required syscall loading value in $v0 print char
        syscall
        # end print the new line char for next row

        j for_row                   
        nop

    end_for_row:

    move $a0, $t2       # move number to $a0 as argument for syscall
    li $v0, 1           # select the required syscall loading value in $v0 print int
    syscall
    
    li $v0, 10          # select the required syscall loading value in $v0 exit
    syscall
