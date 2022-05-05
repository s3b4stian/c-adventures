# MISP assembly, run it on MARS emulator
.globl main
.data
    destination: .word case_0, case_1, case_2, case_3, case_4, case_5, case_6, default
    LUN: .asciiz "Lunedi"
    MAR: .asciiz "Martedi"
    MER: .asciiz "Mercoledi"
    GIO: .asciiz "Giovedi"
    VEN: .asciiz "Venerdi"
    SAB: .asciiz "Sabato"
    DOM: .asciiz "Domenica"
    NAD: .asciiz "Giorno non valido"
.text
main:

    li $v0, 5                           # read a integer from keyboard           
    syscall                             # syscall to read the integer

    move $t0, $v0                       # move the result of syscall in $t0, the destination

    # check if number is in range
    li $t5, 0                           # lower limit in $t5
    li $t6, 6                           # upper limit in $t6
    
    slt  $t8, $t0, $t5                  # if $t0 is less tha $t5 then set $t8 to 1
    sgt $t9, $t0, $t6                   # if $t0 is greater than $t6 then set $t9 to 1
    
    or $t7, $t8, $t9                    # or of $t8 and $t9, result in $t7
    
    beq $t7, $zero, trigger_default     # if $t7 equal to zero, then values in range, else
        nop
        li $t0, 7                       # set the default case for the destination

    trigger_default:
    # end check

    # jump table
    sll $t0, $t0, 2             # shift to left x2, multiply for 4, memory alignement
    lw $t1, destination($t0)    # load in $t1 the value from destination array
    jr $t1                      # jump to the address in $t1
    # end jump table

    case_0:
        la $a0, LUN             # load in $a0 the first char of the string
        j end_switch            # jump to end
        nop
    case_1:
        la $a0, MAR
        j end_switch
        nop
    case_2:
        la $a0, MER
        j end_switch
        nop
    case_3:
        la $a0, GIO
        j end_switch
        nop
    case_4:
        la $a0, VEN
        j end_switch
        nop
    case_5:
        la $a0, SAB
        j end_switch
        nop
    case_6:
        la $a0, DOM
        j end_switch
        nop
    default:
    	la $a0, NAD
        j end_switch
        nop

    end_switch:

    li $v0, 4   # select the required syscall loading value in $v0 print string, 
                # address of the first byte of the string in $a0
    syscall

    li $v0, 10  # select the required syscall loading value in $v0 exit
    syscall
