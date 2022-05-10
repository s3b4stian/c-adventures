# MISP assembly, run it on MARS emulator
.globl main
.text
main:
    li $v0, 5       # read first integer from keyboard           
    syscall

    move $a0, $v0   # move the result of syscall in $t0, the destination

    li $v0, 5       # read second integer from keyboard
    syscall         

    move $a1, $v0  

    jal GCD         # call the function greatest common divisor
    nop

    move $a0, $v0   # move number to $a0 as argument for syscall
    li $v0, 1       # select the required syscall loading value in $v0 print int
    syscall

    li $v0, 10      # select the required syscall loading value in $v0 exit
    syscall         # without syscall the MARS go to funzion execution

# function GCD
# recursive version
GCD:
    subi $sp, $sp, 12
    sw $ra, 0($sp)                  # store return address
    sw $a0, 4($sp)                  # store first argument
    sw $a1, 8($sp)                  # store second argument


    beq $a0, $a1, base_case         # if the argumets of this function are equals jump to base case, x = y, GCD(x, y) = x
    nop

    bgt $a0, $a1, invert_arguments  # if first argument is greater than second then inver arguments, x > y, GCD(x, y) = GCD(y, x)
    nop                             # if not then first argument as first, second - first as second, x < y, GCD(x, y) = GCD(x, y – x)
    
    sub $t0, $a1, $a0               # perform y - x
    move $a1, $t0                   # change the second arguments
    
    j recursive                     # jump to recursion
    nop
    
    invert_arguments:
        move $t0, $a0
        move $a0, $a1
        move $a1, $t0

    recursive:
       jal GCD
       nop

    lw $ra, 0($sp)                  # return to base case is here
    addi $sp, $sp, 12               # start to restore the stack

    jr $ra                          # jump to previous stack frame, knowing how many stack frames it is possible to exit fast
    nop

    base_case:
        move $v0, $a0               # the base case is our value
        jr $ra                      # return
        nop
