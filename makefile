BIN=bin/
SRC=src/
TXT=out/
CC=gcc
ARGS=-lpthread -Wall -DTRACE --std=c99 -D_BSD_SOURCE -lrt -g

all: mergesort quicksort bubblesort mergesort_single_process quicksort_single_process bubblesort_single_process

mergesort: $(SRC)mergesort.c
	$(CC) -o $(BIN)mergesort  $(SRC)mergesort.c $(ARGS)
	#./$(BIN)mergesort >> $(TXT)mergesort.txt

quicksort: $(SRC)quicksort.c
	$(CC) -o $(BIN)quicksort $(SRC)quicksort.c $(ARGS)
	#./$(BIN)quicksort >> $(TXT)quicksort.txt

bubblesort: $(SRC)bubblesort.c
	$(CC) -o $(BIN)bubblesort $(SRC)bubblesort.c $(ARGS)
	#./$(BIN)bubblesort >> $(TXT)bubblesort.txt
	
mergesort_single_process: $(SRC)mergesort_single_process.c
	$(CC) -o $(BIN)mergesort_single_process $(SRC)mergesort_single_process.c $(ARGS)
	#./$(BIN)mergesort_single_process >> $(TXT)mergesort_single_process.txt
	
quicksort_single_process: $(SRC)quicksort_single_process.c
	$(CC) -o $(BIN)quicksort_single_process $(SRC)quicksort_single_process.c $(ARGS)
	#./$(BIN)quicksort_single_process >> $(TXT)quicksort_single_process.txt
	
bubblesort_single_process: $(SRC)bubblesort_single_process.c
	$(CC) -o $(BIN)bubblesort_single_process $(SRC)bubblesort_single_process.c $(ARGS)
	#./$(BIN)bubblesort_single_process >> $(TXT)bubblesort_single_process.txt
