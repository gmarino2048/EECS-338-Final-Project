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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

//Global variables containing array that will be modified and overwritten throughout the testing


int *RandomArray(int arraySize);
int validate (int array[], int size);
int writeout (struct data arguments);

int *RandomArray(int arraySize){
	int i = 0;
  int array[arraySize];
	srand(time(0));
	for(i = 0; i < size; i++){
		int number = (rand() % INT_MAX);
		//printf("%d", number);
		array[i] = number;
	}

  return array
}

// The main method has yet to be implemented because the other methods are not yet complete
int main(){
	//struct timeval start_time, stop_time, elapsed_time;

  //Perform on multiple threads
	for (int threads = 1; threads <= 64; threads = threads * 2){
    for (int length = 1; lenth < 1000000000; length = length * 10){
      // Perform with length * 1
      int size = length * 1;
      int *arr = RandomArray(size);

      // Start time here
      quicksort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }

      arr = RandomArray(size);
      // Start time here
      mergesort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }

      arr = RandomArray(size);
      // Start time here
      bubblesort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }
      // Writeout here

      // Perform with length * 2
      size = length * 2;
      arr = RandomArray(size);

      // Start time here
      quicksort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }

      arr = RandomArray(size);
      // Start time here
      mergesort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }

      arr = RandomArray(size);
      // Start time here
      bubblesort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }
      // Writeout here

      // Perform with length * 5
      size = length * 5;
      arr = RandomArray(size);

      // Start time here
      quicksort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }

      arr = RandomArray(size);
      // Start time here
      mergesort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }

      arr = RandomArray(size);
      // Start time here
      bubblesort(arr, threads, size);
      // End time, store seconds as double
      if (validate(arr, size) < 0){
        exit(-1);
      }
      // Writeout here
    }
  }
}


// The validate method has not yet been implemented
int validate (int *arr, int size){
  for (int i = 0; i < size - 1; i++){
    if (arr[i] > arr[i+1]){
      return -1;
    }
  }
  return 0;
}

// The writeout method has not yet been implemented
int writeout (int threads, int size double quick, double merge, double bubble) {

}
