# MISP assembly, run it on MARS emulator
.globl main
.data
    N1: .word 64
    N2: .word 128
    N3: .word 32
    N4: .word 512
.text
main:
    lw      $a0, N1             # load first value to registry $a0
    lw      $a1, N2             # load second value to registry $a1
    lw      $a2, N3             # load third value to registry $a2
    lw      $a3, N4             # load fourth value to registry $a3

    move    $v0, $a0            # move first value to $v0, registry used to represente the max variable

    slt     $t0, $v0, $a1       # bge exploded, if $v0 is less than $a1 then $t0 to 1 else to 0
    beq     $t0, $0, checkC     # if $t0 equal to zero then checkC
    #bge     $v0, $a1, checkC    # if $v0 is greater than or equal $a1, then jump to checkC
    nop
    move    $v0, $a1            # else move $a1 in $v0, $a1 is the new max

    checkC:
        slt     $t0, $v0, $a2       # bge exploded, if $v0 is less than $a2 then $t0 to 1 else to 0
        beq     $t0, $0, checkD     # if $t0 equal to zero then checkD
        #bge     $v0, $a2, checkD    # if v0 is greater than or equal $a2, then jump to checkD
        nop
        move    $v0, $a2            # else move $a2 in $v0, $a1 is the new max

    checkD:
        slt     $t0, $v0, $a3       # bge exploded, if $v0 is less than $a3 then $t0 to 1 else to 0
        beq     $t0, $0, end        # if $t0 equal to zero then checkD
        #bge     $v0, $a3, end       # if v0 is greater than or equal $a3, then jump to end
        nop
        move    $v0, $a3            # else move $a3 in $v0, $a1 is the new max

    end:
        move    $a0, $v0            # $v0 used to select syscall replace $a0 value
        li 	    $v0, 1              # select the required syscall loading value in $v0 print integer
        syscall                     # syscall call
        li	    $v0, 10             # select the required syscall loading value in $v0 exit
        syscall
