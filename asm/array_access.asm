# MISP assembly, run it on MARS emulator
.globl main
.data
    array_word: .word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    array_half: .half 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    array_byte: .byte 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

.text

main:
    
    #
    # access array using pointer to memory
    #
    la $a0, array_word          # load address (first element) of array of words
    la $a1, array_half          # load address (first element) of array of half words
    la $a2, array_byte          # load address (first element) of array of bytes

    lw $t0, ($a0)               # load the word at address
    lh $t1, ($a1)               # load the half word at address
    lb $t2, ($a2)               # load the byte at address

    addi $a0, $a0, 4            # add 4 bytes for the next word address
    addi $a1, $a1, 2            # add 2 bytes for the next half word address
    addi $a2, $a2, 1            # add 1 byte for the next byte address

    lw $t0, ($a0)               # load the (second element) word at address
    lh $t1, ($a1)               # load the (second element) half word at address
    lb $t2, ($a2)               # load the (second element) byte at address

    #
    # access array using index
    #
    li $a0, 3                   # element at index 3
    li $a1, 3                   # element at index 3
    li $a2, 3                   # element at index 3

    sll $a0, $a0, 2             # multiply x4 to obtain the word index
    sll $a1, $a1, 1             # multiply x2 to obtain the half word index
    # not needed
    #sll $a2, $a2, 0

    lw $t0, array_word($a0)     # load the word at index 3
    lh $t1, array_half($a1)     # load the half word at index 3
    lb $t2, array_byte($a2)     # load the byte at index 3

    li $v0, 10
    syscall
