# MISP assembly, run it on MARS emulator
.globl main
.data
    vector: .word 20, 75, 18, 22, 33, 50, 69
    v_size: .word 7
.text
main:

    la      $t0, vector            # address of the first element in vector
    lw      $t1, v_size             # size of the array in $t1

    # calculate the address of 
    # the last elemente in vector
    sll     $t1, $t1, 2             # v_size * 4
    add     $t1, $t1, $t0           # end = vector + v_size


    li      $t2, 0                  # sum to zero

    for:
        bge     $t0, $t1, end_for   # if memory address of the current element is great or equal than the end of the vector, end the cicle
        nop

        lw      $t3, ($t0)          # load the current value at the memory address

        add     $t2, $t2, $t3       # increment the sum with the current value of the array

        # important
        addi    $t0, $t0, 4         # memory address of the next element in array, add 4 to obtain the next memory address
        # important

        move    $a0, $t3            # move number to $a0 as argument for syscall
        li      $v0, 1              # select the required syscall loading value in $v0 print int
        syscall

        li      $a0, ' '            # load immediate a space to $a0 for syscall
        li      $v0, 11             # select the required syscall loading value in $v0 print char
        syscall

        j for
        nop

        end_for:

    li      $a0, '\n'               # load immediate a space to $a0 for syscall
    li      $v0, 11                 # select the required syscall loading value in $v0 print char
    syscall

    move    $a0, $t2                # move number to $a0 as argument for syscall
    li      $v0, 1                  # select the required syscall loading value in $v0 print int
    syscall

    li      $v0, 10                 # select the required syscall loading value in $v0 exit
    syscall
