# MISP assembly, run it on MARS emulator
.globl main
.text
main:
    li $v0, 5       # read a integer from keyboard           
    syscall         # syscall to read the integer

    move $a0, $v0   # move the result of syscall in $t0, the destination

    jal fibonacci   # call the function fibonacci
    nop

    move $a0, $v0   # move number to $a0 as argument for syscall
    li $v0, 1       # select the required syscall loading value in $v0 print int
    syscall

    li $v0, 10      # select the required syscall loading value in $v0 exit
    syscall         # without syscall the MARS go to funzion execution

# function fibonacci
# iterative version
fibonacci:
    li $t2, 1                   # N = 1

    li $t0, 0                   # temp 1
    li $t1, 1                   # temp 2

    for:
        beq $t2, $a0, return    # while $a is less equal to zero, it start from keyboard input   
        nop

        add $v0, $t0, $t1       # sum temp1 and temp2

        move $t0, $t1           # set temp1 as temp2
        move $t1, $v0           # move the sum to temp2

        add $t2, $t2, 1         # N incement

        j for
        nop

    return:
        jr $ra                  # funciton return
        nop                     # no nop no party
