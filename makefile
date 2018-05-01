BIN=bin/
SRC=src/
TXT=out/
CC=gcc
ARGS=-lpthread -Wall -DTRACE --std=c99 -D_BSD_SOURCE -lrt -g

all: mergesort quicksort bubblesort mergesort_single_process quicksort_single_process bubblesort_single_process run

mergesort: $(SRC)mergesort.c
	$(CC) -o $(BIN)mergesort  $(SRC)mergesort.c $(ARGS)

quicksort: $(SRC)quicksort.c
	$(CC) -o $(BIN)quicksort $(SRC)quicksort.c $(ARGS)

bubblesort: $(SRC)bubblesort.c
	$(CC) -o $(BIN)bubblesort $(SRC)bubblesort.c $(ARGS)

mergesort_single_process: $(SRC)mergesort_single_process.c
	$(CC) -o $(BIN)mergesort_single_process $(SRC)mergesort_single_process.c $(ARGS)

quicksort_single_process: $(SRC)quicksort_single_process.c
	$(CC) -o $(BIN)quicksort_single_process $(SRC)quicksort_single_process.c $(ARGS)

bubblesort_single_process: $(SRC)bubblesort_single_process.c
	$(CC) -o $(BIN)bubblesort_single_process $(SRC)bubblesort_single_process.c $(ARGS)

run:
	./$(BIN)mergesort >> $(TXT)mergesort.txt
	./$(BIN)quicksort >> $(TXT)quicksort.txt
	./$(BIN)bubblesort >> $(TXT)bubblesort.txt
	./$(BIN)mergesort_single_process >> $(TXT)mergesort_single_process.txt
	./$(BIN)quicksort_single_process >> $(TXT)quicksort_single_process.txt
	./$(BIN)bubblesort_single_process >> $(TXT)bubblesort_single_process.txt
