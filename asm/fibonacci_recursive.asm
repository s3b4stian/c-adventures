# MISP assembly, run it on MARS emulator
.globl main
.text
main:
    li $v0, 5       # read a integer from keyboard         
    syscall         # syscall to read the integer

    move $a0, $v0   # move the result of syscall in $a0, the destination N value
    move $fp, $sp

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
    subi $sp, $sp, 16
    sw $ra, 8($sp)
    sw $fp, 4($sp)
    sw $s0, 0($sp)

    move $fp, $sp

    sw $a0, 12($fp)
    lw  $v0, 12($fp)
    nop

    li $t0, 1
    ble $v0, $t0, base_case
    nop
    lw  $v0, 12($fp)
    nop

    sub $v0, $v0, 2
    move $a0, $v0
    jal fibonacci
    nop

    move $s0, $v0

    lw  $v0, 12($fp)
    nop

    sub $v0, $v0, 1
    move $a0, $v0
    jal fibonacci
    nop

    add $v0, $s0, $v0   

    base_case:
        move $sp, $fp
        lw $ra, 8($sp)
        lw $fp, 4($sp)
        lw $s0, 0($sp)

        addi $sp, $sp, 16
        jr $ra
        nop
