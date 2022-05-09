# MISP assembly, run it on MARS emulator
.globl main
.text
main:
    li $v0, 5       # read a integer from keyboard           
    syscall         # syscall to read the integer

    move $a0, $v0   # move the result of syscall in $t0, the destination

    jal factorial   # call the function factorial
    nop

    move $a0, $v0   # move number to $a0 as argument for syscall
    li $v0, 1       # select the required syscall loading value in $v0 print int
    syscall

    li $v0, 10      # select the required syscall loading value in $v0 exit
    syscall         # without syscall the MARS go to funzion execution

# function factorial
# iterative version
factorial:
    li $v0, 1               # N = 1

    for:
        blez $a0, return    # while $a is less equal to zero, it start from keyboard input   
        nop

        mul $v0, $v0, $a0   # multiply 
        sub $a0, $a0, 1     # decrement $a0 of 1
        j for
        nop

    return:
        jr $ra              # funciton return
        nop                 # no nop no party
