# MISP assembly, run it on MARS emulator
.globl main
.data

    phrase: .asciiz "a phr4se With some Numb3rs 09872 and some words."
    ph_len: .word 48

.text

main:

    li $a2, 0                   # counter to zero

    # function arguments
    lb $a0, phrase($a2)         # first char of the string
    lw $a1, ph_len              # string len
    nop

    jal char_count
    nop

    move $a0, $v0               # print first returned value
    li $v0, 1
    syscall

    li $a0, ' '                 # print space
    li $v0, 11
    syscall

    move $a0, $v1               # print second returned value
    li $v0, 1
    syscall

    li $a0, ' '                 # print space
    li $v0, 11
    syscall

    move $a0, $s0               # print third returned value
    li $v0, 1
    syscall

    li $v0, 10                  # exit
    syscall

char_count:
    subi $sp, $sp, 16           # reserve space in stack
    sw $ra, 0($sp)              # store return address

    bge $a2, $a1, return        # if end of the string reached then end recursion
    nop
    
    if_letter:
        sge $t0, $a0, 'a'       # check if char is >= a
        sle $t1, $a0, 'z'       # check if char is <= z
        sge $t2, $a0, 'A'       # check if char is >= A
        sle $t3, $a0, 'Z'       # check if char is <= Z
    
        and $t0, $t0, $t1       # 1 in $t0 if lowercase letter
        and $t1, $t2, $t3       # 1 in $t1 if uppercase letter
    
        or $t0, $t0, $t1        # 1 in $t0 if lower or upper case letter
        
        beqz $t0 if_number      # branch to check if is number if $t0 is 0
        nop
        
        addi $v0, $v0, 1        # if not branch, increment counter for letters
        j end_if                # jump to the end of the ifs
        nop
    
    if_number:
        sge $t0, $a0, '0'       # check if char is >= 0
        sle $t1, $a0, '9'       # check if char is <= 9
        
        and $t0, $t0, $t1       # 1 in $t0 if number
        
        beqz $t0 if_other       # branch to other char if $t0 is 0
        nop
        
        addi $v1, $v1, 1        # if not branch, increment counter for numbers
        j end_if                # jump to the end of the ifs
        nop
    
    if_other:
        addi $s0, $s0, 1        # increment the counter for other chars
    
    end_if:
        # store in stack value of counter
        # not needed but usefull to see how all works
        sw $v0, 4($sp)
        sw $v1, 8($sp)
        sw $s0, 12($sp)
        addi $a2, $a2, 1        # increment index
        lb $a0, phrase($a2)     # load next char
        jal char_count          # recursive
        nop	
    
    return:
        lw $ra, 0($sp)          # restore return address
        addi $sp, $sp, 16       # free space in stack frame
        jr $ra                  # return
        nop
