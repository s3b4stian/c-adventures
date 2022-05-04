# MISP assembly, run it on MARS emulator
.globl main
.data
    vector: .word 20, 75, 18, 22, 33, 50, 69
    v_size: .word 7
.text
main:

    lw      $t0, vector($zero)      # first element of the array in $t0 on max variable
    lw      $t1, v_size             # size of the array in $t1

    li      $t2, 0                  # i of the for cicle

    for:
        bge     $t2, $t1, end_for   # if i < v_size
        nop

        sll     $t3, $t2, 2         # shift the $t2 to the correct address to access to the array

        lw      $a0, vector($t3)    # move number to $a0 as argument for syscall
        li      $v0, 1              # select the required syscall loading value in $v0 print int
        syscall

        li      $a0, ' '            # load immediate a space to $a0 for syscall
        li      $v0, 11             # select the required syscall loading value in $v0 print char
        syscall

        lw      $t4, vector($t3)    # load the current vector value to $t4

        ble     $t4, $t0, end_if      # brach less equals if $t4 is less than the current max
            nop
            move    $t0, $t4        # else update the max

        end_if:

        addi    $t2, $t2, 1         # increment i

        j for
        nop

        end_for:

    li      $a0, '\n'               # load immediate a space to $a0 for syscall
    li      $v0, 11                 # select the required syscall loading value in $v0 print char
    syscall

    move    $a0, $t0                # move number to $a0 as argument for syscall
    li      $v0, 1                  # select the required syscall loading value in $v0 print int
    syscall
    
    li      $v0, 10                 # select the required syscall loading value in $v0 exit
    syscall
