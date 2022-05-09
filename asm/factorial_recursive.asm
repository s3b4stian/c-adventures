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
# recursive version
factorial:
    blez $a0, base_case     # jump to base case
    nop

    # save registers on stack
    subi $sp, $sp, 8        # create space on stack, 2 words
    sw $ra, 0($sp)          # store return address
    sw $a0, 4($sp)          # store N value
    # end save

    sub $a0, $a0, 1         # decrement N

    jal factorial           # recursive call
    nop

    # once base_case, $ra contain the address of the first lw
    # execution restart from here 

    # restore register from stack
    lw $ra, 0($sp) 
    lw $a0, 4($sp)
    addi $sp, $sp, 8
    # end restore

    mul $v0, $v0, $a0       # multiply values retrieved from stack

    jr $ra
    nop

    base_case:
        li $v0, 1           # initialize accoumulator
        jr $ra
        nop