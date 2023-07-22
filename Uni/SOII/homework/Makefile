
CC := gcc
CFLAGS := -Wall -Wextra -O3 -std=c11 -D_POSIX_C_SOURCE

PROGS := clean colonnade

all: $(PROGS)

debug: CFLAGS := $(CFLAGS) -D_DEBUG
debug: all

colonnade: ./bin/columns.o ./bin/process_single.o ./bin/process_multi.o ./bin/main.o
	$(CC) $^ -o bin/$@
./bin/%.o : ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*.o bin/colonnade output.*