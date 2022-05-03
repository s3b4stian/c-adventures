# MISP assembly, run it on MARS emulator
# Same as the below C code
# #include <stdio.h>
# int main() {
#     int x = 10;
#     do 
#     {
#         printf("%d ",x);
#         x--;
#     } while (x != 0);
#     return 0;
# }
.globl main
.data
    X: .word 10
.text
main:
    lw  $t0, X

    do:
        move    $a0, $t0        # move number to $a0 as argument for syscall
        li      $v0, 1          # select the required syscall loading value in $v0 print int
        syscall

        li      $a0, ' '        # load immediate a space to $a0 for syscall
        li      $v0, 11         # select the required syscall loading value in $v0 print char
        syscall

        subi    $t0, $t0, 1     # decrement $t0 X

        bnez    $t0, do         # branch to "do" on $t0 not equal to zero


    li	    $v0, 10             # select the required syscall loading value in $v0 exit
    syscall
