BIN=bin/
SRC=src/
TXT=out/
CC=gcc
ARGS=-lpthread -Wall -DTRACE --std=c99 -D_BSD_SOURCE -lrt -g

all: mergesort quicksort bubblesort

mergesort: $(SRC)mergesort.c
	$(CC) -o $(BIN)mergesort  $(SRC)mergesort.c $(ARGS)
	#./$(BIN)mergesort >> $(TXT)mergesort.txt

quicksort: $(SRC)quicksort.c
	$(CC) -o $(BIN)quicksort $(SRC)quicksort.c $(ARGS)
	#./$(BIN)quicksort >> $(TXT)quicksort.txt

bubblesort: $(SRC)bubblesort.c
	$(CC) -o $(BIN)bubblesort $(SRC)bubblesort.c $(ARGS)
