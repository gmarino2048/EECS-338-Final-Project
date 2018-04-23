BIN=bin/
SRC=src/
CC=gcc
ARGS=-Wall -lpthread

all: mergesort quicksort bubblesort main join

mergesort: $(SRC)mergesort.c
	$(CC) -c -o $(BIN)mergesort.o  $(SRC)mergesort.c $(ARGS)

quicksort: $(SRC)quicksort.c
	$(CC) -c -o $(BIN)quicksort.o $(SRC)quicksort.c $(ARGS)

bubblesort: $(SRC)bubblesort.c
	$(CC) -c -o $(BIN)bubblesort.o $(SRC)bubblesort.c $(ARGS)

main: $(SRC)main.c
	$(CC) -c -o $(BIN)main.o $(SRC)main.c $(ARGS)

join: $(BIN)mergesort.o $(BIN)quicksort.o $(BIN)bubblesort.o $(BIN)main.o
	gcc -o run $(BIN)mergesort.o $(BIN)quicksort.o $(BIN)bubblesort.o $(BIN)main.o
