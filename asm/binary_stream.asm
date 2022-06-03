# Si realizzi in assembly MIPS il seguente programma. 
# Sia data in memoria una stringa S ed un indirizzo in memoria A.

# La stringa S consiste in una concatenazione di caratteri binari, 
# '0' (codice ASCII 0x30) e '1', di lunghezza non minore di 8 
# e terminata da un carattere '\0'. 
# Nel programma da realizzare, si consideri la sequenza binaria di S come uno stream di bit. 
# Il programma deve tradurre tale stream in una stringa composta da coppie di caratteri 
# esadecimali (uno per byte). 
# Poiché si considera S come uno stream, i caratteri esadecimali devono essere creati usando 
# quelli che codificano un byte partendo dal primo carattere, poi dal secondo, poi dal terzo, 
# e così via. L'indirizzo base della stringa di traduzione deve essere A. 
# La stringa di traduzione prodotta deve terminare per '\0'. 

# Se, ad esempio,
# S è "0110 1010 110"
# e A è 0x0100 8000
# allora a partire dall'indirizzo A dovrà essere scritta la seguente stringa:
# "6A D5 AB 56"
# perchè
# – il byte codicato da S[0] a S[ 7] è 0110 1010 = 0x6A,
# – il byte codicato da S[1] a S[ 8] è 1101 0101 = 0xD5,
# – il byte codicato da S[2] a S[ 9] è 1010 1011 = 0xAB,
# – il byte codicato da S[3] a S[10] è 0101 0110 = 0x56.

# Il programma assembly deve definire nella sezione dedicata al data segment 
# la stringa (S) che termina con un simbolo di fine stringa '\0' ed il byte B. 

# Nella sezione dedicata al text segment, il programma deve avere nel comparto main il caricamento dei dati da 
# memoria, la chiamata ad una funzione byteStream definita di seguito e la stampa a terminale della 
# stringa prodotta da byteStream salvata all'indirizzo A. 
# La stampa a terminale non deve avvenire all'interno della funzione ma nel comparto main chiamante.

# La funzione byteStream accetta come argomenti:
# – $a0: l'indirizzo base della stringa S;
# – $a1: l'indirizzo A;
# e restituisce come risultato:
# – $v0: la lunghezza della stringa prodotta e salvata all'indirizzo A (nell'esempio, 8).

# Note: Commentare ogni riga di codice avendo cura di spiegare a cosa servano i registri. 
# Una soluzione ricorsiva sarà premiata con un bonus di 1 punto. 
# Si ricorda che la syscall per per la stampa di una stringa prevede come argomenti $v0 = 4 e $a0 
# assegnato con l'indirizzo della stringa da stampare.

# Inserire qui il proprio codice

.data

hex: .asciiz "0123456789ABCDEF"
S:     .byte   0:100
A:     .byte   0:100
B:     .byte   0

.text

main:
    # read a string and put it in S
    li $v0, 8       # syscal number to read a string
    la $a0, S       # address of first element of string buffer
    li $a1, 100     # max chars to read
    syscall

    # byteStream call
    la $a0, S       # addess of first element of S (source string)
    la $a1, A       # addess of first element of A (output string)
    jal byteStream  # returns The length of the string in $v0
    nop

    # print the string in A
    move $t0, $v0
    li $v0, 4
    la $a0, A
    syscall

    # end the program
    li $v0, 10
    syscall

# $a0 address of S
# $a1 address of A
byteStream:

    li $t0, 0                   # bit collector
    li $t1, 0                   # number of bit read (counter)

    while:	
        lb $s0, ($a0)           # load current byte (current character) from $a0 to $s0

        beq $s0, '\n', end      # if the byte is a new line, end
        nop

        beqz $s0, end           # if the byte is equal to zero end
        nop

        sll $t0, $t0, 1         # shift the the bit stream of 1
        andi $t2, $s0, 1	    # copy on LSB of $t2 the LSB of $s0
        or   $t0, $t0, $t2      # update the bit stream

        blt $t1, 7, continue    # every 8 bytes put the characters in A $a0
        nop

            # copy to A the 0xF0 part of the registry
            andi $t3, $t0, 0xF0 # preserve only the highest nibble of the byte
            srl $t3, $t3, 4     # shift right of 4
            lb $t4, hex($t3)    # load the corresponding char from the hex table
            sb $t4, ($a1)       # store the char in A, $a1

            # copy to A+1 the 0x0F part of the registry
            andi $t3, $t0, 0x0F # preserve only the lowest nibble of the byte
            lb $t4, hex($t3)    # load the corresponding char from the hex table
            sb $t4, 1($a1)      # store the char in A, $a1

            addi $a1, $a1, 2    # increment A, $a1 of 2

        continue:

            addi $a0, $a0, 1    # increment the index of S, reg $a0 of 1
            addi $t1, $t1, 1    # increment the bit count

            j while             # jump to the next byte
            nop

    end:
        sb $zero, ($a1)         # terminate the A string with null byte
        move $v0, $t1           # move to $v0 the number chars write to the string

        jr $ra                  # return
        nop
