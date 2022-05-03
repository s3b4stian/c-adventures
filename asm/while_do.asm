# MISP assembly, run it on MARS emulator
# Same as the below C code
# #include <stdio.h>
# int main() {
#     int c = 0;
#     while (c < 10) {
#         printf("%d ",c);
#         c++;
#     }
#     return 0;
# }
.globl main
.data
    C: .word 0
.text
main:
    lw  $t0, C
    li  $t1, 10

    while:
        blt     $t1, $t0, end_while # branch to "end_while" on $t1 less tha C

        move    $a0, $t0            # move number to $a0 as argument for syscall
        li      $v0, 1              # select the required syscall loading value in $v0 print int
        syscall

        li      $a0, ' '            # load immediate a space to $a0 for syscall
        li      $v0, 11             # select the required syscall loading value in $v0 print char
        syscall

        addi    $t0, $t0, 1         # decrement $t0 X

        j while

    end_while:

    li	    $v0, 10                 # select the required syscall loading value in $v0 exit
    syscall
