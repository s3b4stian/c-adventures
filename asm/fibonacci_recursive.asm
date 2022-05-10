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
# int fib(int n)
# {
#     if (n <= 1) {
#         return n;
#     }
# 
#     return fib(n - 2) + fib(n - 1);
# }
fibonacci:
    subi $sp, $sp, 16           # preserve space in stack
    sw $ra, 8($sp)              # save return address
    sw $fp, 4($sp)              # save frame pointer
    sw $s0, 0($sp)              

    move $fp, $sp               # current stack pointer as frame pointer

    sw $a0, 12($fp)             # save function parameter n
    lw  $v0, 12($fp)            # load function parameter in $v0 
    nop

    li $t0, 1                   # if n <= 1 then
    ble $v0, $t0, base_case     # jump to base case
    nop
    lw  $v0, 12($fp)            # load function parameter n in $v0 
    nop

    sub $v0, $v0, 2             # decrement by 2 the n parameter as argument for recursive function call
    move $a0, $v0               # argument to $a0
    jal fibonacci               # recursive call 
    nop

    move $s0, $v0               # move return function value to $s0

    lw  $v0, 12($fp)            # load fuction parameter n in $v0
    nop

    sub $v0, $v0, 1             # decrement by 1 the n parameter as argument for the 2nd recursive function call
    move $a0, $v0               # argument to $a0
    jal fibonacci               # recursive call
    nop

    add $v0, $s0, $v0           # sum to $v0 the previous return value $s0 and the current $v0

    base_case:
        move $sp, $fp           # restore the stack pointer
        lw $ra, 8($sp)          # load return address
        lw $fp, 4($sp)          # load the frame pointer
        lw $s0, 0($sp)          # load the return value

        addi $sp, $sp, 16       # free stack space
        jr $ra                  # jump to return address
        nop
