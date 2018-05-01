BIN=bin/
SRC=src/
CC=gcc
ARGS=-lpthread -Wall -DTRACE --std=c99 -D_BSD_SOURCE -lrt

all: mergesort quicksort bubblesort

mergesort: $(SRC)mergesort.c
	$(CC) -o $(BIN)mergesort  $(SRC)mergesort.c $(ARGS)

quicksort: $(SRC)quicksort.c
	$(CC) -o $(BIN)quicksort $(SRC)quicksort.c $(ARGS)

bubblesort: $(SRC)bubblesort.c
	$(CC) -o $(BIN)bubblesort $(SRC)bubblesort.c $(ARGS)
