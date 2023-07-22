# Colonnade

A program to paginate text files.

## Compiling

To compile the program:
```
make
```
At the end **the binary is put** into the folder `bin/` along the object files.

> **_NOTE:_**  The command `make` imply a `make clean`

### Debug Mode
The program could be compiled in debug mode to have a more verbose output.

To compile in debug mode:
```
make debug
```

### Memory check
The program have been analyzed with `valgrind` to detect memory leaks in both single process and multi process modess.

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./bin/colonnade -f input.lorem.txt
```

## Usage
To manipulate a text file with `colonnade`:
```
./bin/colonnade -f input.txt
```
The output is written to the output file `output.input.txt`.

> **_NOTE:_**  The parameter `-f` is the only one mandatory, others, are described into the next section.


## Options
It's possible to specify various parameters about the the format of the text.

The options menu will appear if the program is executed with no parameters or if an unknown parameter is passed.

The options menu:
```
options [default value]:
        -f    indicates the input file
        -c    [30]  indicates the width of a column in chars
        -n    [2]   indicates the number of columns per page
        -s    [2]   indicates the space between columns
        -r    [40]  indicates the number of rows for a column/per page
        -m    indicates the use of multi processing
```
> **_NOTE:_**  Parameters with default value can be omitted

## Known bugs and weird things
Some rare situation are not handled by the code, mainly there are two know.

A void line as first line in column, happens when the last row of a paragraph is the last row of the column. e.g.
```
    [+] Formatted text:

    aaa  bbb  ccc ddd eee fff ggg    ooo  ppp  qqq rrr sss ttt uuu
    hhh  iii  jjj kkk lll mmm nnn    vvv www xxx yyy zzz          
    ooo  ppp  qqq rrr sss ttt uuu                                 
    vvv www xxx yyy zzz              111  222  333 444 555 666 777
                                     888 999 000                  
    111  222  333 444 555 666 777                                 
    888 999 000                      aaa  bbb  ccc ddd eee fff ggg
                                     hhh  iii  jjj kkk lll mmm nnn
    aaa  bbb  ccc ddd eee fff ggg    ooo  ppp  qqq rrr sss ttt uuu
    hhh  iii  jjj kkk lll mmm nnn    vvv www xxx yyy zzz          

    %%%

-->                                  888 999 000                  
    111  222  333 444 555 666 777                                 
    888 999 000                      aaa  bbb  ccc ddd eee fff ggg
                                     hhh  iii  jjj kkk lll mmm nnn
    aaa  bbb  ccc ddd eee fff ggg    ooo  ppp  qqq rrr sss ttt uuu
    hhh  iii  jjj kkk lll mmm nnn    vvv www xxx yyy zzz          
    ooo  ppp  qqq rrr sss ttt uuu                                 
    vvv www xxx yyy zzz              111  222  333 444 555 666 777
                                     888 999 000                  
    111  222  333 444 555 666 777
```

The second weird thing makes the last row of the last paragraph to exceed the column maximum width. e.g.
```
%%%

aaaa  bbbb cccc    1111  2222 3333
dddd  eeee ffff    4444  5555 6666
gggg  hhhh iiii    7777  8888 9999
jjjj  kkkk llll    0000           
mmmm  nnnn oooo                   
pppp  qqqq rrrr    aaaa  bbbb cccc
ssss  tttt uuuu    dddd  eeee ffff
vvvv  wwww xxxx    gggg  hhhh iiii
yyyy zzzz          jjjj  kkkk llll
                   mmmm  nnnn oooo

%%%

pppp  qqqq rrrr                   
ssss  tttt uuuu                   
vvvv  wwww xxxx                   
yyyy zzzz                         
                                  
1111  2222 3333                   
4444  5555 6666                   
7777 8888 9999 0000  <--             

[+] Output written to output.input.fuzz4.txt
```
No more bugs were encountered during the testing.

# Development

## About the code
Code have been organized in multiple files:

- main.c
- columns.c
- process_single.c
- process_multi.c

For every `.c` file except for the `main.c` there is a corresponding `.h` file containings the prototype for functions and the structs.

Macros have been used to make the code less verbose. e.g. check pointers, check semaphores status, ... All macros are in `.h` files.

### Memory and pointers
All pointer passed as argument to a function are checked for a NULL value.

All dynamic memory is allocated using `calloc`, more confortable than `malloc` because memory is automatically set to zero and a manual null byte after a string isn't required.

Pointers from `calloc` and `realloc` have not been checked intentionally, if a `calloc` fails, there is a bigger problem, buy more ram on amazon.

### Programming aids
Chat-GPT was not used as aid to development, instead lot of time have been spent on:

- [https://man7.org/](https://man7.org/)
- [https://stackoverflow.com/](https://stackoverflow.com/)
- [https://en.wikipedia.org/wiki/Main_Page](https://en.wikipedia.org/wiki/Main_Page)
- [https://gustedt.gitlabpages.inria.fr/modern-c/](https://gustedt.gitlabpages.inria.fr/modern-c/)
- [https://github.com/s3b4stian/c-adventures](https://github.com/s3b4stian/c-adventures)
- Course lectures
- Code snippets from the course


## Single Process Mode
In this mode, all operations are executed sequentially, there are four main operations:

- file read and tokenization in an array of words
- array of words organized in justified rows
- justified rows to pages
- pages to file

### Array of Words
The array of words is an array of pointers to `word` structure, heap allocated:
```
|array_of_words|

[0]->|word|n|
[1]->|word|n|
[2]->|word|n|
[n]->|word|n|
```

### Justified Rows
Justified rows is an array of pointer to `rows` structure, heap allocated, every row is a linked list of `word` structure:
```
|array_of_rows|

[0]->|row|f|-->|word|n|-->|word|n|-->|word|n|--> NULL
[1]->|row|f|-->|word|n|-->|word|n|--> NULL
[2]->|row|f|-->|word|n|-->|word|n|-->|word|n|-->|word|n|-->|word|n|--> NULL
[n]->|row|f|-->|word|n|-->|word|n|-->|word|n|-->|word|n|--> NULL
```
In `row`, `f` is the pointer to the first `word`, every `word` has a pointer to the next, the `row` ends when the pointer to the next is `NULL`.

To justify a row the program check the number of chars for every word, the spaces between words and the max width of a column.

If the width (in chars) of a column is greather than the chars of all words plus spaces then program start to loop the linked list, every time a `word` has the attribute space, an addition space is concatenated to the `word`. When the width of the column is matched the loop stops.

Using a linked list to abstract a `row` is easier than work with a `row` as array of char.

### To Pages
Every justified row is at this point written to a matrix that abstract the pages.

Writes are done following thi order:
```
--      --      --      -- --      -- --      -- --
    ->  --  ->  --  ->  --     ->  -- --  ->  -- --
                --      --         --         -- --
```

When a page is full, avery page has a maximun number of rows corresponding at the maximun height of a column, the program insert the page separator and restart.

```
--      --      --      -- --      -- --      -- --      -- --      -- --      -- --      -- --
        --      --      --         -- --      -- --      -- --      -- --      -- --      -- --
    ->      ->  --  ->  --     ->  --     ->  -- --  ->  -- --  ->  -- --  ->  -- --  ->  -- --
                                                         %%         %%         %%         %%
                                                                    --         -- --      -- --
                                                                                          --
```
### Pages to file
Once the page matrix is compled is written to a file row by row, the name of the output file is made prependig thw word `output.` to the original file name. e.g. the file `lorem.txt` become `output.lorem.txt`.


## Multi process
Multi process development brings with it new problems than single process programming, you need a way for process to communicate and to syncronize them.

As architecture the multiprocessing part is the porting of the actions seen before in single process mode.

Actions by processes:
- Main process
- Read file and array of words creation [aka P1]
- Creation of justified rows array [aka P2]
- Justified rows to pages [aka P3]
- Pages to file [aka P4]

Communication between processes is done using shared memory and semaphores are used to avoid race conditions. Have been allocated the least quantity of shared memory as possible.

### Why semaphores and shared memory
There are lot of ways to achieve the comunication between processes
- shared files
- shared memory
- pipes
- name pipes
- message queues
- sockets
- signals

In the first module of the course a part of the program was dedicated to semaphores as method to synchronize two or more processes. I was interested in learning more about semaphores.

Shared memory because no other metod I think fit with semaphores.

### Array of words to array of rows
Trasfering data between P1 and P2 processes:
- P1 write to shared memory the number of allocated words (`struct`) and the size of every word
- P2 read from shared memory
- P1 loop
    * write to shared memory a `word`
- P2 loop
    * read from shared memory a `word`

P2 use the data received from P1 to create an array of justified rows then transfers to P3 every justified row created. 

### Array of rows to pages
Trasnfering data between P2 and P3 processes:
- P2 write to shared memory the number of rows written
- P3 read from shared memory
- P2 loop
    * write to shared memory the number of words in a `row`
    - write to shared memory the words from the row, one by one
- P3 loop
    * read from shared memory the number of words
    * read from shared memory the words, one by one

P3 use the data received from P2 to populate a matrix an create a multicolumn page then tranfers to P4 every row of the matrix.

### Pages to final file
Trasfering data between P3 and P4:
- P3 write to shared memory the number of rows written into the matrix
- P4 read from shared memory
- P3 loop
    * write to shared memory a row of the matrix
- P4 loop
    * read from shared memory

In every read/write a semaphore put in wait status the other process involved into the operation.