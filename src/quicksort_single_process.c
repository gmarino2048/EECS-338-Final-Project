/*classic quicksort algorithm utilizing a singular process.
This algorithm will be used in testing, and will serve as
a control to compare to our multiprocess quicksort implementation.*/

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

void quicksort(int array[], long lowIndex, long highIndex);
int partition(int array[], long lowIndex, long highIndex);
void swap (int *arr, long index1, long index2);
int *randomArray(long size);

int main(){
  struct timeval start_time, stop_time, elapsed_time;
  long i;
  for(i = 1; i < 100000000; i = i * 2){

    int *unsorted = malloc(i * sizeof(int));
    unsorted = randomArray(i);
    gettimeofday(&start_time, NULL);
    quicksort(unsorted, 0, (i - 1));
    gettimeofday(&stop_time, NULL);

    timersub(&stop_time, &start_time, &elapsed_time);
    printf("%ld,%f\n", i, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
    free(unsorted);
  }
}

void quicksort(int array[], long lowIndex, long highIndex){
  if(lowIndex < highIndex){
    int i = partition(array, lowIndex, highIndex);
    quicksort(array, lowIndex, i - 1);
    quicksort(array, i + 1, highIndex);
  }
}

int partition(int array[], long lowIndex, long highIndex){
  int pivot = array[highIndex];
  int i = (lowIndex - 1);

  for(int j = lowIndex; j <= highIndex - 1; j++){
    if(array[j] <= pivot){
      i++;
      swap(array, i, j);
    }
  }
  swap(array, (i + 1), highIndex);
  return (i + 1);
}

void swap (int *arr, long index1, long index2){
  int temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}


int *randomArray (long size){
  int *arr = malloc(size * sizeof(int));
  srand(time(0));

  for (long i = 0; i < size; i++){
    int num = (rand() % INT_MAX);
    arr[i] = num;
  }
  return arr;
}
