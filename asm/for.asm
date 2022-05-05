# MISP assembly, run it on MARS emulator
# Same as the below C code
# #include <stdio.h>
# int main() {
#     for (int i = 0; i < N; i++) {
#         printf("%d ",i);
#     }
#     return 0;
# }
.globl main
.data
    N: .word 10
.text
main:
    move $t0, $zero             # used as i and set to zero
    lw $t1, N                   # used as N

    for:
        bge $t0, $t1, end_for   # branch to "end_while" on $t1 less tha C

        move $a0, $t0           # move number to $a0 as argument for syscall
        li $v0, 1               # select the required syscall loading value in $v0 print int
        syscall

        li $a0, ' '             # load immediate a space to $a0 for syscall
        li $v0, 11              # select the required syscall loading value in $v0 print char
        syscall

        addi $t0, $t0, 1        # decrement $t0 X

        j for

    end_for:

    li $v0, 10                  # select the required syscall loading value in $v0 exit
    syscall
