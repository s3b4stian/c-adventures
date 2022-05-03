# MISP assembly, run it on MARS emulator
.data
    N1: .word 10
    N2: .word 20
.text
    lw      $t1, N1         # load word N1 in $t1 registry
    lw      $t2, N2         # load word N1 in $t1 registry
    add     $t0, $t1, $t2   # sum $t1 and $t2 and put result in $t0
    
    move    $a0, $t0        # move $t0 to $a0 as parameter for the syscall

    li 	    $v0, 1          # select the required syscall loading value in $v0 print integer
    syscall                 # syscall call
    li	    $v0, 10         # select the required syscall loading value in $v0 exit
    syscall                 # syscall call
