//Main function that calls the sorting algorithms
//Noah Houpt and Guy Marino
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 500000000

/*The purpose of this script is to
implement the sorting algorithms with various parameters
the parameters we are testing are:

Number of threads: 1, 2, 4, 8, 16, 32, 64

Length of Array: 10, 20, 50, 100, 200, 500,
1000, 2000, 5000, 10 000, 20 000, 50, 000, 100 000, 200 000,
500 000, 1 000 000, 2 000 000, 5 000 000, 10 000 000, 20 000 000
50 000 000, 100 000 000, 200 000 000, and 500 000 000

Different Sorting Algorithms: Bubble, Quick, Merge

We will be timing each of these parameters in order to
check the data and obtain a result of the experiment

The fucntions we are working with are:

quicksort(int[] array, int threadCount);
mergesort(int[] array, int threadCount);
bubblesort(int[] array, int threadCount);*/

//Global variables containing array that will be modified and overwritten throughout the testing
int array[N];

void RandomArray(int lowerBound, int upperBound, int arraySize){
	int i = 0;
	srand(time(0));
	for(i = 0; i < arraySize; i++){
		int number = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
		array[i] = number;
	}
}

// The main method has yet to be implemented because the other methods are not yet complete
int main(){
	struct timeval start_time, stop_time, elapsed_time;

}


// The validate method has not yet been implemented
int validate (int array[], int size){

}

// The writeout method has not yet been implemented
int writeout (struct data arguments) {

}
