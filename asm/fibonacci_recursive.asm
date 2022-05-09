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
# recursive version
fibonacci:
    # save registers on stack
    subi $sp, $sp, 16       # create space on stack, 4 words
    sw $ra, 0($sp)          # store return address
    sw $a0, 4($sp)          # store N value
    sw $v1, 8($sp)          # store N - 1
    sw $t0, 12($sp)         # buffer
    # end save

    li $t0, 2               # N = 2
    blt $a0, $t0, base_case  # if N < 2 then jump to base case
    nop

    sub $a0, $a0, 1         # decrement N to N - 1

    jal fibonacci           # recursive call for N - 1
    nop

    move $v1, $v0

    sub $a0, $a0, 1         # decrement N to N - 2

    jal fibonacci           # recursive call for N - 2
    nop

    # once base_case, $ra contain the address of the first lw
    # execution restart from here 

    # restore register from stack
    lw $ra, 0($sp)
    lw $a0, 4($sp)
    lw $v1, 8($sp)
    lw $t0, 12($sp)
    addi $sp, $sp, 16
    # end restore

    add $v0, $v0, $v1       # N - 1 + N - 2

    jr $ra
    nop

    base_case:
        li $v0, 1

        lw $ra, 0($sp)
        lw $a0, 4($sp)
        lw $v1, 8($sp)
        lw $t0, 12($sp)
        addi $sp, $sp, 16

        jr $ra
        nop
